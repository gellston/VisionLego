#pragma once


#ifndef VL_VSCRIPT
#define VL_VSCRIPT


#include <unordered_map>


#include <node.h>

namespace vl {
	class vscript;
	using pointer_vscript = std::shared_ptr<vscript>;
	class vscript {

	private:

		std::unordered_map<unsigned long long, pointer_node> _nodes_table;

		
	public:


		vscript();
		~vscript();


		std::vector<pointer_node> allNodes();

		void checkNodeExist(std::string name, std::string type);
		void createNode(std::string name, std::string type);
		void insertNode(pointer_node node);
		void deleteNode(pointer_node node);
		void deleteNode(unsigned long long uid);
		pointer_node searchNode(pointer_node node);
		pointer_node searchNode(unsigned long long uid);


	};

}

#endif