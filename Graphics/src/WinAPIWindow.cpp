#include "pch.h"
#include "WinAPIWindow.h"
#include "GraphicsContext.h"
#include "DirectX11Context.h"

namespace pawn {

    WinAPIWindow* WinAPIWindow::m_This = nullptr;
	
    LRESULT CALLBACK WinAPIWindow::FakeWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    	if(m_This != nullptr) {
            return m_This->WindowProc(hwnd, uMsg, wParam, lParam);
    	}

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    LRESULT CALLBACK WinAPIWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
             switch (uMsg) {
                 case WM_DESTROY: {
                     m_IsClosed = true;
                     NotifyObservers(WindowCloseEvent());
                     PostQuitMessage(0);
                 }
                 break;

                 default: {}
             }

             return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

	WinAPIWindow::WinAPIWindow(const std::wstring& title, uint32_t width, uint32_t height)
	: m_Width(width), m_Height(height), m_IsClosed(false) {
        const wchar_t className[] = L"Window";
        HINSTANCE hInstance = GetModuleHandle(nullptr);
        WNDCLASS wc = { };
        wc.lpfnWndProc = WinAPIWindow::FakeWindowProc;
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

        m_This = this;
	}

	void WinAPIWindow::Update() {
        static MSG msg = { };
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
	}

}
