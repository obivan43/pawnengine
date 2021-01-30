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

    ShowWindow(hwnd, nCmdShow);

    pawn::Clock timer;
    timer.Reset();

    pawn::DirectX11API directX11Api;
	
    MSG msg = { };
    while (msg.message != WM_QUIT) {
        if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return 0;
}