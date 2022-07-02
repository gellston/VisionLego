#pragma once

#ifndef VL_INODE
#define VL_INODE

#include <string>

namespace vl {
	class inode {
	public:
		virtual ~inode() {};
		virtual int type() = 0;
		virtual std::string name() = 0;
		virtual unsigned long long uid() = 0;
		virtual unsigned int depth() = 0;
	};
}

#endif

