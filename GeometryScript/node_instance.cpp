#include "node_instance.h"
#include <vector>
#include <string>
#include <memory>
#include "error_utils.h"
#include "node/v8-util.h"

namespace GeometryScript::Executor
{
	NodeInstance::NodeInstance(node::MultiIsolatePlatform* platform,
		const std::vector<std::string>& args,
		const std::vector<std::string>& exec_args)
	{
        printf("Creating NodeInstance\n");
        int exit_code = 0;

        // Setup up a libuv event loop, v8::Isolate, and Node.js Environment.
        std::vector<std::string> errors;
        std::unique_ptr<node::CommonEnvironmentSetup> setup =
            node::CommonEnvironmentSetup::Create(platform, &errors, args, exec_args);
        if (!setup) {
            for (const std::string& err : errors)
                fprintf(stderr, "%s: %s\n", args[0].c_str(), err.c_str());
            return;
        }

        printf("Created libuv event loop, v8::Isolate, and Node.js Environment.\n");

        v8::Isolate* isolate = setup->isolate();

        isolate->SetFatalErrorHandler([](const char* location, const char* message) {
            printf("FATAL ERROR: %s %s\n", location, message);
        });

        node::Environment* env = setup->env();

        printf("Set up v8::Isolate and Node.js Environment.\n");

        {
            v8::Locker locker(isolate);
            printf("Created v8::Locker from v8::Isolate\n");
            v8::Isolate::Scope isolate_scope(isolate);
            printf("Created v8::Isolate::Scope from v8::Locker\n");
            // The v8::Context needs to be entered when node::CreateEnvironment() and
            // node::LoadEnvironment() are being called.
            v8::HandleScope scope(isolate);
            v8::Local<v8::Context> context = setup->context();
            v8::Context::Scope context_scope(context);

            printf("Loading Node.js Environment\n");

            // Set up the Node.js instance for execution, and run code inside of it.
            // There is also a variant that takes a callback and provides it with
            // the `require` and `process` objects, so that it can manually compile
            // and run scripts as needed.
            // The `require` function inside this script does *not* access the file
            // system, and can only load built-in Node.js modules.
            // `module.createRequire()` is being used to create one that is able to
            // load files from the disk, and uses the standard CommonJS file loader
            // instead of the internal-only `require` function.
            v8::MaybeLocal<v8::Value> loadenv_ret = node::LoadEnvironment(
                env,
                "function test(str) {"
                "   return 'test ' + str;"
                "}"
            );

            printf("Loaded Node.js Environment\n");

            if (loadenv_ret.IsEmpty())  // There has been a JS exception.
            {
                printf("JS Exception\n");
                return;
            }

            exit_code = node::SpinEventLoop(env).FromMaybe(1);

            //printf("%s\n", loadenv_ret.ToLocalChecked());

            v8::Handle<v8::Object> global = context->Global();
            v8::MaybeLocal<v8::Value> maybeValue = global->Get(context, v8::String::NewFromUtf8Literal(isolate, "test"));
            if (maybeValue.IsEmpty())
            {
                printf("Test doesn't exist\n");
                return;
            }
            v8::Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(maybeValue.ToLocalChecked());
            v8::Handle<v8::Value> args[1];
            args[0] = v8::String::NewFromUtf8Literal(isolate, "test");
            printf("Calling Function\n");
            v8::MaybeLocal<v8::Value> maybeResult = func->Call(context, global, 1, args);
            if (maybeResult.IsEmpty())
            {
                printf("Function call failed\n");
                return;
            }
            v8::Handle<v8::Value> jsResult = maybeResult.ToLocalChecked();
            printf("Called Function\n");
            v8::Handle<v8::String> result = jsResult->ToString(context).ToLocalChecked();
            std::string cppStr(*v8::String::Utf8Value(isolate, result));
            printf("test result: %s\n", cppStr);

            // node::Stop() can be used to explicitly stop the event loop and keep
            // further JavaScript from running. It can be called from any thread,
            // and will act like worker.terminate() if called from another thread.
            //node::Stop(env);
        }

        return;
	}

	NodeInstance::~NodeInstance()
	{

	}
}