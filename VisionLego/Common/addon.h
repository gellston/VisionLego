#pragma once

#ifndef VL_ADDON
#define VL_ADDON


#include <memory>
#include <string>


#include "node.h"
#include "iaddon.h"
#include "constructor.h"
#include "nodeInfo.h"

namespace vl {

	class impl_addon;
	class addon : public vl::iaddon {
	private:
		std::unique_ptr<impl_addon> _instance;
		

	protected:
		void constructor(int type, pointer_iconstructor _constructor);
		void nodeInfo(pointer_nodeInfo info);

	public:
		addon();
		virtual ~addon() override;

		bool exist(int type) override;
		std::shared_ptr<vl::iconstructor> find(int type) override;
		std::vector<pointer_nodeInfo> information() override;

		template<typename T> void add(int type, std::string category) {
			try {
				std::shared_ptr<vl::iconstructor> constructor(new vl::constructor<T>());
				this->constructor(type, constructor);

				pointer_argument arg(new vl::argument());
				arg->add("category", category);
				arg->add("type", type);

				pointer_nodeInfo info(new vl::nodeInfo(typeid(T).name(), arg));
				this->nodeInfo(info);
			}
			catch (vl::exception e) {
				throw e;
			}
		}

		static std::shared_ptr<vl::addon> createAddon();
	};

	using pointer_addon = std::shared_ptr<addon>;
}

#endif