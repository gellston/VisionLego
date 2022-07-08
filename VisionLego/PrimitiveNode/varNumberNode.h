#pragma once


#include <node.h>


namespace vl {
	class varNumberNode : vl::node {
	private:
	public:

		varNumberNode(std::string name, smrtengine engine);
		~varNumberNode() override;

		void init() override;
		void preprocess() override;
		void process() override;
	};
}