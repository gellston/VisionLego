#pragma once

#ifndef VL_NODE
#define VL_NODE

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <functional>


#include "vlenum.h"
#include "ihandle.h"
#include "inode.h"
#include "vlexception.h"
#include "property.h"

namespace vl {

	class node;

	using pointer_node = std::shared_ptr<node>;
	using weak_pointer_node = std::weak_ptr<node>;

							    //type, 상수 노드, 상수 노드 사용 유무,  uid,  param 이름(output이름)
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
		void registerCondition(std::string name);


		
		


	public:

		node(std::string name, int type, bool isConst, vl::ihandle* engine);
		virtual ~node();

		int type() override;
		std::string name() override;
		unique uid() override;
		unsigned int depth() override;
		bool isConst() override;
		bool inCondition() override;
		void setInCondition(bool check) override;
		void checkConnectivity() override;


		void primitive(pointer_property prop);
		pointer_property primitive();
		


		//Find const node
		std::shared_ptr<vl::inode> input(std::string key) override;
		std::shared_ptr<vl::inode> output(std::string key) override;
		template<typename T> std::shared_ptr<T> input(std::string name) {
			return std::dynamic_pointer_cast<T>(this->input(name));
		}


		//Get node information
		std::vector<input_info> input() override;
		std::vector<output_info> output() override;
		std::vector<std::string> condition() override;

		//Get uids if its connected node
		std::vector<unsigned long long> inputUid() override;
		std::vector<unsigned long long> outputUid() override;
		

		void connect(std::string outkey, unsigned long long outUid, std::string inkey) override;
		void connect(pointer_inode outNode, std::string outKey, std::string inkey) override;
		void disconnect(std::string inKey) override;
		void addInCondition(std::string name, unsigned long long uid) override;
		void addInCondition(std::string name, pointer_inode node) override;

		void removeInCondtion(std::string name, unsigned long long uid) override;
		void removeInCondtion(std::string name, pointer_inode node) override;


		void runCondition(std::string key) override;


		void name(std::string name);
		void uid(unique value);
		void depth(unsigned int depth);

		std::string serialization() override;
		std::string beautify() override;
		void parse(std::string content) override;
	};

}

#endif
