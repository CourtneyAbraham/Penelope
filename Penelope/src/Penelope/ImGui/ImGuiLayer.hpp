#pragma once

#include "Penelope/Layer.hpp"
#include "Penelope/Events/AllEvents.hpp"

namespace Penelope {
	class PENELOPE_API ImGuiLayer : public Layer {

	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;

	private:
		bool OnWindowResize(WindowResizeEvent& event);

		bool OnKeyTyped(KeyTypedEvent& event);
		bool OnKeyPressed(KeyPressedEvent& event);
		bool OnKeyReleased(KeyReleasedEvent& event);

		bool OnMouseButtonPressed(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& event);
		bool OnMouseMoved(MouseMovedEvent& event);

		bool OnMouseScrolled(MouseScrolledEvent& event);

		const char* ImGuiLayer::GetClipboardString(void*);

		float m_Time = 0.0f;

	};
}