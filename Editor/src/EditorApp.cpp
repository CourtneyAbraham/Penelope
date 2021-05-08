
#include <Penelope.hpp>
#include <ImGui\imgui.h>
#include <ImGui\imgui_internal.h>

class EditorLayer : public Penelope::Layer {
public:
	EditorLayer() : Layer("Editor") {

	}

	void OnUpdate() override {
	}

	void OnImGuiRender() override {
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("GlobalEditorDockSpace", nullptr, window_flags);
		ImGui::PopStyleVar();
		ImGui::PopStyleVar(2);

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
			ImGuiID dockspaceID = ImGui::GetID("EditorDockSpace");
			ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspace_flags);

			static auto firstTime = true;
			if (firstTime) {
				firstTime = false;

				ImGui::DockBuilderRemoveNode(dockspaceID);
				ImGui::DockBuilderAddNode(dockspaceID, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
				ImGui::DockBuilderSetNodeSize(dockspaceID, viewport->Size);

				auto dockIDProperties = ImGui::DockBuilderSplitNode(dockspaceID, ImGuiDir_Right, 0.175f, nullptr, &dockspaceID);
				auto dockIDLog = ImGui::DockBuilderSplitNode(dockspaceID, ImGuiDir_Down, 0.2f, nullptr, &dockspaceID);
				auto dockIDHierarchy = ImGui::DockBuilderSplitNode(dockspaceID, ImGuiDir_Left, 0.25f, nullptr, &dockspaceID);
				auto dockIDViewport = ImGui::DockBuilderGetNode(dockspaceID);

				// we now dock our windows into the docking node we made above
				ImGui::DockBuilderDockWindow("Log", dockIDLog);
				ImGui::DockBuilderDockWindow("Properties", dockIDProperties);
				ImGui::DockBuilderDockWindow("Hierarchy", dockIDHierarchy);
				ImGui::DockBuilderDockWindow("Viewport", dockspaceID);
				ImGui::DockBuilderFinish(dockspaceID);
			}
		}

		ImGui::End();

		ImGui::Begin("Properties");
		ImGui::Text("Hello, Properties!");
		ImGui::End();

		ImGui::Begin("Log");
		ImGui::Text("Hello, Log!");
		ImGui::End();

		ImGui::Begin("Hierarchy");
		ImGui::Text("Hello, Hierarchy!");
		ImGui::End();

		ImGui::Begin("Viewport");
		ImGui::Text("Hello, Viewport!");
		ImGui::End();
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