#pragma once

#ifdef PN_PLATFORM_WINDOWS

extern Penelope::Application* Penelope::CreateApplication();

int main(int argc, char** argv) {
	Penelope::Log::Init();

	auto app = Penelope::CreateApplication();
	app->Run();
	delete app;
}

#endif