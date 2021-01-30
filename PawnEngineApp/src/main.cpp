#include "pch.h"

#ifdef PAWN_DIRECTX11

#pragma comment(lib, "d3d11.lib")

#endif

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY: {
            PostQuitMessage(0);
        }
        return 0;
    	
        default: {}
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
    const wchar_t className[] = L"Test Window";
    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = className;
    wc.style = CS_OWNDC;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hCursor = nullptr;
    wc.hIcon = nullptr;
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = nullptr;
	
    RegisterClass(&wc);

    const HWND hwnd = CreateWindowEx(0,className,
		L"Learn to Program Windows",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    if (hwnd == nullptr) {
        return 0;
    }

    RECT rect = {};
    GetWindowRect(hwnd, &rect);
    SetWindowPos(hwnd, HWND_TOP, rect.left, rect.top, 800, 600, 0);
	
    ShowWindow(hwnd, nCmdShow);

    pawn::Clock timer;
    timer.Reset();

    std::shared_ptr<pawn::GraphicsContext> graphicsContext;
    std::unique_ptr<pawn::GraphicsAPI> graphicsAPI;
	
#ifdef PAWN_DIRECTX11
    graphicsContext = std::make_shared<pawn::DirectX11Context>();
    graphicsAPI = std::make_unique<pawn::DirectX11API>();
#endif
	
    graphicsContext->Initialize(hwnd);
    graphicsAPI->SetContext(graphicsContext);
    graphicsAPI->SetClearColor(1.0f, 0.0f, 0.0f);
	
    MSG msg = { };
    while (msg.message != WM_QUIT) {
        timer.Tick();
    	
        if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    	
        graphicsAPI->Clear();
        graphicsContext->SwapBuffers();
    }

    return 0;
}