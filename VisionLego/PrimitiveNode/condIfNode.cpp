#include <vlexception.h>
#include <macro.h>
#include <vlenum.h>
#include <iostream>


#include "condIfNode.h"
#include "constBoolNode.h"



vl::condIfNode::condIfNode(std::string name, vl::ihandle* engine) : vl::node(name, vl::to_integer(vl::objectType::VL_IF), false, engine) {
	try {
		this->setConst(false);
		this->registerNode("condition", vl::to_integer(vl::objectType::VL_CONST_FLOW), vl::searchType::input);
		this->registerNode("check", vl::to_integer(vl::objectType::VL_CONST_BOOL), vl::searchType::input);

		this->registerNode("condition", vl::to_integer(vl::objectType::VL_CONST_FLOW), vl::searchType::output);


		this->registerCondition("if");
		this->registerCondition("else");

	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}


vl::condIfNode::~condIfNode() {

}



void vl::condIfNode::init() {
	try {

		//노드 초기화 시에 호출됨!!
		auto check = this->searchNode<vl::constBoolNode>("check", vl::searchType::input);
		check->set(false);
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}

void vl::condIfNode::preprocess() {

}

void vl::condIfNode::process() {
	try {

		auto check = this->searchNode<vl::constBoolNode>("check", vl::searchType::input);

		if (check->get() == true) {
			std::cout << "if condition" << std::endl;
			this->runCondition("if");
			std::cout << "if condition" << std::endl;
		}
		else {
			std::cout << "else condition" << std::endl;
			this->runCondition("else");
			std::cout << "else condition" << std::endl;
		}
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}