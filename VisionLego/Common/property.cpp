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

template<> int vl::property::get(std::string key, int dummy) {
	if(this->check("int", key) == false) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Type or key is not exist");
		throw vl::exception(message);
	}

	try {


		return std::stoi(this->_instance->_data_table["int"]["key"]);
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}
template<> double vl::property::get(std::string key, double dummy) {
	if (this->check("double", key) == false) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Type or key is not exist");
		throw vl::exception(message);
	}
	try {


		return std::stod(this->_instance->_data_table["double"]["key"]);
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}
template<> std::string vl::property::get(std::string key, std::string dummy) {
	if (this->check("string", key) == false) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Type or key is not exist");
		throw vl::exception(message);
	}
	try {


		return this->_instance->_data_table["double"]["key"];
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}
template<> bool vl::property::get(std::string key, bool dummy) {
	if (this->check("bool", key) == false) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Type or key is not exist");
		throw vl::exception(message);
	}
	try {

		if (this->_instance->_data_table["bool"][key] == "true")
			return true;
		else return false;
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}



bool vl::property::check(std::string type, std::string key) {

	if (this->_instance->_data_table.find(type) == this->_instance->_data_table.end()) {
		return false;
	}

	if (this->_instance->_data_table[type].find(key) == this->_instance->_data_table[type].end()) {
		return false;
	}

	return true;
}


void vl::property::set(std::string key, int value) {
	try {

		this->_instance->_data_table["int"][key] = std::to_string(value);
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}
void vl::property::set(std::string key, double value) {
	try {

		this->_instance->_data_table["double"][key] = std::to_string(value);
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}
void vl::property::set(std::string key, std::string value) {
	try {

		this->_instance->_data_table["string"][key] = value;
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}
void vl::property::set(std::string key, bool value) {
	try {
		if(value)
			this->_instance->_data_table["bool"][key] = "true";
		else
			this->_instance->_data_table["bool"][key] = "false";
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}


void vl::property::parse(std::string type, std::string key,  std::string value) {
	this->_instance->_data_table[type][key] = value;
}


std::vector<vl::property_data> vl::property::table() {
	std::vector<property_data> _data;

	for (auto type : this->_instance->_data_table) {
		std::string type_name = type.first;
		auto keys = type.second;
		for (auto key : keys) {
			std::string key_name = key.first;
			auto value = key.second;
			_data.push_back(std::make_tuple(type_name, key_name, value));
		}
	}
	
	return _data;
}


void vl::property::clear() {
	this->_instance->_data_table.clear();
}