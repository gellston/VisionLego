#pragma once

#ifndef VL_IADDON
#define VL_IADDON


#include <memory>
#include <string>


#include "node.h"
#include "iconstructor.h"
#include "nodeInfo.h"
#include "ihandle.h"

namespace vl {

	class iaddon;
	class iaddon : public vl::ihandle {
	private:


	public:
		virtual ~iaddon(){}
		virtual bool exist(int type) = 0;
		virtual std::shared_ptr<vl::iconstructor> find(int type) = 0;
		virtual std::vector<pointer_nodeInfo> information() = 0;
	};

	using pointer_iaddon = std::shared_ptr<iaddon>;
}

#endif