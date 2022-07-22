#pragma once

#ifndef VL_BINDING
#define VL_BINDING


#include <initializer_list>

#include "addon.h"
#include "iengine.h"

#ifndef VL_ADDON_BINDING
#define VL_ADDON_EXPORT __declspec(dllimport)
#else
#define VL_ADDON_EXPORT __declspec(dllexport)
#endif



#define VL_ADDON_INIT extern "C" VL_ADDON_EXPORT void vl_init


#define VL_VERSION(version)\
extern "C" VL_ADDON_EXPORT const char* vl_version() {\
\
	return version; \
}\

#define VL_NAME(name)\
extern "C" VL_ADDON_EXPORT const char* vl_name() {\
\
	return name; \
}\

#define VL_MODULE \
extern "C" VL_ADDON_EXPORT bool vl_module() {\
\
	return true; \
}\








#endif