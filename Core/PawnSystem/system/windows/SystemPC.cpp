#include "SystemPC.h"

#ifdef _WIN32

static HWND g_GameEngineWindowHandle{ nullptr };

extern "C" {

	void SetGameEngineWindowHWND(HWND handle) {
		g_GameEngineWindowHandle = handle;
	}

	HWND GetGameEngineWindowHWND() {
		return g_GameEngineWindowHandle;
	}

}

#endif
