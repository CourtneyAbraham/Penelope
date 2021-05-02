#include "pnpch.hpp"

#include "Penelope/Application.hpp"

#include "Penelope/Input.hpp"

#include "glad/glad.h"

namespace Penelope {

	Application* Application::s_Instance = nullptr;

	Application::Application() {

		PN_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(PN_BIND_EVENT_FN(Application::OnEvent));
	}
	Application::~Application() {

	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::OnEvent(Event& event) {
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<WindowCloseEvent>(PN_BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(event);

			if (event.Handled) {
				break;
			}
		}

	}

	void Application::Run() {

		while (m_Running) {

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& event) {
		m_Running = false;

		return true;
	}

}