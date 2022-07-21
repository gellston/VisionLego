#include <vlexception.h>
#include <macro.h>
#include <iostream>
#include <thread>

#include "varBoolNode.h"
#include "constBoolNode.h"




vl::varBoolNode::varBoolNode(std::string name, vl::ihandle* engine) : vl::node(name, vl::to_integer(vl::objectType::VL_BOOL), false, engine) {

	try {
		this->setConst(false);
		this->registerNode("condition", vl::to_integer(vl::objectType::VL_CONST_FLOW), vl::searchType::input);
		this->registerNode("input", vl::to_integer(vl::objectType::VL_CONST_BOOL), vl::searchType::input);

		this->registerNode("condition", vl::to_integer(vl::objectType::VL_CONST_FLOW), vl::searchType::output);
		this->registerNode("output", vl::to_integer(vl::objectType::VL_CONST_BOOL), vl::searchType::output);
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}


vl::varBoolNode::~varBoolNode() {

}

void vl::varBoolNode::init() {
	try {

		//��� �ʱ�ȭ �ÿ� ȣ���!!
		auto input = this->searchNode<vl::constBoolNode>("input", vl::searchType::input);
		auto output = this->searchNode<vl::constBoolNode>("output", vl::searchType::output);

		input->set(false);
		output->set(false);
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}

void vl::varBoolNode::preprocess() {
	try {
		
		//�뵵�� ������.. ���� �뵵�� ������������

		
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}

void vl::varBoolNode::process() {
	try {

		auto input = this->searchNode<vl::constBoolNode>("input", vl::searchType::input);
		auto output = this->searchNode<vl::constBoolNode>("output", vl::searchType::output);

		bool value = input->get();
		output->set(value);

		//std::cout << "uid = " << this->uid() << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}


