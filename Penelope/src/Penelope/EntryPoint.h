#pragma once

#ifdef PENELOPE_PLATFORM_WINDOWS

extern Penelope::Application* Penelope::CreateApplication();

int main(int argc, char** argv) {
	auto app = Penelope::CreateApplication();
	app->Run();
	delete app;
}

#endif