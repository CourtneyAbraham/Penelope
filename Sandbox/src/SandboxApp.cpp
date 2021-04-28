
#include <Penelope.h>

class Sandbox : public Penelope::Application {
public:
	Sandbox() {

	}
	~Sandbox() {

	}
};

Penelope::Application* Penelope::CreateApplication() {
	return new Sandbox();
}