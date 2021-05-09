#pragma once

#include <unordered_map>
#include <Penelope.hpp>
#include <ImGui/imgui.h>

class EditorLayer : public Penelope::Layer {
public:
	EditorLayer() : Layer("Editor") { }

	void OnUpdate() override;

	void OnImGuiRender() override;

	void GenerateDockingSpace();

	void OnEvent(Penelope::Event& event) override;

private:
	std::unordered_map<const char*, ImGuiID> m_DockingIDs;

	void NewPanelDock(const char* name, ImGuiID* id, ImGuiDir split_dir, float sizeRatio);
};