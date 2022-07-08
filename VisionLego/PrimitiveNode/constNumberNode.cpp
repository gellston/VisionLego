#include "constNumberNode.h"


namespace vl {
	class impl_constNumberNode {
	public:

		double data;


	};
}


vl::constNumberNode::constNumberNode(std::string name, smrtengine engine) : vl::node(name, (int)vl::objectType::VL_CONST_NUMBER, false, engine),
																		    _instance(new impl_constNumberNode()) {

	this->_instance->data = false;
	this->setConst(true);
}

vl::constNumberNode::~constNumberNode() {

}

void vl::constNumberNode::set(double data) {
	this->_instance->data = data;
}
double vl::constNumberNode::get() {
	return this->_instance->data;
}

void vl::constNumberNode::init() {

}

void vl::constNumberNode::preprocess() {

}

void vl::constNumberNode::process() {


}


