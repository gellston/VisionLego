#include "vscript.h"


#include <unordered_map>
#include <filesystem>
#include <Windows.h>
#include <random>
#include <algorithm>
#include <future>
#include <fstream>
#include <iostream>
#include <sstream>


#include <node.h>
#include <vlexception.h>
#include <macro.h>
#include <iconstructor.h>
#include <iengine.h>

#include <nlohmann/json.hpp>



namespace vl {

	class impl_vscript {
	public:

		std::unordered_map<unsigned long long, pointer_node> _nodes_table;
		//std::vector<pointer_node> _align_nodes;
		std::unordered_map<unsigned int, std::vector<pointer_node>> _align_nodes;
		std::unordered_map<std::string, HMODULE> _addon_handles;
		std::vector<vl::addon_info> _addonInfo;
		std::string _libraryPath;
		std::vector<pointer_iaddon> _addons;

		unsigned int _max_task_count;

		impl_vscript() {

			
		}

		~impl_vscript() {

		}
	};


	class engine : public vl::iengine {

	private:
		vl::impl_vscript * _instance;
		unsigned int _depth;

	public:

		engine() {
			_instance = nullptr;
			this->_depth = 0;
		}

		~engine() {
		}

		void setScript(vl::impl_vscript* arg) {
			this->_instance = arg;
		}

		void registerAddon(pointer_iaddon addon) {
			this->_instance->_addons.push_back(addon);
		}

		//For graph creation

		vl::pointer_inode find(unsigned long long uid) {
			if (this->_instance->_nodes_table.find(uid) == this->_instance->_nodes_table.end()) {
				std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Uid is not exist");
				throw vl::exception(message);
			}
			auto node = this->_instance->_nodes_table[uid];
			return node;
		}

		vl::pointer_inode find(unsigned long long uid, std::string key, unsigned int depth) {

			if (this->_instance->_nodes_table.find(uid) == this->_instance->_nodes_table.end()) {
				std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Uid is not exist");
				throw vl::exception(message);
			}

			try {
				auto node = this->_instance->_nodes_table[uid]; //outNode
				if (node->depth() >= depth) {
					std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Invalid graph depth");
					throw vl::exception(message);
				}
				auto const_output = node->output(key);
				return const_output;
			}
			catch (vl::exception e) {
				std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
				throw vl::exception(message);
			}
		}


		void depthAlign() {
			//Depth align process start!
			for (unsigned int depth = 1; depth <= this->deepDepth() + 1; depth++) {
				std::vector<vl::pointer_node> equal_vectors;
				for (auto& pair : this->_instance->_nodes_table) {
					if (depth == pair.second->depth()) {
						equal_vectors.push_back(pair.second);
					}
				}


				for (auto& object : equal_vectors) {

					//current Depth
					unsigned int currentDepth = 0;

					//Input Depth Collection and check Depth 
					auto uidGroup = object->inputUid();
					for (auto& uid : uidGroup) {


						auto inputNodeUID = this->_instance->_nodes_table[uid]->depth();

						if (inputNodeUID > currentDepth)
							currentDepth = inputNodeUID;
					}

					currentDepth++; //current Node depth increase for depth align;
					object->depth(currentDepth);
				}
			}

		}

		void depthSorting() {
			//Depth sorting process start!
			this->_instance->_align_nodes.clear();
			for (unsigned int depth = 1; depth <= this->deepDepth() + 1; depth++) {
				std::vector<vl::pointer_node> equal_vectors;
				for (auto& pair : this->_instance->_nodes_table) {
					if (depth == pair.second->depth()) {
						equal_vectors.push_back(pair.second);
					}
				}
				for (auto& object : equal_vectors) {
					this->_instance->_align_nodes[depth].push_back(object);
				}
			}
		}

		bool checkDepth(unsigned long long uid, unsigned int depth) {

			if (this->_instance->_nodes_table.find(uid) == this->_instance->_nodes_table.end())
				return false;

			if (this->_instance->_nodes_table[uid]->depth() < depth)
				return true;
			else 
				return false;
		}

		void depthUpdate(unsigned int depth) {
			if (this->_depth < depth)
				this->_depth = depth;
		}

		void clearDeepDepth() {
			this->_depth = 0;
		}

		unsigned int deepDepth() {
			return this->_depth;
		}

