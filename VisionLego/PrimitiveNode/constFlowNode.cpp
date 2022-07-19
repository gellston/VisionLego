#include "vlexception.h"
#include "macro.h"

#include <vlexception.h>
#include <macro.h>

#include "constFlowNode.h"





vl::constFlowNode::constFlowNode(std::string name, vl::ihandle* engine) : vl::node(name, (int)vl::objectType::VL_CONST_FLOW, false, engine)
{
	try {
		this->setConst(true);
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}

}


vl::constFlowNode::~constFlowNode() {

}



void vl::constFlowNode::init() {

}

void vl::constFlowNode::preprocess() {

}

void vl::constFlowNode::process() {


}