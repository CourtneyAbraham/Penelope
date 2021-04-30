#pragma once

#include "Penelope/Core.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Penelope {
	class PENELOPE_API Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; };
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; };

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define PN_CORE_TRACE(...)    ::Penelope::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PN_CORE_INFO(...)     ::Penelope::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PN_CORE_WARN(...)     ::Penelope::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PN_CORE_ERROR(...)    ::Penelope::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PN_CORE_CRITICAL(...) ::Penelope::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define PN_TRACE(...)         ::Penelope::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PN_INFO(...)          ::Penelope::Log::GetClientLogger()->info(__VA_ARGS__)
#define PN_WARN(...)          ::Penelope::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PN_ERROR(...)         ::Penelope::Log::GetClientLogger()->error(__VA_ARGS__)
#define PN_CRITICAL(...)      ::Penelope::Log::GetClientLogger()->critical(__VA_ARGS__)