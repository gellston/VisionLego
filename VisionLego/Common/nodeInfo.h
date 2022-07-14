#pragma once

#ifndef VL_NODE_INFO
#define VL_NODE_INFO


#include <string>
#include <memory>

#include "argument.h"

namespace vl {

	class impl_info;
	class nodeInfo {

	private:
		std::unique_ptr<impl_info> _instance;

	public:

		nodeInfo(std::string name, pointer_argument arg);
		~nodeInfo();

		std::string name();
		std::string category();
		int type();


	};

	using pointer_nodeInfo = std::shared_ptr<vl::nodeInfo>;
}

#endif