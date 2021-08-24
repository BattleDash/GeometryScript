#pragma once

#include <vector>

#include "node_instance.h"

namespace GeometryScript::Executor
{
	class NodeManager
	{
	public:
		NodeManager();
		~NodeManager();

		NodeInstance* CreateInstance();

		std::vector<NodeInstance*> instances;
	};
}

extern GeometryScript::Executor::NodeManager* gNodeManager;