#pragma once

#include "node/node.h"
#include "node/v8.h"

namespace GeometryScript::Executor
{
	class NodeInstance
	{
	public:
		NodeInstance(node::MultiIsolatePlatform* platform,
			const std::vector<std::string>& args,
			const std::vector<std::string>& exec_args);
		~NodeInstance();
	};
}