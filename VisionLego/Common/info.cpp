#include "info.h"

#include "vlenum.h"


namespace vl {
	class impl_info {
	public:
		impl_info() {
			this->name = "";
			this->category = "";
			this->type = vl::non_type;
		}

		~impl_info() {

		}

		std::string name;
		std::string category;
		int type;

	};
}

vl::info::info(std::string name, pointer_argument arg) : _instance(new vl::impl_info()) {


	try {
		this->_instance->name = name;
		this->_instance->category = arg->get<std::string>("category");
		this->_instance->type = arg->get<int>("type");
	}
	catch (vl::exception e) {
		throw e;
	}

}

vl::info::~info() {

}

std::string vl::info::category() {
	return this->_instance->category;
}

std::string vl::info::name() {
	return this->_instance->name;
}

int vl::info::type() {

	return this->_instance->type;
}