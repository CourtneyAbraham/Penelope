#include "pnpch.hpp"

#include "OpenGLContext.hpp"

#include <GLFW/glfw3.h>
#include <Glad/glad.h>

namespace Penelope {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle){
		PN_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PN_CORE_ASSERT(status, "Failed to initialise Glad!");

		PN_CORE_INFO("OpenGL Info:");
		PN_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		PN_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		PN_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}

}