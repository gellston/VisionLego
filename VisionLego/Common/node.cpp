#include "node.h"

#include "macro.h"
#include "vlexception.h"

namespace vl {

	class impl_node {
	public:

		unique _uid;
		unsigned int _depth;
		std::string _name;
		int _type;

		bool _error;
		std::string _message;

		smrtengine _engine;

		std::unordered_map<std::string, input_node> _inputNode;
		std::unordered_map<std::string, output_node> _outputNode;

		impl_node() {
			_uid = 0;
			_depth = 0;
			_name = "";
			_type = 0;
			_error = false;
			_message = "";
		}
		~impl_node() {

		}

	};
}


vl::node::node(std::string name, int type, smrtengine engine) : _instance(new vl::impl_node()) {

	this->_instance->_name = name;
	this->_instance->_type = type;


	this->_instance->_uid = 0;
	this->_instance->_depth = 0;

	this->_instance->_engine = engine;

	if (engine == nullptr) {
		std::string message = generate_error_message(__FUNCTION__, __LINE__, "Null engine");
		throw vl::exception(message);
	}


}

vl::node::~node() {


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
}

bool vl::node::error() {
	return this->_instance->_error;
}

std::string vl::node::message() {
	return this->_instance->_message;
}


void vl::node::check() {

	
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

		if (isConst == false && this->_instance->_engine->exist(unique) == false) {
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


vl::pointer_node vl::node::searchNode(std::string name, vl::searchType type) {

	if (this->_instance->_engine == nullptr) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "invalid engine");
		throw vl::exception(message);
	}


	switch (type)
	{
	case vl::searchType::input: {
		if (this->_instance->_inputNode.find(name) == this->_instance->_inputNode.end()) {
			std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "invalid node key");
			throw vl::exception(message);
		}


		vl::input_node inputInfo = this->_instance->_inputNode[name];
		//name,  상수 노드, 상수 노드 사용 유무,  uid
		//using input_node = std::tuple<pointer_node, bool, unsigned long long>;

		auto type_id = std::get<0>(inputInfo);
		auto node = std::get<1>(inputInfo); //const node pointer
		auto isConst = std::get<2>(inputInfo); //is const check
		auto unique = std::get<3>(inputInfo); //unique id


		if (isConst == true) return node;


		try {
			auto node = this->_instance->_engine->find(unique);
			return std::dynamic_pointer_cast<vl::node>(node);

		}
		catch (vl::exception exception) {
			throw exception;
		}

		break;
	}
	case vl::searchType::output: {
		if (this->_instance->_outputNode.find(name) == this->_instance->_outputNode.end()) {
			std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "invalid node key");
			throw vl::exception(message);
		}


		auto outputInfo = this->_instance->_outputNode[name];
		auto tpye_id = std::get<0>(outputInfo);
		auto node = std::get<1>(outputInfo); //const node pointer

		return node;

		break;
	}

	default: {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "invalid search type argument");
		throw vl::exception(message);
	}
		break;
	}
}
