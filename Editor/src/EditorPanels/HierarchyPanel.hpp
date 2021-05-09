#pragma once

class HierarchyPanel : public Penelope::ImGuiPanel {
public:

	HierarchyPanel(const char* name) : ImGuiPanel(name) {
		Draw();
	}

	void Draw() override {
		ImGui::Begin(m_Name);

		ImGui::Text("Hierarchy time!");

		ImGui::End();
	}
};