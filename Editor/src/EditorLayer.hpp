#pragma once

#include <unordered_map>
#include <vector>
#include <Penelope.hpp>
#include <ImGui/imgui.h>

class EditorLayer : public Penelope::Layer {
public:
	EditorLayer() : Layer("Editor") { }

	~EditorLayer() {
		for (Penelope::ImGuiPanel* panel : m_EditorPanels) {
			delete panel;
		}
	}

	void OnUpdate() override;

	void OnImGuiRender() override;

	void GenerateDockingSpace();

	void OnEvent(Penelope::Event& event) override;

	void PushEditorPanel(Penelope::ImGuiPanel* panel);
	void PopEditorPanel(Penelope::ImGuiPanel* panel);

private:
	std::unordered_map<const char*, ImGuiID> m_DockingIDs;
	std::vector<Penelope::ImGuiPanel*> m_EditorPanels;

	void NewPanelDock(const char* name, ImGuiID* id, ImGuiDir split_dir, float sizeRatio);
};