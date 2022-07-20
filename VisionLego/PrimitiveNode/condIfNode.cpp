#include <vlexception.h>
#include <macro.h>
#include <vlenum.h>

#include "condIfNode.h"




vl::condIfNode::condIfNode(std::string name, vl::ihandle* engine) : vl::node(name, vl::to_integer(vl::objectType::VL_IF), false, engine) {
	try {

	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}


vl::condIfNode::~condIfNode() {

}



void vl::condIfNode::init() {

}

void vl::condIfNode::preprocess() {

}

void vl::condIfNode::process() {


}