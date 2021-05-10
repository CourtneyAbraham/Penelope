
#include "EditorLayer.hpp"
#include "Penelope.hpp"

#include <ImGui\imgui_internal.h>
#include "EditorPanels/AllEditorPanels.hpp"

void EditorLayer::OnUpdate() {
}

void EditorLayer::OnImGuiRender() {
	ImGuiWindowFlags windowFlags =
		ImGuiWindowFlags_MenuBar |
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus |
		ImGuiWindowFlags_NoNavFocus;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGui::Begin("GlobalEditorDockSpace", nullptr, windowFlags);
	ImGui::PopStyleVar(3);

	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
		GenerateDockingSpace();
	}

	ImGui::End();

	for (const auto& [name, panel] : m_EditorPanels) {
		panel->Draw();
	}
}

void EditorLayer::GenerateDockingSpace() {
	static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;
	ImGuiID dockspaceID = ImGui::GetID("EditorDockSpace");
	ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	static bool firstTime = true;
	if (firstTime) {
		firstTime = false;

		ImGui::DockBuilderRemoveNode(dockspaceID);
		ImGui::DockBuilderAddNode(dockspaceID, dockspaceFlags | ImGuiDockNodeFlags_DockSpace);
		ImGui::DockBuilderSetNodeSize(dockspaceID, viewport->Size);

		NewPanelDock("Properties", &dockspaceID, ImGuiDir_Right, 0.175f);
		NewPanelDock("Log", &dockspaceID, ImGuiDir_Down, 0.2f);
		NewPanelDock("Hierarchy", &dockspaceID, ImGuiDir_Left, 0.25f);
		m_DockingIDs["Viewport"] = dockspaceID;

		ImGui::DockBuilderDockWindow("Viewport", m_DockingIDs["Viewport"]);
		ImGui::DockBuilderGetNode(m_DockingIDs["Viewport"])->LocalFlags |= ImGuiDockNodeFlags_HiddenTabBar;
		ImGui::DockBuilderFinish(dockspaceID);

		PushEditorPanel<LogPanel>("Log");
		PushEditorPanel<PropertiesPanel>("Properties");
		PushEditorPanel<HierarchyPanel>("Hierarchy");
		PushEditorPanel<ViewportPanel>("Viewport");
	}
}

void EditorLayer::OnEvent(Penelope::Event& event) {
	Penelope::EventDispatcher dispatcher(event);

	dispatcher.Dispatch<Penelope::LogMessageEvent>(PN_BIND_EVENT_FN(EditorLayer::OnLogMessageEvent));
}

bool EditorLayer::OnLogMessageEvent(Penelope::LogMessageEvent& event) {
	for (const auto& [name, panel] : m_EditorPanels) {
		if (strcmp(name, "Log") == 0) {
			((LogPanel*)panel)->AddLogMessage(event.GetMessage());
		}
	}
	return false;
}

template<typename PanelClass>
PanelClass* EditorLayer::PushEditorPanel(const char* name) {
	m_EditorPanels.emplace(name, new PanelClass(name));
	return (PanelClass*)m_EditorPanels[name];
}

void EditorLayer::PopEditorPanel(Penelope::ImGuiPanel* inPanel) {
	for (const auto& [name, panel] : m_EditorPanels) {
		if (panel == inPanel) {
			delete panel;
			m_EditorPanels.erase(name);
		}
	}
}

void EditorLayer::PopEditorPanel(const char* inName) {
	for (const auto& [name, panel] : m_EditorPanels) {
		if (strcmp(name, inName) == 0) {
			delete panel;
			m_EditorPanels.erase(name);
		}
	}
}

void EditorLayer::NewPanelDock(const char* name, ImGuiID* id, ImGuiDir split_dir, float sizeRatio) {
	m_DockingIDs[name] = ImGui::DockBuilderSplitNode(*id, split_dir, sizeRatio, nullptr, id);
	ImGui::DockBuilderDockWindow(name, m_DockingIDs[name]);
}