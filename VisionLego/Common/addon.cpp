#include "addon.h"


#include "iconstructor.h"
#include "macro.h"

namespace vl {
	class impl_addon {
	public:

		std::unordered_map<int, std::shared_ptr<vl::iconstructor>> _table;
		std::vector<vl::pointer_nodeInfo> _information;

		impl_addon() {

		}

		~impl_addon() {

		}

	};
}



vl::addon::addon() : _instance(new vl::impl_addon()) {

}

vl::addon::~addon() {

}

bool vl::addon::exist(int type) {

	if (this->_instance->_table.find(type) == this->_instance->_table.end()) {
		return false;
	}
	return true;
}


std::shared_ptr<vl::iconstructor> vl::addon::find(int type) {

	if (this->_instance->_table.find(type) == this->_instance->_table.end()) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Type is not exist");
		throw vl::exception(message);
	}

	try {

		return this->_instance->_table[type];

	}
	catch (vl::exception e) {
		throw e;
	}
}

void vl::addon::constructor(int type, pointer_iconstructor _constructor) {

	if (this->_instance->_table.find(type) != this->_instance->_table.end()) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Type already exist in this addon");
		throw vl::exception(message);
	}
	
	this->_instance->_table[type] = _constructor;
}

void  vl::addon::nodeInfo(pointer_nodeInfo info) {
	this->_instance->_information.push_back(info);
}

std::shared_ptr<vl::addon> vl::addon::createAddon() {
	std::shared_ptr<vl::addon> _addon(new vl::addon());
	return _addon;
}

std::vector<vl::pointer_nodeInfo> vl::addon::information() {
	return this->_instance->_information;
}