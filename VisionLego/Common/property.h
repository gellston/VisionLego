#pragma once


#ifndef VL_PROPERTY
#define VL_PROPERTY

#include <memory>
#include <iostream>


namespace vl {
	class impl_property;
	class property {

	private:
		std::unique_ptr<vl::impl_property> _instance;
		bool check(std::string type, std::string key);
	public:
		property();
		~property();

		int get(std::string key, int dummy = 0);
		double get(std::string key, double dummy = 0);
		std::string get(std::string key, std::string dummy = "");
		bool get(std::string key, bool dummy = false);

		void set(std::string key, int value);
		void set(std::string key, double value);
		void set(std::string key, std::string value);
		void set(std::string key, bool value);


		void parse(std::string key, std::string type, std::string value);


	};
}


#endif