#pragma once

class LogPanel : public Penelope::ImGuiPanel {
public:

	LogPanel(const char* name) : ImGuiPanel(name) {
		Draw();
	}

	void Draw() override {
		ImGui::Begin(m_Name);

		ImGui::Text("Log time!");

		ImGui::End();
	}
};