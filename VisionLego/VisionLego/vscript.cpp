#include "vscript.h"



#include <node.h>
#include <unordered_map>
#include <vlexception.h>
#include <filesystem>
#include <macro.h>
#include <Windows.h>

#include <iconstructor.h>

namespace vl {
	class impl_vscript {
	public:

		std::unordered_map<unsigned long long, pointer_node> _nodes_table;
		std::unordered_map<std::string, HMODULE> _addon_handles;
		std::string _libraryPath;
		std::vector<std::shared_ptr<vl::iaddon>> _addons;

		impl_vscript() {

		}

		~impl_vscript() {

		}
	};
}



vl::vscript::vscript() : _instance(new vl::impl_vscript()) {

}


vl::vscript::~vscript() {

}




void vl::vscript::setAddonPath(std::string path) {

	if (std::filesystem::exists(path) == false) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Addon path is not exists");
		throw vl::exception(message);
	}

	this->_instance->_libraryPath = path;

}

void vl::vscript::loadLibrary() {

	if (this->_instance->_addon_handles.size() > 0) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "library is already loaded.");
		throw vl::exception(message);
	}

	for (const auto& entry : std::filesystem::directory_iterator(this->_instance->_libraryPath)) {
		if (entry.path().extension().string() == ".dll") {
			std::string filePath = entry.path().string();
			std::string fileName = entry.path().filename().string();
			bool check = false;
			HMODULE module = LoadLibraryA(filePath.c_str());
			if (module != nullptr) {

				try {

	/*				auto vl_version = (const char* (*)())GetProcAddress(module, "vl_version");
					auto vl_name = (const char* (*)())GetProcAddress(module, "vl_name");
					auto vl_module = (bool (*)())GetProcAddress(module, "vl_module");
					auto vl_init = (void (*)(vl::iengine*))GetProcAddress(module, "vl_module");

					if (vl_version == nullptr || vl_name == nullptr || vl_module == nullptr || vl_init == nullptr) {
						FreeLibrary(module);
						continue;
					}

					if (vl_module() == false) {
						FreeLibrary(module);
						continue;
					}


				*/


					this->_instance->_addon_handles[fileName] = module;
				}
				catch (std::exception e) {
					FreeLibrary(module);
				}
			}
		}
	}
}


void vl::vscript::unloadLibrary() {

	std::vector <std::string> removedkey;
	bool error = false;
	try {
		for (auto& pair : this->_instance->_addon_handles) {
			if ((bool)FreeLibrary(pair.second) == true) {
				removedkey.push_back(pair.first);
			}
			else {
				error = true;
			}
		}

		for (auto& key : removedkey) {
			this->_instance->_addon_handles.erase(key);
		}

		if (error) {
			std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, "Unexpected error detected. please check addon");
			throw vl::exception(message);
		}
	}
	catch (vl::exception e) {
		throw e;
	}
	catch (std::exception e) {
		std::string message = vl::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw vl::exception(message);
	}
}

std::vector<std::shared_ptr<vl::iaddon>> vl::vscript::addons() {

}




void vl::vscript::run() {
	try {

	}
	catch (vl::exception e) {

	}
}

void vl::vscript::compile() {

}

void vl::vscript::load(std::string context, vl::contextType type) {

}

vl::pointer_inode vl::vscript::find(unsigned long long key, int depth) {

	return nullptr;
}

vl::pointer_inode vl::vscript::create(std::string name, int objectType) {
	
	return nullptr;
}

void vl::vscript::addNode(std::string name, int objectType) {

}

bool vl::vscript::exist(unsigned long long key, int depth) {

	return false;
}


void vl::vscript::registerAddon(std::shared_ptr<vl::iaddon> addon) {
	this->_instance->_addons.push_back(addon);
}