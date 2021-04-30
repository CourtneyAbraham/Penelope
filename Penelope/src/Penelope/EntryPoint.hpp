#pragma once

#ifdef PN_PLATFORM_WINDOWS

extern Penelope::Application* Penelope::CreateApplication();

int main(int argc, char** argv) {
	Penelope::Log::Init();
	PN_CORE_WARN("Init!");
	int a = 5;
	PN_INFO("Init! {0}", a);

	auto app = Penelope::CreateApplication();
	app->Run();
	delete app;
}

#endif