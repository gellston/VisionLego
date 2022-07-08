#include "constBoolNode.h"
#include "vlenum.h"

namespace vl {
	class impl_constBoolNode {
	public:

		bool data;


	};
}


vl::constBoolNode::constBoolNode(std::string name, smrtengine engine) : vl::node(name, (int)vl::objectType::VL_CONST_BOOL, false, engine),
																	    _instance(new impl_constBoolNode()) {

	this->_instance->data = false;
	this->setConst(true);
}

vl::constBoolNode::~constBoolNode() {

}

void vl::constBoolNode::set(bool data) {
	this->_instance->data = data;
	
}
bool vl::constBoolNode::get() {
	return this->_instance->data;
}

void vl::constBoolNode::init() {

}

void vl::constBoolNode::preprocess() {

}

void vl::constBoolNode::process() {


}