		vl::pointer_inode create(std::string name, int objectType) {
			try {
				for (auto addon : this->_instance->_addons) {
					if (addon->exist(objectType) == true) {
						auto constructor = addon->find(objectType);
						auto node = constructor->create(name, this);
						if(node->isConst() == true)
							return node;
					}
				}

				std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Can't find object type");
				throw vl::exception(message);
			}
			catch (std::exception e) {
				std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
				throw vl::exception(message);
			}
		}

		std::vector<unsigned long long> searchInputUID(unsigned long long inputUid, unsigned int depth) {
			std::vector<unsigned long long> uidResult;

			for (auto & nodeInfo : this->_instance->_nodes_table) {
				auto node = nodeInfo.second;

				if (depth >= node->depth())
					continue;

				auto inputUidInfo = node->inputUid();

				if (std::find(inputUidInfo.begin(), inputUidInfo.end(), inputUid) != inputUidInfo.end()) {
					uidResult.push_back(node->uid());
				}
			}
			return uidResult;
		}


		
	};
}


vl::vscript::vscript() : _instance(new vl::impl_vscript()), _engine(new vl::engine()) {
	this->_engine->setScript(this->_instance.get());

	this->_instance->_max_task_count = 4;
}


vl::vscript::~vscript() {
	try {
		this->clearNode();
		this->unloadLibrary();
	}
	catch (std::exception e) {

	}
}


void vl::vscript::setAddonPath(std::string path) {

	if (std::filesystem::exists(path) == false) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Addon path is not exists");
		throw vl::exception(message);
	}

	this->_instance->_libraryPath = path;
}

void vl::vscript::loadLibrary() {

	if (this->_instance->_addon_handles.size() > 0) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "library is already loaded.");
		throw vl::exception(message);
	}


	if (this->_instance->_libraryPath.length() == 0) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Invalid library path.");
		throw vl::exception(message);
	}

	for (const auto& entry : std::filesystem::directory_iterator(this->_instance->_libraryPath)) {
		if (entry.path().extension().string() == ".dll") {
			std::string filePath = entry.path().string();
			std::string fileName = entry.path().filename().string();
			bool check = false;
			HMODULE module = LoadLibraryA(filePath.c_str());
			if (module != nullptr) {

				try {

					auto vl_version = (const char* (*)())GetProcAddress(module, "vl_version");
					auto vl_name = (const char* (*)())GetProcAddress(module, "vl_name");
					auto vl_module = (bool (*)())GetProcAddress(module, "vl_module");
					auto vl_init = (void (*)(vl::iengine*))GetProcAddress(module, "vl_init");

					if (vl_version == nullptr || vl_name == nullptr || vl_module == nullptr || vl_init == nullptr) {
						FreeLibrary(module);
						continue;
					}

					if (vl_module() == false) {
						FreeLibrary(module);
						continue;
					}

					vl_init(this->_engine.get());

					std::string version = vl_version();
					std::string name = vl_name();
					

					this->_instance->_addon_handles[fileName] = module;
					this->_instance->_addonInfo.push_back({ name, version });
				}
				catch (std::exception e) {
					FreeLibrary(module);
				}
			}
		}
	}
}


void vl::vscript::unloadLibrary() {

	std::vector <std::string> removedkey;
	bool error = false;
	try {

		this->_engine->clearDeepDepth();

		this->_instance->_nodes_table.clear();
		this->_instance->_addons.clear();

		for (auto& pair : this->_instance->_addon_handles) {
			if ((bool)FreeLibrary(pair.second) == true) {
				removedkey.push_back(pair.first);
			}
			else {
				error = true;
			}
		}

		for (auto& key : removedkey) {
			this->_instance->_addon_handles.erase(key);
		}

		if (error) {
			std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Unexpected error detected. please check addon");
			throw vl::exception(message);
		}
	}
	catch (vl::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}

std::vector<std::shared_ptr<vl::iaddon>> vl::vscript::addons() {
	return this->_instance->_addons;
}

std::vector<vl::addon_info> vl::vscript::addonInfo() {
	return this->_instance->_addonInfo;
}

void vl::vscript::run(vl::syncType sync) {

	volatile bool errorDetected = false;

	
	switch (sync)
	{
	case vl::syncType::serial: {
		for (unsigned int depth = 1; depth < this->_engine->deepDepth() + 1; depth++) {
			for (auto& node : this->_instance->_align_nodes[depth]) {
				try {
					if (node->inCondition() == true) continue;

					node->process();
				}
				catch (vl::exception e) {
					std::cout << e.what() << std::endl;
					errorDetected = true;
				}
			}
		}
		break;
	}
		
	case vl::syncType::parallel: {

		auto maxCount = this->_instance->_max_task_count;
		for (unsigned int depth = 1; depth < this->_engine->deepDepth() + 1; depth++) {

			auto _tasks = this->_instance->_align_nodes[depth];

			volatile int currentIndex = 0;

			std::vector<std::future<void>> _futures;
			for (unsigned int currentIndex =0; currentIndex < _tasks.size(); currentIndex++) {

				_futures.push_back(std::async(std::launch::async, [&](auto index) {
					try {
						_tasks[index]->process();
					}
					catch (vl::exception e) {
						errorDetected = true;
					}
				}, currentIndex));


				if (_futures.size() == maxCount) {
					for (auto& future : _futures) {
						future.wait();
					}
					_futures.clear();
				}
				
			}

			for (auto& future : _futures) {
				future.wait();
			}
		}


		break;
	}
	default:
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Invalid execution enum.");
		throw vl::exception(message);
	}

	if (errorDetected == true) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Vision script run failed.");
		throw vl::exception(message);
	}
}

