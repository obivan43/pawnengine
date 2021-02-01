#include "pch.h"
#include "WinAPIWindow.h"
#include "GraphicsContext.h"
#include "DirectX11Context.h"

namespace pawn {

	WinAPIWindow::WinAPIWindow(const std::wstring& title, uint32_t width, uint32_t height)
	: m_Width(width), m_Height(height), m_IsClosed(false) {
        const wchar_t className[] = L"Window";
        HINSTANCE hInstance = GetModuleHandle(nullptr);
        WNDCLASS wc = { };
        wc.lpfnWndProc = DefWindowProc;
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

        m_WindowHandle = CreateWindowEx(0, className,
            title.c_str(),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            nullptr,
            nullptr,
            hInstance,
            nullptr
        );

        RECT rect = {};
        GetWindowRect(m_WindowHandle, &rect);
        SetWindowPos(m_WindowHandle, HWND_TOP, rect.left, rect.top, 800, 600, 0);

        ShowWindow(m_WindowHandle, SW_SHOW);
	}

	void WinAPIWindow::Update() {
        static MSG msg = { };
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (msg.message == WM_QUIT) {
            m_IsClosed = true;
        }
	}

}
