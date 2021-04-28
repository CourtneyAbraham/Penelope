#pragma once

#include "Core.h"

namespace Penelope {

	class PENELOPE_API Application {
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	// To be define by client
	Application* CreateApplication();
}