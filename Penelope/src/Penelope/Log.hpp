#pragma once

#include <memory>

#include "Core.hpp"
#include "spdlog/spdlog.h"

namespace Penelope {
	class PN_API Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; };
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; };

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define PENELOPE_CORE_TRACE(...)    ::Penelope::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PENELOPE_CORE_INFO(...)     ::Penelope::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PENELOPE_CORE_WARN(...)     ::Penelope::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PENELOPE_CORE_ERROR(...)    ::Penelope::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PENELOPE_CORE_CRITICAL(...) ::Penelope::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define PENELOPE_TRACE(...)         ::Penelope::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PENELOPE_INFO(...)          ::Penelope::Log::GetClientLogger()->info(__VA_ARGS__)
#define PENELOPE_WARN(...)          ::Penelope::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PENELOPE_ERROR(...)         ::Penelope::Log::GetClientLogger()->error(__VA_ARGS__)
#define PENELOPE_CRITICAL(...)      ::Penelope::Log::GetClientLogger()->critical(__VA_ARGS__)