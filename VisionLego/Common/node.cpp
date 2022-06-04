#include "node.h"


vl::node::node(std::string name, int type) {


	this->_name = name;
	this->_type = type;

	this->_uid = 0;
	this->_depth = 0;
}

vl::node::~node() {


}


unsigned long long vl::node::uid() {

	return this->_uid;
}

void vl::node::uid(unsigned long long value) {
	this->_uid = value;
}

std::string vl::node::name() {

	return this->_name;

}

void vl::node::name(std::string _name) {
	this->_name = _name;
}

int vl::node::type() {

	return this->_type;
}

unsigned int vl::node::depth() {

	return this->_depth;
}


void vl::node::depth(unsigned int depth) {
	this->_depth = depth;
}

