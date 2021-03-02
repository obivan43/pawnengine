#include "pch.h"
#include "WinAPIWindow.h"

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
                     WindowCloseEvent event;
                     NotifyObservers(event);
                     PostQuitMessage(0);
                 }
                 break;

                 case WM_SETFOCUS: {
                     WindowFocusEvent event;
                     NotifyObservers(event);
                 }
                 break;

                 case WM_KILLFOCUS: {
                     WindowLostFocusEvent event;
                     NotifyObservers(event);
                 }
                 break;

                 case WM_SIZE: {
                     uint32_t width = LOWORD(lParam);
                     uint32_t height = HIWORD(lParam);
                     WindowResizeEvent event(width, height);
                     NotifyObservers(event);
                 }
                 break;

                 case WM_MOVE: {
                     int32_t xPos = LOWORD(lParam);
                     int32_t yPos = HIWORD(lParam);
                     WindowMovedEvent event(xPos, yPos);
                     NotifyObservers(event);
                 }
                 break;

                 case WM_KEYDOWN: {
                     m_KeyboardInputManager.OnKeyPressed(static_cast<uint8_t>(wParam));
                 }
                 break;

                 case WM_KEYUP: {
                     m_KeyboardInputManager.OnKeyRelease(static_cast<uint8_t>(wParam));
                 }
                 break;

                 case WM_CHAR: {
                     m_KeyboardInputManager.OnChar(static_cast<uint8_t>(wParam));
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
        SetWindowPos(m_WindowHandle, HWND_TOP, rect.left, rect.top, width, height, 0);

        m_This = this;
	}

	void WinAPIWindow::Update() {
        static MSG msg = { };
        ShowWindow(m_WindowHandle, SW_SHOW);
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
	}

}
