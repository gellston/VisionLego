#pragma once

#ifndef VL_NODE
#define VL_NODE

#include <string>

namespace vl {
	class node {

	private:
		unsigned long long _uid;
		std::string _name;
		std::string _type;

	public:
		node(std::string name, std::string type, unsigned long long uid);
		~node();

		unsigned long long uid();
		std::string name();
		std::string type();

	};
}

#endif
