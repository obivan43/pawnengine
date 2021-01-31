#include "pch.h"

#ifdef PAWN_DIRECTX11

#pragma comment(lib, "d3d11.lib")

#endif

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
    std::wstring windowTitle(L"Pawn WinAPIWindow");
    pawn::Window& window = pawn::WinAPIWindow::Instance(windowTitle, 800, 600, hInstance);

    pawn::Clock timer;
    timer.Reset();

    std::unique_ptr<pawn::GraphicsAPI> graphicsAPI;
#ifdef PAWN_DIRECTX11
    graphicsAPI = std::make_unique<pawn::DirectX11API>();
#else
    graphicsAPI = std::make_unique<pawn::GraphicsAPI>();
#endif
	
    graphicsAPI->SetContext(window.GetGraphicsContext());
    graphicsAPI->SetClearColor(1.0f, 0.0f, 0.0f);

    while(!window.IsClosed()) {
        timer.Tick();
		graphicsAPI->Clear();
    	
        window.Update();
    }

    return 0;
}