#pragma once


#include <node.h>


namespace vl {
	class varBoolNode : vl::node {
	private:
	public:

		varBoolNode(std::string name, smrtengine engine);
		~varBoolNode() override;

		void init() override;
		void preprocess() override;
		void process() override;
	};
}