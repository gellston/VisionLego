#pragma once

#ifndef VL_NODE
#define VL_NODE

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

namespace vl {

	//외부 입력 노드			  //Type,       Name,     상수 노드 ,   상수노드 사용 유무,  uid
	using input_node = std::tuple<int, std::string, pointer_node, unsigned long long>;

	//상수 입력 노드			  // Type,      Name,         Node
	//using input_const = std::tuple<std::string, std::string, pointer_node>;

	//출력 노드					  // Type,      Name,        Node
	using output_node = std::tuple<int, std::string, pointer_node>;



	class node;
	using pointer_node = std::shared_ptr<node>;
	class node {

	private:
		unsigned long long _uid;
		unsigned int _depth;
		std::string _name;
		int _type;									// scheme

		std::vector<input_node> _inputNode; 				// scheme
		std::vector<output_node> _outputNode; 				// scheme


		std::unordered_map<unsigned long long, pointer_node> _table; // Table
	public:
		node(std::string name, int);
		~node();

		//void setHashTable(std::unordered_map<unsigned long long, pointer_node> table);



		int type();

		std::string name();
		void name(std::string name);

		unsigned long long uid();
		void uid(unsigned long long value);

		unsigned int depth();
		void depth(unsigned int depth);


	};

}

#endif
