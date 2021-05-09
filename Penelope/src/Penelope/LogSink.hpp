#pragma once

#include <Penelope.hpp>
#include <spdlog/sinks/base_sink.h>


namespace Penelope {
	template<typename Mutex>
	class LogEventSink : public spdlog::sinks::base_sink<Mutex> {
	protected:
		void sink_it_(const spdlog::details::log_msg& msg) override {
			spdlog::memory_buf_t formatted;
			base_sink<Mutex>::formatter_->format(msg, formatted);

			Penelope::LogMessageEvent event((Penelope::LogLevel)msg.level, fmt::to_string(formatted));
			Penelope::Application::Get().OnEvent(event);
		}

		void flush_() override {

		}
	};

#include "spdlog/details/null_mutex.h"
#include <mutex>
	using LogSinkMT = LogEventSink<std::mutex>;
	using LogSinkST = LogEventSink<spdlog::details::null_mutex>;
}