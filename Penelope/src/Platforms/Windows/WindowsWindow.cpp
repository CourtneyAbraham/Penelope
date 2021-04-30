#include "pnpch.hpp"

#include "WindowsWindow.hpp"

namespace Penelope {
	static bool s_GLFWInitialised = false;

	Window* Window::Create(const WindowProperties& properties) {
		return new WindowsWindow(properties);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& properties) {
		Init(properties);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}
	void WindowsWindow::Init(const WindowProperties& properties) {
		m_Data.Title = properties.Title;
		m_Data.Width = properties.Width;
		m_Data.Height = properties.Height;

		PN_CORE_TRACE("Created window \"{0}\" ({1}, {2})", properties.Title, properties.Width, properties.Height);

		if (!s_GLFWInitialised) {

			// TODO Terminate GLFW on system shutdown
			int success = glfwInit();
			PN_CORE_ASSERT(success, "Could not initialise GLFW!");

			s_GLFWInitialised = true;
		}

		m_Window = glfwCreateWindow(properties.Width, properties.Height, properties.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);
		} else {
			glfwSwapInterval(0);
		}

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const {
		return m_Data.VSync;
	}
}