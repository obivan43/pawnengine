#pragma once

#include "Window.h"

namespace pawn {
	
	class WinAPIWindow : public Window, public Singleton<WinAPIWindow> {

		public:
			WinAPIWindow() = default;
			WinAPIWindow(const std::wstring& title, uint32_t width, uint32_t height);
			virtual void Update() override;
			
			virtual uint32_t GetWidth() const override { return m_Width; }
			virtual uint32_t GetHeight() const override { return m_Height; }
			virtual void* GetNativeHandle() const override { return m_WindowHandle; }
			virtual bool IsClosed() const override { return m_IsClosed; }

		private:
			static LRESULT CALLBACK FakeWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
			LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
		private:
			uint32_t m_Width;
			uint32_t m_Height;
			HWND m_WindowHandle;
			bool m_IsClosed;

			static WinAPIWindow* m_This;
	};
	
}
