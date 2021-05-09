#pragma once

#include <Penelope.hpp>

class ViewportPanel : public Penelope::ImGuiPanel {
public:

	ViewportPanel(const char* name) : ImGuiPanel(name) { }

	void Draw() override {
		ImGui::Begin(m_Name);
		m_Size = ImGui::GetWindowSize();
		ImGui::End();
	}
private:
	ImVec2 m_Size = ImVec2(0, 0);
};