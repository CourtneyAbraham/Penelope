
#include <Penelope.hpp>

class EditorLayer : public Penelope::Layer {
public:
	EditorLayer() : Layer("Editor") {

	}

	void OnUpdate() override {
	}

	void OnImGuiRender() override {
	}

	void OnEvent(Penelope::Event& event) override {
	}
};

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