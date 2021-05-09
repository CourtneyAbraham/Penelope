
#include <Penelope.hpp>
#include <ImGui\imgui.h>
#include <ImGui\imgui_internal.h>

#include "EditorPanels/AllEditorPanels.hpp"

class EditorLayer : public Penelope::Layer {
public:
	EditorLayer() : Layer("Editor") {

	}

	void OnUpdate() override {
	}

	void OnImGuiRender() override {
		static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("GlobalEditorDockSpace", nullptr, windowFlags);
		ImGui::PopStyleVar();
		ImGui::PopStyleVar(2);

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
			ImGuiID dockspaceID = ImGui::GetID("EditorDockSpace");
			ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);

			static auto firstTime = true;
			if (firstTime) {
				firstTime = false;

				ImGui::DockBuilderRemoveNode(dockspaceID);
				ImGui::DockBuilderAddNode(dockspaceID, dockspaceFlags | ImGuiDockNodeFlags_DockSpace);
				ImGui::DockBuilderSetNodeSize(dockspaceID, viewport->Size);

				auto dockIDProperties = ImGui::DockBuilderSplitNode(dockspaceID, ImGuiDir_Right, 0.175f, nullptr, &dockspaceID);
				auto dockIDLog = ImGui::DockBuilderSplitNode(dockspaceID, ImGuiDir_Down, 0.2f, nullptr, &dockspaceID);
				auto dockIDHierarchy = ImGui::DockBuilderSplitNode(dockspaceID, ImGuiDir_Left, 0.25f, nullptr, &dockspaceID);
				auto dockIDViewport = dockspaceID;

				// we now dock our windows into the docking node we made above
				ImGui::DockBuilderDockWindow("Log", dockIDLog);
				ImGui::DockBuilderDockWindow("Properties", dockIDProperties);
				ImGui::DockBuilderDockWindow("Hierarchy", dockIDHierarchy);
				ImGui::DockBuilderDockWindow("Viewport", dockIDViewport);
				ImGui::DockBuilderGetNode(dockIDViewport)->LocalFlags |= ImGuiDockNodeFlags_HiddenTabBar;
				ImGui::DockBuilderFinish(dockspaceID);
			}
		}

		ImGui::End();


		PropertiesPanel propertiesPanel("Properties");
		LogPanel logPanel("Log");
		HierarchyPanel hierarchyPanel("Hierarchy");
		ViewportPanel viewportPanel("Viewport");
	}

	void OnEvent(Penelope::Event& event) override {
	}
};

class Editor : public Penelope::Application {
public:
	Editor() {
		PushLayer(new EditorLayer());
	}
	~Editor() {

	}
};

Penelope::Application* Penelope::CreateApplication() {
	return new Editor();
}