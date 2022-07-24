#pragma once


#ifndef VL_CONST_NUMBER_NODE
#define VL_CONST_NUMBER_NODE



#include <node.h>


namespace vl {
	class impl_constNumberNode;
	class constNumberNode;
	class constNumberNode : public vl::node {
	private:
		std::unique_ptr<impl_constNumberNode> _data;
	public:

		constNumberNode(std::string name, vl::ihandle* engine);
		~constNumberNode() override;

		void set(double data);
		double get();

		void init() override;
		void preprocess() override;
		void process() override;
		void onUpdatePrimitive() override;
		void changePrimitive(vl::pointer_property prop) override;

	};
}

#endif