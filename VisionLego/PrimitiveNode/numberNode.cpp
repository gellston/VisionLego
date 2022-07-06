#include "numberNode.h"


namespace vl {
	class impl_numberNode {
	public:

		double data;


	};
}


vl::numberNode::numberNode(std::string name, smrtengine engine) : vl::node(name, 2, engine),
_instance(new impl_numberNode()) {


	this->_instance->data = false;
}

vl::numberNode::~numberNode() {

}

void vl::numberNode::set(double data) {
	this->_instance->data = data;
}
double vl::numberNode::get() {
	return this->_instance->data;
}


void vl::numberNode::preprocess() {

}

void vl::numberNode::process() {


}


