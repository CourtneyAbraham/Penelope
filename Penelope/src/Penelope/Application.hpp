#pragma once

#include "Penelope/Core.hpp"
#include "Penelope/Window.hpp"
#include "Penelope/Events/ApplicationEvent.hpp"
#include "Penelope/LayerStack.hpp"
#include "Penelope/ImGui/ImGuiLayer.hpp"

namespace Penelope {

	class PENELOPE_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;

		LayerStack m_LayerStack;

		static Application* s_Instance;
	};

	// To be define by client
	Application* CreateApplication();
}