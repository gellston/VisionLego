#pragma once

#ifndef VL_IENGINE
#define VL_IENGINE


#include "inode.h"
#include "iaddon.h"
#include "ihandle.h"

namespace vl {
	using pointer_inode = std::shared_ptr<vl::inode>;
	class iengine : public vl::ihandle {
	public:

		virtual ~iengine() {};
		virtual pointer_inode find(unsigned long long key, int depth) = 0;
		virtual pointer_inode create(std::string name, int objectType) = 0;
		virtual bool exist(unsigned long long key, int depth) = 0;
		virtual void registerAddon(std::shared_ptr<vl::iaddon> addon) = 0;

	};

	using smrtengine = std::shared_ptr<vl::iengine>;
}

#endif