#pragma once


#include <node.h>


namespace vl {
	class varNumberNode : public vl::node {
	private:
	public:

		varNumberNode(std::string name, poiner_ihandle engine);
		~varNumberNode() override;

		void init() override;
		void preprocess() override;
		void process() override;

	};
}