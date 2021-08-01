#include "SystemPC.h"

#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

#ifdef _WIN32

static HWND g_GameEngineWindowHandle{ nullptr };

extern "C" {

	void SetGameEngineWindowHWND(HWND handle) {
		g_GameEngineWindowHandle = handle;
	}

	HWND GetGameEngineWindowHWND() {
		return g_GameEngineWindowHandle;
	}

	void CreateConsoleOutput() {
		int hConHandle{ 0 };
		long lStdHandle{ 0 };
		CONSOLE_SCREEN_BUFFER_INFO coninfo{};
		FILE* fp{ nullptr };

		AllocConsole();

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
		coninfo.dwSize.Y = 500;
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

		lStdHandle = reinterpret_cast<long>(GetStdHandle(STD_OUTPUT_HANDLE));
		hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

		fp = _fdopen(hConHandle, "w");

		*stdout = *fp;

		setvbuf(stdout, NULL, _IONBF, 0);

		lStdHandle = reinterpret_cast<long>(GetStdHandle(STD_INPUT_HANDLE));
		hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

		fp = _fdopen(hConHandle, "r");
		*stdin = *fp;
		setvbuf(stdin, NULL, _IONBF, 0);

		lStdHandle = reinterpret_cast<long>(GetStdHandle(STD_ERROR_HANDLE));
		hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

		fp = _fdopen(hConHandle, "w");

		*stderr = *fp;

		setvbuf(stderr, NULL, _IONBF, 0);
		std::ios::sync_with_stdio();
	}

}

#endif
