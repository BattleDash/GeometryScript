#include "hook_manager.h"

#include <cassert>
#include "log_macros.h"

namespace GeometryScript
{
	namespace Hooks
	{
		std::vector<Hook> hooks;
		std::mutex hooks_mutex;
		enum class hook_method
		{
			export_hook,
			function_hook,
			vtable_hook
		};
		struct named_hook : public Hook
		{
			const char* name;
			hook_method method;
		};
		void createHook(Hook::address target, LPVOID replacement)
		{
			Hook hook;
			hook.target = target;
			hook.trampoline = target;
			hook.replacement = replacement;
			hook.install();
			hooks.push_back(hook);
		}
		Hook::address call(LPVOID replacement, Hook::address target)
		{
			assert(target != nullptr || replacement != nullptr);

			for (int attempt = 0; attempt < 2; ++attempt)
			{
				// Protect access to hook list with a mutex
				const std::lock_guard<std::mutex> lock(hooks_mutex);

				// Enumerate list of installed hooks and find matching one
				const auto it = std::find_if(hooks.cbegin(), hooks.cend(),
					[target, replacement](const Hook& hook) {
					// If only a target address is provided, find the matching hook
					if (replacement == nullptr)
						return hook.target == target;
					// Otherwise search with the replacement function address (since the target address may not be known inside a replacement function)
					return hook.replacement == replacement &&
						// Optionally compare the target address too, in case the replacement function is used to hook multiple targets (do not do this if it is unknown)
						(target == nullptr || hook.target == target);
				});

				const Hook tempHook = it != hooks.cend() ? *it : Hook{};

				if (tempHook.valid())
					return tempHook.call();
			}

			LOG(ERROR) << "Unable to resolve hook for 0x" << replacement << '!';

			return nullptr;
		}
	}
}