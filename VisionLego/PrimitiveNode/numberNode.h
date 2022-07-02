#pragma once


#include <node.h>


namespace vl {
	class impl_numberNode;
	class numberNode : vl::node {
	private:
		std::unique_ptr<impl_numberNode> _instance;
	public:

		numberNode(std::string name, smrtengine engine;
		~numberNode() override;

		void set(double data);
		double get();

	};
}