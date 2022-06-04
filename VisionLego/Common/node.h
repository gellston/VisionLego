#pragma once

#ifndef VL_NODE
#define VL_NODE

#include <string>
#include <memory>
#include <vector>

namespace vl {

	using input_info = std::tuple<std::string, unsigned long long>;
	using output_info = std::tuple<std::string, unsigned long long>;



	class node;
	using pointer_node = std::shared_ptr<node>;
	class node {

	private:
		unsigned long long _uid;
		unsigned int _depth;
		std::string _name;
		std::string _type;

		std::vector<input_info> _input;
		std::vector<output_info> _output;

	public:
		node(std::string name, std::string type);
		~node();

		std::string type();

		std::string name();
		void name(std::string name);

		unsigned long long uid();
		void uid(unsigned long long value);

		unsigned int depth();
		void depth(unsigned int depth);

	};

}

#endif
