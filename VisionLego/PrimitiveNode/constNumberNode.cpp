#include <vlexception.h>
#include <macro.h>


#include "constNumberNode.h"

namespace vl {
	class impl_constNumberNode {
	public:

		double data;


	};
}


vl::constNumberNode::constNumberNode(std::string name, vl::ihandle* engine) : vl::node(name, vl::to_integer(vl::objectType::VL_CONST_NUMBER), false, engine),
_data(new impl_constNumberNode()) {

	try {
		this->_data->data = false;
		this->setConst(true);
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}

}


vl::constNumberNode::~constNumberNode() {

}

void vl::constNumberNode::set(double data) {
	this->_data->data = data;
}
double vl::constNumberNode::get() {
	return this->_data->data;
}

void vl::constNumberNode::init() {

}

void vl::constNumberNode::preprocess() {

}

void vl::constNumberNode::process() {


}


