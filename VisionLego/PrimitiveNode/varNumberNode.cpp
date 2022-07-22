#include <vlexception.h>
#include <macro.h>

#include "varNumberNode.h"
#include "constNumberNode.h"

vl::varNumberNode::varNumberNode(std::string name, vl::ihandle* engine) : vl::node(name, vl::to_integer(vl::objectType::VL_NUMBER), false, engine){

	try {
		this->setConst(false);

		this->registerNode("condition", vl::to_integer(vl::objectType::VL_CONST_FLOW), vl::searchType::input);
		this->registerNode("input", vl::to_integer(vl::objectType::VL_CONST_NUMBER), vl::searchType::input);


		this->registerNode("condition", vl::to_integer(vl::objectType::VL_CONST_FLOW), vl::searchType::output);
		this->registerNode("output", vl::to_integer(vl::objectType::VL_CONST_NUMBER), vl::searchType::output);


		//parse preparation
		this->property<double>("input", [&]() {
			return this->input<vl::constNumberNode>("input")->get();
		});

		this->property<double>("input", [&](double value) {
			this->input<vl::constNumberNode>("input")->set(value);
		});

	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}


vl::varNumberNode::~varNumberNode() {

}

void vl::varNumberNode::init() {
	try {

		//노드 초기화 시에 호출됨!!
		auto input = this->searchNode<vl::constNumberNode>("input", vl::searchType::input);
		auto output = this->searchNode<vl::constNumberNode>("output", vl::searchType::output);

		input->set(0);
		output->set(0);
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
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


void vl::varNumberNode::primitive(vl::pointer_argument arg) {

}
