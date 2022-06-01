#include "node.h"


vl::node::node(std::string name, std::string type, unsigned long long uid) {

}

vl::node::~node() {


}
unsigned long long vl::node::uid() {

	return this->_uid;
}

std::string vl::node::name() {

	return this->_name;

}

std::string vl::node::type() {

	return this->_type;
}