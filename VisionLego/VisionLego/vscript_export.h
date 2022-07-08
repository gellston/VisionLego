#pragma once

#ifndef VL_VSCRIPT_EXPORT
#define VL_VSCRIPT_EXPORT


#ifndef VL_SCRIPT_API
#define VL_SCRIPT_EXPORT __declspec(dllimport)
#else
#define VL_SCRIPT_EXPORT __declspec(dllexport)
#endif



#endif