#include "node.h"

#include "macro.h"
#include "iengine.h"


#include <stack>


namespace vl {

	class impl_node {
	public:

		unique _uid;
		unsigned int _depth;
		std::string _name;
		int _type;

		bool _error;
		std::string _message;
		bool _isConst;
		bool _inCondition;

		vl::iengine * _engine;

		std::unordered_map<std::string, input_node> _inputNode;
		std::unordered_map<std::string, output_node> _outputNode;


		std::vector<vl::input_info> _inputInfo;
		std::vector<vl::output_info> _outputInfo;


		std::unordered_map<std::string, std::vector<pointer_inode>> _conditional_node_map;

		impl_node() {
			_uid = 0;
			_depth = 0;
			_name = "";
			_type = 0;
			_error = false;
			_message = "";
			_engine = nullptr;
			_inCondition = false;
		}
		~impl_node() {

		}

	};
}


vl::node::node(std::string name, int type, bool isConst, vl::ihandle * engine) : _instance(new vl::impl_node()) {

	this->_instance->_name = name;
	this->_instance->_type = type;

	this->_instance->_uid = 0;
	this->_instance->_depth = 0;

	this->_instance->_engine = (vl::iengine *) engine;
	this->_instance->_isConst = isConst;

	if (engine == nullptr) {
		std::string message = generate_error_message(__FUNCTION__, __LINE__, "Null engine");
		throw vl::exception(message);
	}

}

vl::node::~node() {
	this->_instance->_inputInfo.clear();
	this->_instance->_inputNode.clear();
	this->_instance->_outputInfo.clear();
	this->_instance->_outputNode.clear();

}


unsigned long long vl::node::uid() {

	return this->_instance->_uid;
}

void vl::node::uid(unique value) {
	this->_instance->_uid = value;
}

std::string vl::node::name() {

	return this->_instance->_name;

}

void vl::node::name(std::string _name) {
	this->_instance->_name = _name;
}

int vl::node::type() {

	return this->_instance->_type;
}

unsigned int vl::node::depth() {

	return this->_instance->_depth;
}


void vl::node::depth(unsigned int depth) {
	this->_instance->_depth = depth;
	if(this->_instance->_engine != nullptr)
		this->_instance->_engine->depthUpdate(depth);
}

bool vl::node::error() {
	return this->_instance->_error;
}

std::string vl::node::message() {
	return this->_instance->_message;
}

bool vl::node::inCondition() {
	return this->_instance->_inCondition;
}

void vl::node::setCondition(bool check) {
	this->_instance->_inCondition = check;
}

bool vl::node::isConst() {
	return this->_instance->_isConst;
}

void vl::node::setConst(bool isConst) {
	this->_instance->_isConst = isConst;
}

void vl::node::checkConnectivity() {


	if (this->_instance->_engine == nullptr) {
		std::string message = generate_error_message(__FUNCTION__, __LINE__, "Null engine exception");
		throw vl::exception(message);
	}


	
	for (auto & element : this->_instance->_inputNode)
	{

		auto & type_id = std::get<0>(element.second);
		auto & node = std::get<1>(element.second); //const node pointer
		auto & isConst = std::get<2>(element.second); //is const check
		auto & unique = std::get<3>(element.second); //unique id

		std::string param_name = element.first;

		if (type_id == vl::non_type) {
			std::string info = this->name();
			info += ":";
			info += param_name;
			info += ":";
			info += "Invalid type";

			std::string message = generate_error_message(__FUNCTION__, __LINE__, info);
			throw vl::exception(message);
		}

		if (isConst == false && unique == vl::non_uid) {
			std::string info = this->name();
			info += ":";
			info += param_name;
			info += ":";
			info += "Node is not connected";

			std::string message = generate_error_message(__FUNCTION__, __LINE__, info);
			throw vl::exception(message);
		}

		if (isConst == false && this->_instance->_engine->checkDepth(unique, this->_instance->_depth) == false) {
			std::string info = this->name();
			info += ":";
			info += param_name;
			info += ":";
			info += "Invalid node path info";

			std::string message = generate_error_message(__FUNCTION__, __LINE__, info);
			throw vl::exception(message);
		}
	}
}


