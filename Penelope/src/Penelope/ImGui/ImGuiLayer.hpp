#pragma once

#include "Penelope/Layer.hpp"
#include "Penelope/Events/AllEvents.hpp"

namespace Penelope {
	class ImGuiLayer : public Layer {

	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;
		void Begin();
		void End();

	private:

		float m_Time = 0.0f;

	};
}