#pragma once

#include "Penelope/Core.hpp"
#include "Penelope/Window.hpp"
#include "Penelope/Events/ApplicationEvent.hpp"
#include "Penelope/LayerStack.hpp"

namespace Penelope {

	class PENELOPE_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:
		bool OnWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> m_Window;

		bool m_Running = true;

		LayerStack m_LayerStack;
	};

	// To be define by client
	Application* CreateApplication();
}