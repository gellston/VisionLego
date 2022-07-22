#pragma once

#ifndef VL_IENGINE
#define VL_IENGINE


#include "inode.h"
#include "iaddon.h"
#include "ihandle.h"

namespace vl {

	class iengine : public vl::ihandle {
	public:
		virtual ~iengine() {};
		virtual pointer_inode find(unsigned long long uid, std::string key, unsigned int depth) = 0;
		virtual pointer_inode find(unsigned long long uid) = 0;
		virtual pointer_inode create(std::string name, int objectType) = 0;
		virtual bool checkDepth(unsigned long long uid, unsigned int depth) = 0;
		virtual void registerAddon(pointer_iaddon addon) = 0;
		virtual void depthUpdate(unsigned int depth) = 0;
		virtual void depthAlign() = 0;
		virtual void depthSorting() = 0;
		virtual std::vector<unsigned long long> searchInputUID(unsigned long long inputUid, unsigned int depth) = 0;


		
	};

	using pointer_iengine = std::shared_ptr<vl::iengine>;
}

#endif