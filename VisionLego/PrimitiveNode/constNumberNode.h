#pragma once


#include <node.h>


namespace vl {
	class impl_constNumberNode;
	class constNumberNode : public vl::node {
	private:
		std::unique_ptr<impl_constNumberNode> _instance;
	public:

		constNumberNode(std::string name, vl::ihandle* engine);
		~constNumberNode() override;

		void set(double data);
		double get();

		void init() override;
		void preprocess() override;
		void process() override;

	};
}