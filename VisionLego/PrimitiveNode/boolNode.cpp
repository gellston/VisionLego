#include "boolNode.h"


namespace vl {
	class impl_boolNode {
	public:

		bool data;


	};
}


vl::boolNode::boolNode(std::string name, smrtengine engine) : vl::node(name, 1, engine),
										   _instance(new impl_boolNode()) {

	this->_instance->data = false;
}

vl::boolNode::~boolNode() {

}

void vl::boolNode::set(bool data) {
	this->_instance->data = data;
}
bool vl::boolNode::get() {
	return this->_instance->data;
}
