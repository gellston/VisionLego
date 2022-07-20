#include <vlexception.h>
#include <macro.h>

#include "constBoolNode.h"


namespace vl {
	class impl_constBoolNode {
	public:

		bool data;


	};
}


vl::constBoolNode::constBoolNode(std::string name, vl::ihandle* engine) : vl::node(name, vl::to_integer(vl::objectType::VL_CONST_BOOL), false, engine),
_data(new impl_constBoolNode()) {
	try {
		this->_data->data = false;
		this->setConst(true);
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}

}


vl::constBoolNode::~constBoolNode() {

}

void vl::constBoolNode::set(bool data) {
	this->_data->data = data;
	
}
bool vl::constBoolNode::get() {
	return this->_data->data;
}

void vl::constBoolNode::init() {

}

void vl::constBoolNode::preprocess() {

}

void vl::constBoolNode::process() {


}