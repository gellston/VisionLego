#pragma once

#ifndef VL_NODE_INFO
#define VL_NODE_INFO


#include <string>
#include <memory>

#include "argument.h"

namespace vl {

	class impl_info;
	class info {

	private:
		std::unique_ptr<impl_info> _instance;

	public:

		info(std::string name, pointer_argument arg);
		~info();

		std::string name();
		std::string category();
		int type();


	};

	using pointer_info = std::shared_ptr<vl::info>;
}

#endif