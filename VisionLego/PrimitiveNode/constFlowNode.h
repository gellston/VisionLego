#pragma once


#ifndef VL_CONST_FLOW_NODE
#define VL_CONST_FLOW_NODE


#include "node.h"

namespace vl {

	class constFlowNode;
	class constFlowNode : public vl::node {
	private:

	public:

		constFlowNode(std::string name, vl::ihandle* engine);
		~constFlowNode() override;

		void init() override;
		void preprocess() override;
		void process() override;

	};
}

#endif