void vl::vscript::save(std::string path) {
	try {
		std::ofstream out(path);
		out << this->serialization();
		out.close();
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}

void vl::vscript::setMaxTaskCount(int num) {
	this->_instance->_max_task_count = num;
}

void vl::vscript::verification() {
	/// <summary>
	/// Check Connectivity
	/// </summary>
	/// 
	/// 
	bool errorDetected = false;


	for (unsigned int depth = 1; depth < this->_engine->deepDepth() + 1; depth++) {
		for (auto& node : this->_instance->_align_nodes[depth]) {
			try {

				node->checkConnectivity();
			}
			catch (vl::exception e) {
				errorDetected = true;
			}
		}
	}

	if (errorDetected == true) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Vision verification failed.");
		throw vl::exception(message);
	}

}

void vl::vscript::load(std::string context, vl::contextType type) {
	try {


		switch (type)
		{
		case vl::contextType::file: {

			std::ifstream inFile;
			inFile.open(context); //open the input file

			std::stringstream strStream;
			strStream << inFile.rdbuf(); //read the file
			std::string content = strStream.str();


			std::vector<std::string> lines;
			auto ss = std::stringstream{ content };

			for (std::string line; std::getline(ss, line, '\n');)
				lines.push_back(line);

			this->clearNode();

			for (auto& line : lines) {
				auto object = nlohmann::json::parse(line);
				int type = object["type"];
				unsigned long long uid = object["uid"];

				auto node = this->addNode("", type, uid);
				node->parse(line);
			}
			
			this->_engine->depthAlign();
			this->_engine->depthSorting();

			break;
		}
			
		case vl::contextType::json: {

			std::vector<std::string> lines;
			auto ss = std::stringstream{ context };

			for (std::string line; std::getline(ss, line, '\n');)
				lines.push_back(line);

			this->clearNode();

			for (auto& line : lines) {
				auto object = nlohmann::json::parse(line);
				int type = object["type"];
				unsigned long long uid = object["uid"];

				auto node = this->addNode("", type, uid);
				node->parse(line);
			}

			this->_engine->depthAlign();
			this->_engine->depthSorting();

			break;
		}
		default:
			std::string message = vl::generate_error_message(__FUNCTION__, __LINE__,"Invalid load type");
			throw vl::exception(message);
			break;
		}
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}

void  vl::vscript::initNodes() {

	bool errorDetected = false;

	for (unsigned int depth = 1; depth < this->_engine->deepDepth() + 1; depth++) {
		for (auto& node : this->_instance->_align_nodes[depth]) {
			try {
				node->init();
			}
			catch (vl::exception e) {
				errorDetected = true;
			}
		}
	}

	if (errorDetected == true) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Vision verification failed.");
		throw vl::exception(message);
	}
}

