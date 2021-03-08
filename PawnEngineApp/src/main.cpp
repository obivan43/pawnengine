#include "pch.h"
#include "Application.h"
#include "DefaultLayer.h"

#ifdef PAWN_DIRECTX11

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

#elif PAWN_OPENGL

#pragma comment(lib, "opengl32.lib")

#endif

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE parent, PWSTR pCmdLine, int nCmdShow) {
	const std::shared_ptr<pawn::Layer> layer(new pawn::DefaultLayer());

	pawn::Application& application = pawn::Application::Instance();
	application.GetLayerList().PushLayer(layer);

	application.Run();
	
    return 0;
}