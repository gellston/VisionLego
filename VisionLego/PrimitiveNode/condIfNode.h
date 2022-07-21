#pragma once


#ifndef VL_CONDITION_IF_NODE
#define VL_CONDITION_IF_NODE


#include <node.h>


namespace vl {
	class condIfNode;
	class condIfNode : public vl::node {
	private:
	public:

		condIfNode(std::string name, vl::ihandle* engine);
		~condIfNode() override;


		void init() override;
		void preprocess() override;
		void process() override;

	};
}

#endif