#pragma once

#ifndef VL_NODE
#define VL_NODE

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>


#include "vlenum.h"
#include "iengine.h"
#include "inode.h"
#include "vlexception.h"

namespace vl {

	class node;

	using pointer_node = std::shared_ptr<node>;

							    //type,상수 노드, 상수 노드 사용 유무,  uid
	using input_node = std::tuple<int, pointer_node, bool, unsigned long long>;
	using output_node = std::tuple<int, pointer_node>;
	using smrtengine = std::shared_ptr<vl::iengine>;
	using unique = unsigned long long;

	class impl_node;
	class node : public inode {

	private:

		std::unique_ptr<impl_node> _instance;

	protected:

		void registerNode(std::string name, int objectType,  vl::searchType type);
		pointer_node searchNode(std::string name, vl::searchType type);
		template<typename T> std::shared_ptr<T> searchNode(std::string name, vl::searchType type) {
			try {
				auto node = this->searchNode(name, type);
				return std::dynamic_pointer_cast<T>(node);
			}
			catch (vl::exception e) {
				throw e;
			}
		}

		void setConst(bool isConst);
		virtual void init() = 0;
		virtual void preprocess() = 0;
		virtual void process() = 0;

	public:

		node(std::string name, int type, bool isConst, smrtengine engine);
		virtual ~node();

		int type();
		std::string name();
		unique uid();
		unsigned int depth();

		bool isConst();

		bool error();
		std::string message();

		void name(std::string name);
		void uid(unique value);
		void depth(unsigned int depth);

		void check();
	};

}

#endif
