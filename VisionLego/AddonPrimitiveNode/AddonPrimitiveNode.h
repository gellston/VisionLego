#pragma once

#include "binding.h"

#include <varBoolNode.h>
#include <varNumberNode.h>
#include <constBoolNode.h>
#include <constNumberNode.h>


VL_MODULE
VL_NAME("PrimitiveNode")
VL_VERSION("1.0")
VL_ADDON_INIT(engine){

	auto _addon = vl::addon::createAddon();
	_addon->add<vl::varBoolNode>((int)vl::objectType::VL_BOOL, "Primitive");
	_addon->add<vl::varNumberNode>((int)vl::objectType::VL_NUMBER, "Primitive");
	_addon->add<vl::constBoolNode>((int)vl::objectType::VL_CONST_BOOL, "Primitive");
	_addon->add<vl::constNumberNode>((int)vl::objectType::VL_CONST_NUMBER, "Primitive");

	engine->registerAddon(_addon);
}
