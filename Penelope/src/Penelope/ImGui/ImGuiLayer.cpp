#include "pnpch.hpp"

#include "ImGuiLayer.hpp"

#include "Platforms/OpenGL/ImGuiOpenGLRenderer.h"

#include "Penelope/Application.hpp"
#include "Penelope/Core.hpp"
#include "Penelope/Keycodes.hpp"
#include "Platforms/Windows/WindowsWindow.hpp"

namespace Penelope {

	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {

	}

	ImGuiLayer::~ImGuiLayer() {

	}

	void ImGuiLayer::OnAttach() {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io.KeyMap[ImGuiKey_Tab] = PN_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = PN_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = PN_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = PN_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = PN_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = PN_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = PN_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = PN_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = PN_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = PN_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = PN_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = PN_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = PN_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = PN_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = PN_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = PN_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A] = PN_KEY_A;
		io.KeyMap[ImGuiKey_C] = PN_KEY_C;
		io.KeyMap[ImGuiKey_V] = PN_KEY_V;
		io.KeyMap[ImGuiKey_X] = PN_KEY_X;
		io.KeyMap[ImGuiKey_Y] = PN_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = PN_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 460");

	}

	void ImGuiLayer::OnDetach() {

	}

	void ImGuiLayer::OnUpdate() {


		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}

	void ImGuiLayer::OnEvent(Event& event) {
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<WindowResizeEvent>(PN_BIND_EVENT_FN(ImGuiLayer::OnWindowResize));

		dispatcher.Dispatch<KeyTypedEvent>(PN_BIND_EVENT_FN(ImGuiLayer::OnKeyTyped));
		dispatcher.Dispatch<KeyPressedEvent>(PN_BIND_EVENT_FN(ImGuiLayer::OnKeyPressed));
		dispatcher.Dispatch<KeyReleasedEvent>(PN_BIND_EVENT_FN(ImGuiLayer::OnKeyReleased));

		dispatcher.Dispatch<MouseButtonPressedEvent>(PN_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressed));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(PN_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleased));
		dispatcher.Dispatch<MouseMovedEvent>(PN_BIND_EVENT_FN(ImGuiLayer::OnMouseMoved));
		dispatcher.Dispatch<MouseScrolledEvent>(PN_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolled));
	}

	bool ImGuiLayer::OnWindowResize(WindowResizeEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

		return false;
	}

	bool ImGuiLayer::OnKeyTyped(KeyTypedEvent& event) {

		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharacter(event.GetKeyCode());

		if (io.WantCaptureKeyboard) {
			return true;
		}

		return false;
	}

	bool ImGuiLayer::OnKeyPressed(KeyPressedEvent& event) {

		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.GetKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[PN_KEY_LEFT_CONTROL] || io.KeysDown[PN_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[PN_KEY_LEFT_SHIFT] || io.KeysDown[PN_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[PN_KEY_LEFT_ALT] || io.KeysDown[PN_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[PN_KEY_LEFT_SUPER] || io.KeysDown[PN_KEY_RIGHT_SUPER];

		if (io.WantCaptureKeyboard) {
			return true;
		}
		return false;
	}

	bool ImGuiLayer::OnKeyReleased(KeyReleasedEvent& event) {

		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.GetKeyCode()] = false;

		io.KeyCtrl = io.KeysDown[PN_KEY_LEFT_CONTROL] || io.KeysDown[PN_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[PN_KEY_LEFT_SHIFT] || io.KeysDown[PN_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[PN_KEY_LEFT_ALT] || io.KeysDown[PN_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[PN_KEY_LEFT_SUPER] || io.KeysDown[PN_KEY_RIGHT_SUPER];

		if (io.WantCaptureKeyboard) {
			return true;
		}

		return false;
	}

	bool ImGuiLayer::OnMouseButtonPressed(MouseButtonPressedEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.GetMouseButton()] = true;

		if (io.WantCaptureMouse) {
			return true;
		}
		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleased(MouseButtonReleasedEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.GetMouseButton()] = false;

		if (io.WantCaptureMouse) {
			return true;
		}

		return false;
	}

	bool ImGuiLayer::OnMouseMoved(MouseMovedEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(event.GetX(), event.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolled(MouseScrolledEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += event.GetXOffset();
		io.MouseWheel += event.GetYOffset();

		if (io.WantCaptureMouse) {
			return true;
		}
		return false;
	}

	const char* ImGuiLayer::GetClipboardString(void*) {
		return Application::Get().GetWindow().GetClipboardText((void*)0);
	}
}
