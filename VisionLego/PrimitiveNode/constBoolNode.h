#pragma once


#ifndef VL_CONST_BOOL_NODE
#define VL_CONST_BOOL_NODE


#include <node.h>


namespace vl{
	class impl_constBoolNode;
	class constBoolNode;
	class constBoolNode : public vl::node {
	private:
		std::unique_ptr<impl_constBoolNode> _data;
	public:

		constBoolNode(std::string name, vl::ihandle* engine);
		~constBoolNode() override;

		void set(bool data);
		bool get();

		void init() override;
		void preprocess() override;
		void process() override;

	};
}

#endif