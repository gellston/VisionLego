#pragma once


#include <node.h>


namespace vl {
	class varBoolNode : public vl::node {
	private:
	public:

		varBoolNode(std::string name, vl::ihandle* engine);
		~varBoolNode() override;

		void init() override;
		void preprocess() override;
		void process() override;


	};
}