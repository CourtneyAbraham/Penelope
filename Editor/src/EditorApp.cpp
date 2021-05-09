
#include <Penelope.hpp>
#include <Penelope/EntryPoint.hpp>

#include "EditorLayer.hpp"

class Editor : public Penelope::Application {
public:
	Editor() {
		PushLayer(new EditorLayer());
	}
	~Editor() {

	}
};

Penelope::Application* Penelope::CreateApplication() {
	return new Editor();
}