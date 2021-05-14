#include "pnpch.hpp"

#include "Penelope/Application.hpp"
#include "Penelope/Input.hpp"

#include <glad/glad.h>

namespace Penelope {

	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type) 	{
			case Penelope::ShaderDataType::Float:
			case Penelope::ShaderDataType::Float2:
			case Penelope::ShaderDataType::Float3:
			case Penelope::ShaderDataType::Float4:
				return GL_FLOAT;
			case Penelope::ShaderDataType::Int:
			case Penelope::ShaderDataType::Int2:
			case Penelope::ShaderDataType::Int3:
			case Penelope::ShaderDataType::Int4:
				return GL_INT;
			case Penelope::ShaderDataType::Mat3:
			case Penelope::ShaderDataType::Mat4:
				return GL_FLOAT;
			case Penelope::ShaderDataType::Bool:
				return GL_BOOL;
		}

		PN_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	Application::Application() {

		PN_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(PN_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 1.0f, 1.0f
		};

		uint32_t indices[3] = {
			0, 1, 2
		};

		// Vertex Array
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		// Vertex Buffer
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "aPos" },
			{ ShaderDataType::Float4, "aColor" }
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexBuffer->Bind();

		size_t index = 0;
		for (const auto& element : layout) {
			glVertexAttribPointer(
				index, 
				element.GetComponentCount(), 
				ShaderDataTypeToOpenGLBaseType(element.Type), 
				element.Normailzed ? GL_TRUE : GL_FALSE, 
				layout.GetStride(), 
				(void*)element.Offset
			);
			glEnableVertexAttribArray(index);

			++index;
		}

		// Index Buffer
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_IndexBuffer->Bind();

		std::string vertexSource = R"(
			#version 460 core

			layout (location = 0) in vec3 aPos;
			layout (location = 1) in vec4 aColor;

			out vec4 Color;

			void main(){
				gl_Position = vec4(aPos, 1.0);

				Color = aColor;

			}
		)";
		std::string fragmentSource = R"(
			#version 460 core

			out vec4 FragColor;

			in vec4 Color;

			void main(){
				FragColor = Color;
			}
		)";

		m_Shader.reset(Shader::Create(vertexSource, fragmentSource));
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

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(event);

			if (event.Handled) {
				break;
			}
		}

	}

	void Application::Run() {

		while (m_Running) {

			glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack) {
				//layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& event) {
		m_Running = false;

		return true;
	}

}