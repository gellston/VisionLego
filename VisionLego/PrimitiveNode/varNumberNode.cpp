#include <vlexception.h>
#include <macro.h>

#include "varNumberNode.h"
#include "constNumberNode.h"

vl::varNumberNode::varNumberNode(std::string name, vl::ihandle* engine) : vl::node(name, (int)vl::objectType::VL_NUMBER, false, engine){

	try {
		this->setConst(false);
		this->registerNode("input", (int)vl::objectType::VL_CONST_NUMBER, vl::searchType::input);
		this->registerNode("output", (int)vl::objectType::VL_CONST_NUMBER, vl::searchType::output);
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}


vl::varNumberNode::~varNumberNode() {

}

void vl::varNumberNode::init() {

}

void vl::varNumberNode::preprocess() {

}

void vl::varNumberNode::process() {
	try {

		auto input = this->searchNode<vl::constNumberNode>("input", vl::searchType::input); 
		auto output = this->searchNode<vl::constNumberNode>("output", vl::searchType::output);

		double value = input->get();
		output->set(value);

	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}


