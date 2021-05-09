#pragma once

class PropertiesPanel : public Penelope::ImGuiPanel {
public:

	PropertiesPanel(const char* name) : ImGuiPanel(name) { }

	void Draw() override {
		ImGui::Begin(m_Name);

		ImGui::Text("Properties time!");

		ImGui::End();
	}
};