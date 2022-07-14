#pragma once

#ifndef VL_CONSTRUCTOR
#define VL_CONSTRUCTOR


#include "iconstructor.h"

namespace vl {

	template<typename T> struct constructor : public vl::iconstructor  {
	public:
		constructor() { }
		virtual ~constructor() override { }

		std::shared_ptr<vl::inode> create(std::string name, vl::ihandle * engine) override {
			return std::shared_ptr<vl::inode>(new T(name, engine));
		}
	};
}

#endif