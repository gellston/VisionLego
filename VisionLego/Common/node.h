#pragma once

#ifndef VL_NODE
#define VL_NODE

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>


#include "vlenum.h"
#include "ihandle.h"
#include "inode.h"
#include "vlexception.h"

namespace vl {

	class node;

	using pointer_node = std::shared_ptr<node>;

							    //type, ��� ���, ��� ��� ��� ����,  uid,  param �̸�(output�̸�)
	using input_node = std::tuple<int, pointer_node, bool, unsigned long long, std::string>;
	using output_node = std::tuple<int, pointer_node>;

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

		node(std::string name, int type, bool isConst, vl::ihandle* engine);
		virtual ~node();

		int type() override;
		std::string name() override;
		unique uid() override;
		unsigned int depth() override;
		bool isConst() override;
		bool error() override;
		std::string message() override;
		void checkConnectivity() override;


		//Find const node
		std::shared_ptr<vl::inode> input(std::string key) override;
		std::shared_ptr<vl::inode> output(std::string key) override;

		//Get node information
		std::vector<input_info> input() override;
		std::vector<output_info> output() override;

		void connect(std::string outkey, unsigned long long outUid, std::string inkey) override;


		void name(std::string name);
		void uid(unique value);
		void depth(unsigned int depth);

		
	};

}

#endif
