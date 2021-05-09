#pragma once

#include <Penelope.hpp>

class LogPanel : public Penelope::ImGuiPanel {
public:

	LogPanel(const char* name) : ImGuiPanel(name) {	
	}

	void AddLogMessage(Penelope::LogMessageInfo message) {
		m_LogMessages.insert(m_LogMessages.cbegin(), message);
	}

	void Draw() override {
		ImGui::Begin(m_Name); 

		if (m_LogMessages.size() > 0) {
			if (m_LogMessages.size() > 256) {
				m_LogMessages.resize(256);
			}
			for (auto it = m_LogMessages.end(); it != m_LogMessages.begin(); ){
				--it;
				ImGui::TextColored(LogColors[it->level], it->text.c_str());
			}

			if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
				ImGui::SetScrollHereY(1.0f);
			}
		}

		ImGui::End();
	}
private:
	std::vector<Penelope::LogMessageInfo> m_LogMessages;

	std::unordered_map<Penelope::LogLevel, ImVec4> LogColors = {
		{Penelope::LogLevel::LEVEL_TRACE,    ImVec4(0.6f, 0.6f, 0.6f, 1.0f)},
		{Penelope::LogLevel::LEVEL_INFO,     ImVec4(1.0f, 1.0f, 1.0f, 1.0f)},
		{Penelope::LogLevel::LEVEL_WARN,     ImVec4(1.0f, 1.0f, 0.6f, 1.0f)},
		{Penelope::LogLevel::LEVEL_ERROR,    ImVec4(1.0f, 0.0f, 0.0f, 1.0f)},
		{Penelope::LogLevel::LEVEL_CRITICAL, ImVec4(0.5f, 0.0f, 0.0f, 1.0f)}
	};

};