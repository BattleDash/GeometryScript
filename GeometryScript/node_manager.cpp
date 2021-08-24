#include "node_manager.h"
#include <vector>
#include <string>
#include <memory>
#include "error_utils.h"
#include "node/node.h"
#include "node/v8.h"

#pragma comment(lib, "libnode.lib")

GeometryScript::Executor::NodeManager* gNodeManager;

namespace GeometryScript::Executor
{
	NodeInstance* NodeManager::CreateInstance()
	{
		// Create a v8::Platform instance. `MultiIsolatePlatform::Create()` is a way
		// to create a v8::Platform instance that Node.js can use when creating
		// Worker threads. When no `MultiIsolatePlatform` instance is present,
		// Worker threads are disabled.
		printf("Creating Instance\n");
		node::MultiIsolatePlatform* platform = node::CreatePlatform(4, nullptr);
		//std::unique_ptr<node::MultiIsolatePlatform> platform = node::MultiIsolatePlatform::Create(4);
		v8::V8::InitializePlatform(platform);
		v8::V8::Initialize();
		printf("Initialized V8\n");
		std::vector<std::string> node_argv{ "node.exe", "test.js" };
		return new NodeInstance(platform, node_argv, std::vector<std::string>());
	}

	NodeManager::NodeManager()
	{
		int argc = __argc;
		char** argv = __argv;
		// Bit of a hack here because including the libuv headers fails to compile
		//argv = ((char** (__fastcall*)(int argc, char** argv))GetProcAddress(GetModuleHandleA("libnode.dll"), "uv_setup_args"))(argc, argv);
		//std::vector<std::string> args(argv, argv + argc);

		//((int(__fastcall*)(const char* name))GetProcAddress(GetModuleHandleA("libnode.dll"), "uv_os_unsetenv"))("NODE_OPTIONS");
		std::vector<std::string> node_argv{ "node.exe", "test.js" };
		std::vector<std::string> exec_args;
		std::vector<std::string> errors;
		// Parse Node.js CLI options, and print any errors that have occurred while
		// trying to parse them.
		int exit_code = node::InitializeNodeWithArgs(&node_argv, &exec_args, &errors);
		for (const std::string& error : errors)
			fprintf(stderr, "%s: %s\n", node_argv[0].c_str(), error.c_str());
		if (exit_code != 0) {
			Utilities::ErrorUtils::ThrowException(L"Failed to initialize NodeInstance.");
			return;
		}
	}
	NodeManager::~NodeManager()
	{
		v8::V8::Dispose();
		v8::V8::ShutdownPlatform();
	}
}