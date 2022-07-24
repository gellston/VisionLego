#pragma once


#ifndef VL_PROPERTY
#define VL_PROPERTY

#include <memory>
#include <iostream>
#include <tuple>
#include <vector>

namespace vl {


	using property_data = std::tuple<std::string, std::string, std::string>;

	class impl_property;
	class property {

	private:
		std::unique_ptr<vl::impl_property> _instance;
		bool check(std::string type, std::string key);
	public:
		property();
		~property();


		template<typename T> T get(std::string key, T dummy) {
			T value;
			return value;
		}

		template<> int get<int>(std::string key, int dummy);
		template<> double get<double>(std::string key, double dummy);
		template<> std::string get<std::string>(std::string key, std::string dummy);
		template<> bool get<bool>(std::string key, bool dummy);


		void set(std::string key, int value);
		void set(std::string key, double value);
		void set(std::string key, std::string value);
		void set(std::string key, bool value);


		void parse(std::string type, std::string key, std::string value);
		std::vector<property_data> table();


		void clear();

	};


	using pointer_property = std::shared_ptr<vl::property>;
}


#endif