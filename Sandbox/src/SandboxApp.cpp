
#include <Penelope.hpp>

class ExampleLayer : public Penelope::Layer {
public:
	ExampleLayer() : Layer("Example") {

	}

	void OnUpdate() override {
	}

	void OnEvent(Penelope::Event& event) override {
		PN_TRACE("{0}", event);
	}
};

class Sandbox : public Penelope::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {

	}
};

Penelope::Application* Penelope::CreateApplication() {
	return new Sandbox();
}