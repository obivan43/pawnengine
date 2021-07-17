#pragma once

#ifdef _WIN32

#include "WindowsAPI.h"

extern "C" {

	void SetGameEngineWindowHWND(HWND handle);
	HWND GetGameEngineWindowHWND();

}

#endif
