#pragma once


#ifndef VL_ICONSTRUCTOR
#define VL_ICONSTRUCTOR



#include <memory>
#include <string>


#include "ihandle.h"
#include "inode.h"

namespace vl {

	class iconstructor : public vl::ihandle {
	public:
		virtual ~iconstructor() {};
		virtual std::shared_ptr<vl::inode> create(std::string name, vl::ihandle* engine) = 0;
	};

	using pointer_iconstructor = std::shared_ptr<vl::iconstructor>;
}

#endif