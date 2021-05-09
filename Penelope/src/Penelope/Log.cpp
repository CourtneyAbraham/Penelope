#pragma once

#include "pnpch.hpp"

#include "Log.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "LogSink.hpp"

namespace Penelope {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {

		spdlog::set_level(spdlog::level::trace);

		std::vector<spdlog::sink_ptr> sinks;
		sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());

		sinks.push_back(std::make_shared<LogSinkMT>());

		s_CoreLogger = std::make_shared<spdlog::logger>("PENELOPE", begin(sinks), end(sinks));
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->set_pattern("%^[%T] %n: %v%$");

		spdlog::set_level(spdlog::level::trace);
		s_ClientLogger = std::make_shared<spdlog::logger>("APP", begin(sinks), end(sinks));
		s_ClientLogger->set_level(spdlog::level::trace);
		s_ClientLogger->set_pattern("%^[%T] %n: %v%$");
	}

}