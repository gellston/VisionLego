#pragma once

#ifndef VL_MACRO
#define VL_MACRO


#include <string>


namespace vl {

	inline std::string generate_error_message(const char* function_name, int line, std::string _context) {
		std::string full_context = "";
		full_context += "==========================\n";
		full_context += function_name;
		full_context += ":";
		full_context += std::to_string(line);
		full_context += ":";
		full_context += "\n";
		full_context += _context;
		full_context += "\n";
		full_context += "==========================\n";
		return full_context;
	}





}

#endif