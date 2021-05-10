#pragma once

#include <unordered_map>
#include <vector>
#include <Penelope.hpp>
#include <ImGui/imgui.h>

class EditorLayer : public Penelope::Layer {
public:
	EditorLayer() : Layer("Editor") { }

	~EditorLayer() {
		for (const auto& [name, panel] : m_EditorPanels) {
			delete panel;
		}
	}

	void OnUpdate() override;

	void OnImGuiRender() override;

	void GenerateDockingSpace();

	void OnEvent(Penelope::Event& event) override;

	template<class PanelClass>
	PanelClass* PushEditorPanel(const char* name);

	void PopEditorPanel(Penelope::ImGuiPanel* panel);
	void PopEditorPanel(const char* name);

private:
	std::unordered_map<const char*, ImGuiID> m_DockingIDs;
	std::unordered_map<const char*, Penelope::ImGuiPanel*> m_EditorPanels;

	std::vector<Penelope::LogMessageInfo> m_LogMessages;

	bool OnLogMessageEvent(Penelope::LogMessageEvent event);

	void NewPanelDock(const char* name, ImGuiID* id, ImGuiDir split_dir, float sizeRatio);
};
