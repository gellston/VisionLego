#pragma once



#ifndef VL_IENGINE
#define VL_IENGINE


#include "inode.h"


namespace vl {

	

	using pointer_inode = std::shared_ptr<vl::inode>;
	class iengine {
	public:

		virtual ~iengine() {};
		virtual pointer_inode find(unsigned long long key, int depth) = 0;
		virtual bool exist(unsigned long long key, int depth) = 0;

	};
}

#endif