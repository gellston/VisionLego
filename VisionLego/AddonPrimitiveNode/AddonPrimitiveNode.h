#pragma once

#include "binding.h"

#include <varBoolNode.h>
#include <varNumberNode.h>
#include <constBoolNode.h>
#include <constNumberNode.h>
#include <constFlowNode.h>
#include <condIfNode.h>


VL_MODULE
VL_NAME("PrimitiveNode")
VL_VERSION("1.0")
VL_ADDON_INIT(vl::iengine* engine)
{
	try {
		auto _addon = vl::addon::createAddon();
		_addon->add<vl::varBoolNode>(vl::to_integer(vl::objectType::VL_BOOL), "Basic");
		_addon->add<vl::varNumberNode>(vl::to_integer(vl::objectType::VL_NUMBER), "Basic");
		_addon->add<vl::constBoolNode>(vl::to_integer(vl::objectType::VL_CONST_BOOL), "Basic");
		_addon->add<vl::constNumberNode>(vl::to_integer(vl::objectType::VL_CONST_NUMBER), "Basic");
		_addon->add<vl::constFlowNode>(vl::to_integer(vl::objectType::VL_CONST_FLOW), "Basic");
		_addon->add<vl::condIfNode>(vl::to_integer(vl::objectType::VL_IF), "Flow");
		engine->registerAddon(_addon);
	}
	catch (std::exception e) {
		
	}
}
