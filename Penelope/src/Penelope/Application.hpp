#pragma once

#include "Penelope/Core.hpp"
#include "Penelope/Window.hpp"
#include "Penelope/Events/ApplicationEvent.hpp"

namespace Penelope {

	class PENELOPE_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);
	private:
		bool OnWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> m_Window;

		bool m_Running = true;
	};

	// To be define by client
	Application* CreateApplication();
}