#pragma once

#include <string>

namespace Penelope {


	enum LogLevel {
		LEVEL_TRACE = 0,
		LEVEL_DEBUG = 1,
		LEVEL_INFO = 2,
		LEVEL_WARN = 3,
		LEVEL_ERROR = 4,
		LEVEL_CRITICAL = 5,
		LEVEL_OFF = 6
	};

	struct LogMessageInfo {

		LogMessageInfo(LogLevel messageLevel = LEVEL_TRACE, const std::string& messageText = "null") : level(messageLevel), text(messageText) {

		}

		LogLevel level = LEVEL_TRACE;
		std::string text = "null";
	};

	class LogMessageEvent : public Event {
	public:
		LogMessageEvent(LogLevel level, const std::string& message) : m_Message(level, message) {}

		inline LogMessageInfo GetMessage() { return m_Message; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "LogMessageEvent: " << m_Message.level << ", " << m_Message.text;
			return ss.str();
		}

		EVENT_CLASS_TYPE(LogMessage)
		EVENT_CLASS_CATEGORY(EventCategoryLog)

	private:
		LogMessageInfo m_Message;
	};
}