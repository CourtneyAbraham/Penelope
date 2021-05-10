#pragma once

#include "Penelope/Core.hpp"
#include "Penelope/Window.hpp"
#include "Penelope/Events/ApplicationEvent.hpp"
#include "Penelope/LayerStack.hpp"
#include "Penelope/ImGui/ImGuiLayer.hpp"
#include "Penelope/Renderer/Shader.hpp"
#include "Penelope/Renderer/VertexBuffer.hpp"
#include "Penelope/Renderer/IndexBuffer.hpp"

namespace Penelope {

	class Application {
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

		uint32_t m_VertexArray;

		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
	};

	// To be define by client
	Application* CreateApplication();
}