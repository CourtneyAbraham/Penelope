#pragma once

#include "Penelope/Renderer/GraphicsContext.hpp"

struct GLFWwindow;

namespace Penelope {
	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}