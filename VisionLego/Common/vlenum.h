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
		VL_CONST_BOOL,
		VL_CONST_NUMBER,


		VL_VARIABLE = 4000,
		VL_BOOL,
		VL_NUMBER


	};

	enum class contextType {
		file,
		json
	};


	const int non_type = 0;
	const int empty_depth = 0;
	const int non_uid = 0;




}


#endif