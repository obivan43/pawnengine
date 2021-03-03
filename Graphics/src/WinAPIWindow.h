#pragma once

#include "Window.h"

namespace pawn {
	
	class WinAPIWindow : public Window, public Singleton<WinAPIWindow> {

		friend Singleton<WinAPIWindow>;
		
		public:
			void Update() override;
			
			uint32_t GetWidth() const override { return m_Width; }
			uint32_t GetHeight() const override { return m_Height; }
			uint32_t GetCenterPositionX() const override { return m_CenterX; }
			uint32_t GetCenterPositionY() const override { return m_CenterY; }
			void* GetNativeHandle() const override { return m_WindowHandle; }
			bool IsClosed() const override { return m_IsClosed; }

		private:
			WinAPIWindow() = default;
			WinAPIWindow(const std::wstring & title, uint32_t width, uint32_t height);
		
			static LRESULT CALLBACK FakeWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
			LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
		private:
			uint32_t m_Width;
			uint32_t m_Height;

			int32_t m_CenterX;
			int32_t m_CenterY;
		
			HWND m_WindowHandle;
			bool m_IsClosed;

			static WinAPIWindow* m_This;
	};
	
}
