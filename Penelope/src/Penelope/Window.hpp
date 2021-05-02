#pragma once

#include "pnpch.hpp"

#include "Penelope/Core.hpp"
#include "Penelope/Events/Event.hpp"

namespace Penelope {
	struct WindowProperties {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProperties(
			const std::string& title = "Penelope Engine", 
			unsigned int width = 1920, 
			unsigned int height = 1080) 
			: Title(title), Width(width), Height(height) {}
	};

	class PENELOPE_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual const char* GetClipboardText() = 0;
		virtual void SetClipboardText(const char* text) = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProperties& properties = WindowProperties());
	};
}
