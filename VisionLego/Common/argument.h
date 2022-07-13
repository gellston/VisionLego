#pragma once


#ifndef VL_ARGUMENT
#define VL_ARGUMENT

#include <string>
#include <memory>
#include <initializer_list>
#include <tuple>
#include <variant>


#include "vlexception.h"

namespace vl {

	using arg = std::variant<bool, std::string, double, int>;

	class impl_argument;
	class argument {
	private:

		std::unique_ptr<impl_argument> _instance;
	public:

		argument();
		argument(std::initializer_list<std::tuple <std::string, arg>> list);
		~argument();


		template<typename T> T get(std::string key){}
		template<typename T> T get(const char* key) {
			try {
				return this->get<T>(std::string(key));
			}
			catch (vl::exception e) {
				throw e;
			}
		}

		template<> double get(std::string key);
		template<> int get(std::string key);
		template<> std::string get(std::string key);
		template<> bool get(std::string key);

		template<typename T> void add(std::string key, T value){}
		template<typename T> void add(const char* key, T value) {
			try {

			}
			catch (vl::exception e) {
				throw e;
			}
		}
		template<> void add(std::string key, double value);
		template<> void add(std::string key, int value);
		template<> void add(std::string key, bool value);
		template<> void add(std::string key, std::string value);
		template<> void add(std::string key, const char* value);

		std::string parse();
		void print();

	};

	using pointer_argument = std::shared_ptr<argument>;

}



#endif