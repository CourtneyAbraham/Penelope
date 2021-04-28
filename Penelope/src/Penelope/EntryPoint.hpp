#pragma once

#ifdef PENELOPE_PLATFORM_WINDOWS

extern Penelope::Application* Penelope::CreateApplication();

int main(int argc, char** argv) {
	Penelope::Log::Init();
	PENELOPE_CORE_WARN("Init!");
	int a = 5;
	PENELOPE_INFO("Init! {0}", a);

	auto app = Penelope::CreateApplication();
	app->Run();
	delete app;
}

#endif