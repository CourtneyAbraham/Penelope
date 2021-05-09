#pragma once

class ViewportPanel : public Penelope::ImGuiPanel {
public:

	ViewportPanel(const char* name) : ImGuiPanel(name) {
		Draw();
	}

	void Draw() override {
		ImGui::Begin(m_Name);
		ImGui::Text("Viewport time!");
		ImGui::End();
	}
};