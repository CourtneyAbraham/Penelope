#include "pnpch.hpp"

#include "Application.hpp"

#include "Penelope/Log.hpp"
#include "Penelope/Events/ApplicationEvent.hpp"

namespace Penelope {

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}
	Application::~Application() {

	}

	void Application::Run() {

		while (m_Running) {
			m_Window->OnUpdate();
		}
	}

}