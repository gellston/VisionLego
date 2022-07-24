#pragma once



#ifndef VL_VAR_BOOL_NODE
#define vL_VAR_BOOL_NODE



#include <node.h>


namespace vl {
	class varBoolNode;
	class varBoolNode : public vl::node {
	private:
	public:

		varBoolNode(std::string name, vl::ihandle* engine);
		~varBoolNode() override;

		void init() override;
		void preprocess() override;
		void process() override;
		void onUpdatePrimitive() override;
		void changePrimitive(vl::pointer_property prop) override;

	};
}

#endif