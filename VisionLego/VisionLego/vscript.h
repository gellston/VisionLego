#pragma once

#ifndef VL_VSCRIPT
#define VL_VSCRIPT

#include <memory>
#include <iengine.h>
#include <vlenum.h>


#include "vscript_export.h"

namespace vl {
	class impl_vscript;
	class vscript;
	using pointer_vscript = std::shared_ptr<vscript>;
	class vscript : public vl::iengine {

	private:

		std::unique_ptr<impl_vscript> _instance;

		
	public:
		VL_SCRIPT_EXPORT vscript();
		VL_SCRIPT_EXPORT ~vscript() override;


		VL_SCRIPT_EXPORT void loadLibrary();
		VL_SCRIPT_EXPORT void unloadLibrary();
		VL_SCRIPT_EXPORT void setAddonPath(std::string path);
		VL_SCRIPT_EXPORT void load(std::string context, vl::contextType type);
		VL_SCRIPT_EXPORT void compile();
		VL_SCRIPT_EXPORT void run();
	
		VL_SCRIPT_EXPORT pointer_inode find(unsigned long long key, int depth) override;
		VL_SCRIPT_EXPORT pointer_inode create(std::string name, int objectType) override;
		VL_SCRIPT_EXPORT bool exist(unsigned long long key, int depth) override;
		VL_SCRIPT_EXPORT void addNode(std::string name, int objectType);
	};

}

#endif