void vl::node::registerNode(std::string name, int objectType, vl::searchType type) {

	if (this->_instance->_engine == nullptr) {
		std::string message = generate_error_message(__FUNCTION__, __LINE__, "Null engine exception");
		throw vl::exception(message);
	}


	try {
		
		switch (type)
		{
		case vl::searchType::input: {
			auto inode = this->_instance->_engine->create(name, objectType);
			auto node = std::dynamic_pointer_cast<vl::node>(inode);
			auto innode = std::make_tuple(objectType, node, true, (unsigned long long)non_uid, "");
			this->_instance->_inputNode[name] = innode;
			this->_instance->_inputInfo.push_back({ name, objectType });
			break;
		}
		case vl::searchType::output: {
			auto inode = this->_instance->_engine->create(name, objectType);
			auto node = std::dynamic_pointer_cast<vl::node>(inode);
			auto outnode = std::make_tuple(objectType, node);
			this->_instance->_outputNode[name] = outnode;
			this->_instance->_outputInfo.push_back({ name, objectType });
			break;
		}
		default:
			throw std::exception("Invalid search type");
			break;
		}
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}




vl::pointer_node vl::node::searchNode(std::string name, vl::searchType type) {

	if (this->_instance->_engine == nullptr) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Null engine exception");
		throw vl::exception(message);
	}


	switch (type)
	{
	case vl::searchType::input: {
		if (this->_instance->_inputNode.find(name) == this->_instance->_inputNode.end()) {
			std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Invalid node key");
			throw vl::exception(message);
		}


		vl::input_node inputInfo = this->_instance->_inputNode[name];
		//name,  상수 노드, 상수 노드 사용 유무,  uid
		//using input_node = std::tuple<pointer_node, bool, unsigned long long>;

		auto type_id = std::get<0>(inputInfo);
		auto node = std::get<1>(inputInfo); //const node pointer
		auto isConst = std::get<2>(inputInfo); //is const check
		auto unique = std::get<3>(inputInfo); //unique id
		auto outputKey = std::get<4>(inputInfo); //output key


		if (isConst == true) return node;


		try {
			auto node = this->_instance->_engine->find(unique, outputKey, this->_instance->_depth);
			return std::dynamic_pointer_cast<vl::node>(node);

		}
		catch (vl::exception exception) {
			throw exception;
		}

		break;
	}
	case vl::searchType::output: {
		if (this->_instance->_outputNode.find(name) == this->_instance->_outputNode.end()) {
			std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Invalid node key");
			throw vl::exception(message);
		}


		auto outputInfo = this->_instance->_outputNode[name];
		auto tpye_id = std::get<0>(outputInfo);
		auto node = std::get<1>(outputInfo); //const node pointer

		return node;

		break;
	}

	default: {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Invalid search type argument");
		throw vl::exception(message);
	}
		break;
	}
}


std::shared_ptr<vl::inode> vl::node::input(std::string key) {
	if (this->_instance->_inputNode.find(key) == this->_instance->_inputNode.end()) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Invalid input key");
		throw vl::exception(message);
	}
	auto node = std::get<1>(this->_instance->_inputNode[key]);
	return node;
}

std::shared_ptr<vl::inode> vl::node::output(std::string key) {
	if (this->_instance->_outputNode.find(key) == this->_instance->_outputNode.end()) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Invalid output key");
		throw vl::exception(message);
	}
	auto node = std::get<1>(this->_instance->_outputNode[key]);
	return node;
}

std::vector<vl::input_info> vl::node::input() {
	return this->_instance->_inputInfo;
}
std::vector<vl::output_info> vl::node::output() {
	return this->_instance->_outputInfo;
}

std::vector<unsigned long long> vl::node::inputUid() {
	std::vector<unsigned long long> uids;
	for (auto& pair : this->_instance->_inputNode) {
		if (std::get<2>(pair.second) == false) {
			uids.push_back(std::get<3>(pair.second));
		}
	}
	return uids;
}

std::vector<unsigned long long> vl::node::outputUid() {
	return this->_instance->_engine->searchInputUID(this->uid(), this->depth());
}

void vl::node::connect(std::string outkey, unsigned long long outUid, std::string inkey) {


	if (this->_instance->_engine == nullptr) {
		std::string message = generate_error_message(__FUNCTION__, __LINE__, "Null engine exception");
		throw vl::exception(message);
	}



	try {

		auto outNode = this->_instance->_engine->find(outUid);
		auto outNodeOutput = outNode->output(outkey);

		if (this->_instance->_inputNode.find(inkey) == this->_instance->_inputNode.end()) {
			std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Invalid input key");
			throw vl::exception(message);
		}

		auto & inNode = this->_instance->_inputNode[inkey];

		auto type = std::get<0>(inNode);
		
		if (type != outNodeOutput->type()) {
			std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Invalid node connection type");
			throw vl::exception(message);
		}


		//Back tracking 필요!! 젠장
		//Back tracking 시작!! 
		auto outputNodes = this->outputUid();
		std::stack<unsigned long long>_node_stack;
		for (auto& uid : outputNodes)
			_node_stack.push(uid);
		
		while (_node_stack.empty() != true) {
			auto _cyrrebtUid = _node_stack.top();
			_node_stack.pop();

			auto _currentOutNode = this->_instance->_engine->find(_cyrrebtUid);
			auto _currentUid = _currentOutNode->outputUid();
			if (outNode == _currentOutNode) {
				std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Recursive node error");
				throw vl::exception(message);
			}

			for (auto& _new_uid : _currentUid)
				_node_stack.push(_new_uid);
		}


		auto finalDepth = outNode->depth() + 1;

		if (finalDepth > this->depth())
			this->depth(finalDepth);
		
		std::get<2>(inNode) = false;  //상수 사용 해제
		std::get<3>(inNode) = outUid;  //uid 설정
		std::get<4>(inNode) = outkey;   //out node 이름 지정 

	}
	catch (vl::exception e) {
		throw e;
	}

	this->_instance->_engine->depthAlign();
	this->_instance->_engine->depthSorting();

}

