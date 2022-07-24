#pragma once


#ifndef VL_VAR_NUMBER_NODE
#define VL_VAR_NUMBER_NODE



#include <node.h>


namespace vl {
	class varNumberNode;
	class varNumberNode : public vl::node {
	private:
	public:

		varNumberNode(std::string name, vl::ihandle* engine);
		~varNumberNode() override;

		void init() override;
		void preprocess() override;
		void process() override;
		void onUpdatePrimitive() override;
		void changePrimitive(vl::pointer_property prop) override;

	};
}

#endif