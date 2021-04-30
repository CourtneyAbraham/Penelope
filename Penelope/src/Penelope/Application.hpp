#pragma once

#include "Penelope/Core.hpp"
#include "Penelope/Window.hpp"

namespace Penelope {

	class PENELOPE_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> m_Window;

		bool m_Running = true;
	};

	// To be define by client
	Application* CreateApplication();
}