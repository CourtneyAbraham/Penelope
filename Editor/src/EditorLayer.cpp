
#include "EditorLayer.hpp"

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

	for (Penelope::ImGuiPanel* panel : m_EditorPanels) {
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

		PushEditorPanel(new PropertiesPanel("Properties"));
		PushEditorPanel(new LogPanel("Log"));
		PushEditorPanel(new HierarchyPanel("Hierarchy"));
		PushEditorPanel(new ViewportPanel("Viewport"));
	}
}

void EditorLayer::OnEvent(Penelope::Event& event) {
}

void EditorLayer::PushEditorPanel(Penelope::ImGuiPanel* panel) {
	m_EditorPanels.emplace_back(panel);
}
void EditorLayer::PopEditorPanel(Penelope::ImGuiPanel* panel) {
	auto it = std::find(m_EditorPanels.begin(), m_EditorPanels.end(), panel);
	if (it != m_EditorPanels.end()) {
		delete *(it);
		m_EditorPanels.erase(it);
	}

}

void EditorLayer::NewPanelDock(const char* name, ImGuiID* id, ImGuiDir split_dir, float sizeRatio) {
	m_DockingIDs[name] = ImGui::DockBuilderSplitNode(*id, split_dir, sizeRatio, nullptr, id);
	ImGui::DockBuilderDockWindow(name, m_DockingIDs[name]);
}