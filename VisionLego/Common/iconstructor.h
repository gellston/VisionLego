#pragma once


#ifndef VL_ICONSTRUCTOR
#define VL_ICONSTRUCTOR



#include <memory>
#include <string>


#include "ihandle.h"
#include "inode.h"

namespace vl {

	class iconstructor {
	public:
		virtual ~iconstructor() {  };

		virtual std::shared_ptr<vl::inode> create(std::string name, poiner_ihandle engine) = 0;

	};
}

#endif