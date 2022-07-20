#pragma once

#ifndef VL_VSCRIPT
#define VL_VSCRIPT

#include <memory>
#include <iaddon.h>
#include <vlenum.h>

#include "vscript_export.h"

namespace vl {
	class impl_vscript;
	class engine;
	using addon_info = std::tuple<std::string, std::string>;
	class vscript  {
	private:
		std::unique_ptr<impl_vscript> _instance;
		std::unique_ptr<engine> _engine;
	public:
		VL_SCRIPT_EXPORT vscript();
		VL_SCRIPT_EXPORT ~vscript();

		/*
		Procedure
		setAddonPath -> loadLibrary() -> compile (check for every node) -> run 
		*/
		VL_SCRIPT_EXPORT void loadLibrary();
		VL_SCRIPT_EXPORT void unloadLibrary();
		VL_SCRIPT_EXPORT void setAddonPath(std::string path);
		VL_SCRIPT_EXPORT std::vector<pointer_iaddon> addons();
		VL_SCRIPT_EXPORT std::vector<addon_info> addonInfo();


		VL_SCRIPT_EXPORT void load(std::string context, vl::contextType type);
		VL_SCRIPT_EXPORT void verification();
		VL_SCRIPT_EXPORT void initNodes();
		VL_SCRIPT_EXPORT void run();
	
		/*
		Graph management
		*/
		VL_SCRIPT_EXPORT vl::pointer_node addNode(std::string name, int objectType);
		VL_SCRIPT_EXPORT pointer_inode findNode(unsigned long long uid);
		VL_SCRIPT_EXPORT void clearNode();

		VL_SCRIPT_EXPORT void disconnect(pointer_inode inNode, std::string inKey);
		VL_SCRIPT_EXPORT void disconnect(unsigned long long inUid, std::string inKey);
		VL_SCRIPT_EXPORT void connect(pointer_inode outNode, std::string outKey, pointer_inode inNode, std::string inKey);
		VL_SCRIPT_EXPORT void connect(unsigned long long outUid, std::string outKey, unsigned long long inUid, std::string inKey);

		VL_SCRIPT_EXPORT void printNodeInfo();
	};

	using pointer_vscript = std::shared_ptr<vscript>;
}

#endif