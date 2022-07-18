#pragma once

#ifndef VL_EXCEPTION
#define VL_EXCEPTION


#include <stdexcept>

namespace vl {

	class exception : public std::runtime_error {
	public:
		exception(const std::string& message = "") : std::runtime_error(message) {}
	};

	class recursivGraphException : vl::exception {
		recursivGraphException(const std::string& message = "") : vl::exception(message) {}
	};

}

#endif