vl::pointer_node vl::vscript::addNode(std::string name, int objectType, unsigned long long uid) {
	try {
		for (auto addon : this->_instance->_addons) {
			if (addon->exist(objectType) == true) {
				auto constructor = addon->find(objectType);
				auto node = constructor->create(name, this->_engine.get());
				if (node->isConst() == true) {
					std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Const object type error");
					throw vl::exception(message);
				}

				unsigned long long unique_id = uid;

				node->uid(unique_id);
				node->name(name);
				node->depth(1);

				auto convertedNode = std::dynamic_pointer_cast<vl::node>(node);
				this->_instance->_nodes_table[unique_id] = convertedNode;


				//Sorting Start;
				//this->_engine->depthSorting();


				return convertedNode;
			}
		}

		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Object tpye not exists");
		throw vl::exception(message);
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}


vl::pointer_node vl::vscript::addNode(std::string name, int objectType) {
	try {
		for (auto addon : this->_instance->_addons) {
			if (addon->exist(objectType) == true) {
				auto constructor = addon->find(objectType);
				auto node = constructor->create(name, this->_engine.get());
				if (node->isConst() == true) {
					std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Const object type error");
					throw vl::exception(message);
				}

				std::random_device rd;
				std::mt19937_64 mersenne(rd());
				std::uniform_int_distribution<unsigned long long int> dice(1, INT64_MAX);

				unsigned long long unique_id = vl::non_uid;
				do {
					unique_id = dice(rd);
				} while (this->_instance->_nodes_table.find(unique_id) != this->_instance->_nodes_table.end());
				
				node->uid(unique_id);
				node->name(name);
				node->depth(1);

				auto convertedNode = std::dynamic_pointer_cast<vl::node>(node);
				this->_instance->_nodes_table[unique_id] = convertedNode;


				//Sorting Start;
				this->_engine->depthSorting();


				return convertedNode;
			}
		}

		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Object tpye not exists");
		throw vl::exception(message);
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}

}


void vl::vscript::clearNode() {
	this->_instance->_nodes_table.clear();
	this->_instance->_align_nodes.clear();
	this->_engine->clearDeepDepth();
}


void vl::vscript::connect(pointer_inode outNode, std::string outKey, pointer_inode inNode, std::string inKey){

	if (inNode.get() == outNode.get() || inNode == nullptr || outNode == nullptr) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Invalid node information");
		throw vl::exception(message);
	}
	
	try {
		inNode->connect(outKey, outNode->uid(), inKey);
	}
	catch (vl::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}

void vl::vscript::connect(unsigned long long outUid, std::string outKey, unsigned long long inUid, std::string inKey) {

	try {
		auto outNode = this->_engine->find(outUid);
		auto inNode = this->_engine->find(inUid);
		this->connect(outNode, outKey, inNode, inKey);
	}
	catch (vl::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}


void vl::vscript::disconnect(pointer_inode inNode, std::string inKey) {
	try {
		this->disconnect(inNode->uid(), inKey);
	}
	catch (vl::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}

void vl::vscript::disconnect(unsigned long long inUid, std::string inKey) {
	try {
		auto inNode = this->_engine->find(inUid);
		inNode->disconnect(inKey);
	}
	catch (vl::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}

vl::pointer_inode vl::vscript::findNode(unsigned long long uid) {
	if (this->_instance->_nodes_table.find(uid) == this->_instance->_nodes_table.end()) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Uid is not exist");
		throw vl::exception(message);
	}

	return this->_instance->_nodes_table[uid];
}


void vl::vscript::printNodeInfo() {
	std::cout << "========= node info =========" << std::endl;
	for (auto pair : this->_instance->_nodes_table) {
		std::string info = std::to_string(pair.first);
		info += ",";
		info += pair.second->name();
		info += ",";
		info += std::to_string(pair.second->type());
		info += ",";
		info += std::to_string(pair.second->depth());
		info += ",";
		info += pair.second->inCondition() == true ? "true" : "false";
		info += "\n";
		std::cout << info << std::endl;
	}
	std::cout << "=============================" << std::endl;
}

std::string vl::vscript::serialization() {
	std::string content;
	for (auto& keyPair : this->_instance->_nodes_table) {
		auto& node = keyPair.second;
		content += node->serialization();
		content += "\n";
	}
	return content;
}


void vl::vscript::disconnect(unsigned long long inUidm) {

	try {
		auto node = this->findNode(inUidm);
		auto outputUID = node->outputUid();

		for (auto uid : outputUID) {
			try {
				auto targetNode = this->findNode(uid);
				targetNode->disconnect(inUidm);
			}
			catch (vl::exception e) {

			}
		}

	}
	catch (vl::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}

}


void vl::vscript::disconnect(pointer_inode inNode) {
	try {
		this->disconnect(inNode->uid());

	}
	catch (vl::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}


void vl::vscript::removeNode(unsigned long long uid) {
	try {

		try {
			this->disconnect(uid);
		}
		catch (vl::exception e) {

		}

		this->_instance->_nodes_table.erase(uid);
		this->_engine->depthAlign();
		this->_engine->depthSorting();
	}
	catch (vl::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}


void vl::vscript::removeNode(pointer_inode node) {
	try {
		this->removeNode(node->uid());
	}
	catch (vl::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}