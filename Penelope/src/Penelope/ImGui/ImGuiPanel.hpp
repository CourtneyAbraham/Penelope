#pragma once

#include <imgui/imgui.h>

namespace Penelope {
	class ImGuiPanel {
	public:
		ImGuiPanel(const char* name) : m_Name(name) {}
		ImGuiPanel() = delete;
		~ImGuiPanel() = default;

		virtual void Draw() = 0;

	protected:
		const char* m_Name;
		ImGuiID m_ID;
	};
}