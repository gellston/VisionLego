#include "varBoolNode.h"

#include "macro.h"
#include "constBoolNode.h"


vl::varBoolNode::varBoolNode(std::string name, smrtengine engine) : vl::node(name, (int)vl::objectType::VL_CONST_NUMBER, false, engine) {

	this->setConst(false);

	this->registerNode("input", (int)vl::objectType::VL_CONST_BOOL, vl::searchType::input);
	this->registerNode("output", (int)vl::objectType::VL_CONST_BOOL, vl::searchType::output);
}

vl::varBoolNode::~varBoolNode() {

}

void vl::varBoolNode::init() {

}

void vl::varBoolNode::preprocess() {

}

void vl::varBoolNode::process() {
	try {

		auto input = this->searchNode<vl::constBoolNode>("input", vl::searchType::input);
		auto output = this->searchNode<vl::constBoolNode>("output", vl::searchType::output);

		bool value = input->get();
		output->set(value);

	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}