void vl::node::connect(pointer_inode outNode, std::string outKey, std::string inkey) {
	try {

		this->connect(outKey, outNode->uid(), inkey);
	}
	catch (vl::exception e) {
		throw e;
	}
}


void vl::node::disconnect(std::string inKey) {

	if (this->_instance->_engine == nullptr) {
		std::string message = generate_error_message(__FUNCTION__, __LINE__, "Null engine exception");
		throw vl::exception(message);
	}

	try {

		if (this->_instance->_inputNode.find(inKey) == this->_instance->_inputNode.end()) {
			std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Invalid input key");
			throw vl::exception(message);
		}


		auto & inNode = this->_instance->_inputNode[inKey];


		auto useConst = std::get<2>(inNode); //const use;
		if (useConst == false) {
			std::get<3>(inNode) = vl::non_uid;	//clear uid
			std::get<2>(inNode) = true;			//const use on
			std::get<4>(inNode) = "";
		}

		unsigned int deepDepth = 0;
		for (auto& input : this->_instance->_inputNode) {
			auto key = input.first;
			auto uid = std::get<3>(input.second);
			auto isConst = std::get<2>(input.second);

			
			if (isConst == false) {
				auto inputNode = this->_instance->_engine->find(uid);

				auto objectDepth = inputNode->depth();
				if (objectDepth > deepDepth)
					deepDepth = objectDepth;
			}
		}
		deepDepth += 1;
		this->depth(deepDepth);
	}
	catch (vl::exception e) {
		throw e;
	}

	this->_instance->_engine->depthAlign();
	this->_instance->_engine->depthSorting();
}


void vl::node::addInCondition(std::string name, unsigned long long uid) {


	try {

		auto node = this->_instance->_engine->find(uid);

		if (node->uid() == this->uid()) {
			std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Can't add node recursively");
			throw vl::exception(message);
		}

		if (node->depth() < this->depth()) {
			std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Invalid node depth");
			throw vl::exception(message);
		}


		for (auto& condition_map : this->_instance->_conditional_node_map) {
			auto& condition_vector = condition_map.second;

			if (std::find(condition_vector.begin(), condition_vector.end(), node) != condition_vector.end()) {
				std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Exist node in condition map");
				throw vl::exception(message);
			}
		}

		if (this->_instance->_conditional_node_map.find(name) == this->_instance->_conditional_node_map.end()) {
			std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Can't find condition map name");
			throw vl::exception(message);
		}



		//Back tracking 필요!! 젠장
		//Back tracking 시작!! 
		auto outputNodes = node->outputUid();
		std::stack<unsigned long long>_node_stack;
		for (auto& uid : outputNodes)
			_node_stack.push(uid);

		while (_node_stack.empty() != true) {
			auto _currentUID = _node_stack.top();
			_node_stack.pop();

			auto _currentOutNode = this->_instance->_engine->find(_currentUID);
			auto _currentUid = _currentOutNode->outputUid();
			if (this == _currentOutNode.get()) {
				std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Recursive node error");
				throw vl::exception(message);
			}

			for (auto& _new_uid : _currentUid)
				_node_stack.push(_new_uid);
		}



		node->connect("condition", this->uid(), "condition");
		node->setCondition(true);

		//auto outputNodes = node->outputUid();
		//std::stack<unsigned long long>_node_stack;
		//for (auto& uid : outputNodes)
		//	_node_stack.push(uid);

		//while (_node_stack.empty() != true) {
		//	auto _currentUID = _node_stack.top();
		//	_node_stack.pop();

		//	auto _currentOutNode = this->_instance->_engine->find(_currentUID);
		//	auto _currentUid = _currentOutNode->outputUid();
		//	if (this == _currentOutNode.get()) {
		//		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Recursive node error");
		//		throw vl::exception(message);
		//	}

		//	for (auto& _new_uid : _currentUid)
		//		_node_stack.push(_new_uid);
		//}


		//여기서 부터코딩
		this->_instance->_conditional_node_map[name].push_back(node);

	}
	catch (vl::exception e) {
		throw e;
	}




	this->_instance->_engine->depthAlign();
	this->_instance->_engine->depthSorting();
}


void vl::node::addInCondition(std::string name, pointer_inode node) {
	try {

		this->addInCondition(name, node->uid());
	}
	catch (vl::exception e) {
		throw e;
	}
}