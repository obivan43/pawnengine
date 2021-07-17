#include "WindowsEventFilter.h"

#include "PawnSystem/system/windows/InputManagerWindows.h"

#include <QString>
#include <Windows.h>

namespace impl {

	LRESULT CALLBACK windowEventHandle(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		LRESULT result{ 0 };
		pawn::system::InputManagerWindows::WinHandle(message, wParam, lParam, &result);
		return result;
	}
	
	bool WindowsEventFilter::nativeEventFilter(const QByteArray& eventType, void* message, qintptr* result) {
		if (eventType == QString("windows_generic_MSG")) {
			result = reinterpret_cast<qintptr*>(windowEventHandle(
				static_cast<MSG*>(message)->hwnd,
				static_cast<MSG*>(message)->message,
				static_cast<MSG*>(message)->wParam,
				static_cast<MSG*>(message)->lParam
			));
		}
		return false;
	}

}
