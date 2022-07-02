#pragma once

#ifndef VL_EXCEPTION
#define VL_EXCEPTION


#include <stdexcept>

namespace vl {

	class exception : public std::runtime_error {
	public:
		exception() : std::runtime_error("") {}
		exception(const std::string& message = "") : std::runtime_error(message) {}
	};



}

#endif