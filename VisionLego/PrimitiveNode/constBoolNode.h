#pragma once


#include <node.h>


namespace vl{
	class impl_constBoolNode;
	class constBoolNode : vl::node {
	private:
		std::unique_ptr<impl_constBoolNode> _instance;
	public:

		constBoolNode(std::string name, smrtengine engine);
		~constBoolNode() override;

		void set(bool data);
		bool get();

		void init() override;
		void preprocess() override;
		void process() override;

	};
}