#pragma once


#include <node.h>


namespace vl{
	class impl_boolNode;
	class boolNode : vl::node {
	private:
		std::unique_ptr<impl_boolNode> _instance;
	public:

		boolNode(std::string name, smrtengine engine);
		~boolNode() override;

		void set(bool data);
		bool get();

		void preprocess() override;
		void process() override;

	};
}