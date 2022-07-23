#include "property.h"

#include "macro.h"
#include "vlexception.h"


#include <unordered_map>



namespace vl {

	class impl_property {
	public:


		
		std::unordered_map<std::string, std::unordered_map<std::string, std::string>> _data_table;



		impl_property() {


			this->_data_table["int"];
			this->_data_table["double"];
			this->_data_table["string"];
			this->_data_table["bool"];

		}

		~impl_property() {


		}
	};
}



vl::property::property() : _instance(new vl::impl_property()) {

}

vl::property::~property() {


}

int vl::property::get(std::string key, int dummy = 0) {
	if(this->check("int", key) == false) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Type or key is not exist");
		throw vl::exception(message);
	}


	return 6;
}
double vl::property::get(std::string key, double dummy = 0) {
	if (this->check("double", key) == false) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Type or key is not exist");
		throw vl::exception(message);
	}
}
std::string vl::property::get(std::string key, std::string dummy = "") {
	if (this->check("string", key) == false) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Type or key is not exist");
		throw vl::exception(message);
	}
}
bool vl::property::get(std::string key, bool dummy = false) {
	if (this->check("bool", key) == false) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Type or key is not exist");
		throw vl::exception(message);
	}

}



bool vl::property::check(std::string type, std::string key) {

	if (this->_instance->_data_table.find("int") == this->_instance->_data_table.end()) {
		return false;
	}

	if (this->_instance->_data_table[type].find(key) == this->_instance->_data_table[type].end()) {
		return false;
	}

	return true;
}


void vl::property::set(std::string key, int value) {

}
void vl::property::set(std::string key, double value) {

}
void vl::property::set(std::string key, std::string value) {

}
void vl::property::set(std::string key, bool value) {

}


void vl::property::parse(std::string key, std::string type, std::string value) {

}