#pragma once

#ifndef VL_ENUM
#define VL_ENUM


namespace vl {
	enum class searchType{
		input,
		output
	};

	enum class objectType {

		VL_CONST = 0,
		VL_CONST_FLOW,
		VL_CONST_BOOL,
		VL_CONST_NUMBER,


		VL_VARIABLE = 4000,
		VL_BOOL,
		VL_NUMBER,


		VL_CONDITION = 8000,
		VL_IF,


		VL_FUNCTION = 12000,
	};

	enum class contextType {
		file,
		json
	};


	const int non_type = 0;
	const int empty_depth = 0;
	const int non_uid = 0;




}

namespace vl {
	inline int to_integer(vl::objectType type) {
		return static_cast<int>(type);
	}
}

#endif