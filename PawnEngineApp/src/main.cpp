#include "pch.h"
#include "Application.h"

#ifdef PAWN_DIRECTX11

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

#elif PAWN_OPENGL

#pragma comment(lib, "opengl32.lib")

#endif

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE parent, PWSTR pCmdLine, int nCmdShow) {
	UNUSED(hInstance)
	UNUSED(parent)
	UNUSED(nCmdShow)
	UNUSED(hInstance)

#if defined(DEBUG) | defined(_DEBUG)
	spdlog::set_level(spdlog::level::debug);
#endif
	
	pawn::Application& application = pawn::Application::Instance();
	application.Run();
    return 0;
}