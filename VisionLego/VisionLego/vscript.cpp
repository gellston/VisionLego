#include "vscript.h"

#include <node.h>
#include <unordered_map>
#include <vlexception.h>
#include <filesystem>
#include <macro.h>
#include <Windows.h>
#include <iconstructor.h>
#include <iengine.h>
#include <random>
#include <iostream>

namespace vl {

	class impl_vscript {
	public:

		std::unordered_map<unsigned long long, pointer_node> _nodes_table;
		std::unordered_map<std::string, HMODULE> _addon_handles;
		std::vector<vl::addon_info> _addonInfo;
		std::string _libraryPath;
		std::vector<pointer_iaddon> _addons;

		impl_vscript() {

		}

		~impl_vscript() {

		}
	};


	class engine : public vl::iengine {

	private:
		vl::impl_vscript * _instance;

	public:

		engine() {
			_instance = nullptr;
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
				throw e;
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
	};
}


vl::vscript::vscript() : _instance(new vl::impl_vscript()), _engine(new vl::engine()) {
	this->_engine->setScript(this->_instance.get());
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
		throw e;
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

void vl::vscript::run() {
	try {

	}
	catch (vl::exception e) {

	}
}

void vl::vscript::compile() {

}

void vl::vscript::load(std::string context, vl::contextType type) {

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

				return convertedNode;
			}
		}
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}

}


void vl::vscript::clearNode() {
	this->_instance->_nodes_table.clear();
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
		throw e;
	}
}

void vl::vscript::connect(unsigned long long outUid, std::string outKey, unsigned long long inUid, std::string inKey) {

	try {
		auto outNode = this->_engine->find(outUid);
		auto inNode = this->_engine->find(inUid);

		this->connect(outNode, outKey, inNode, inKey);
	}
	catch (vl::exception e) {
		throw e;
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
		info += "\n";
		std::cout << info << std::endl;
	}
	std::cout << "=============================" << std::endl;
}