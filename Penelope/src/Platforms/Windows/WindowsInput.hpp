#pragma once

#include "Penelope/Input.hpp"

namespace Penelope {
	class WindowsInput : public Input {
	protected:
		bool IsKeyPressedImpl(int keycode) override;

		bool IsMouseButtonPressedImpl(int button) override;
		std::pair<float, float> GetMousePositionImpl() override;
	};
}