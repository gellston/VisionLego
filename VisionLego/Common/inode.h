#pragma once

#ifndef VL_INODE
#define VL_INODE

#include <string>
#include <memory>

#include "ihandle.h"

namespace vl {
	using input_info = std::tuple<std::string, int>;
	using output_info = std::tuple<std::string, int>;
	class inode : public vl::ihandle {
	public:
		virtual ~inode() {};
		virtual int type() = 0;
		virtual std::string name() = 0;
		virtual unsigned long long uid() = 0;
		virtual unsigned int depth() = 0;

		virtual bool error() = 0;
		virtual std::string message() = 0;
		virtual bool isConst() = 0;
		virtual bool inCondition() = 0;
		virtual void setInCondition(bool check) = 0 ;
		virtual void checkConnectivity() = 0;

		virtual void name(std::string name) = 0;
		virtual void uid(unsigned long long value) = 0;
		virtual void depth(unsigned int depth) = 0;


		virtual void init() = 0;
		virtual void preprocess() = 0;
		virtual void process() = 0;


		virtual std::shared_ptr<vl::inode> input(std::string key) = 0;
		virtual std::shared_ptr<vl::inode> output(std::string key) = 0;
		virtual std::vector<std::string> condition() = 0;
		virtual void runCondition(std::string key) = 0;
		
		virtual std::vector<input_info> input() = 0;
		virtual std::vector<output_info> output() = 0;
		virtual std::vector<unsigned long long> inputUid() = 0;
		virtual std::vector<unsigned long long> outputUid() = 0;

		virtual void connect(std::string outkey, unsigned long long outUid, std::string inkey) = 0;
		virtual void connect(std::shared_ptr<vl::inode> outNode, std::string outKey, std::string inkey) = 0;
		virtual void disconnect(std::string inKey) = 0;
		virtual void addInCondition(std::string name, unsigned long long uid) = 0;
		virtual void addInCondition(std::string name, std::shared_ptr<vl::inode> node) = 0;

		virtual void removeInCondtion(std::string name, unsigned long long uid) = 0;
		virtual void removeInCondtion(std::string name, std::shared_ptr<vl::inode> node) = 0;

	
	};

	using pointer_inode = std::shared_ptr<vl::inode>;
}

#endif

