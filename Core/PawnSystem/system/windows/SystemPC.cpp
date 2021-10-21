#include "SystemPC.h"

#include <fcntl.h>
#include <fstream>
#include <io.h>
#include <iostream>
#include <stdio.h>

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
		HANDLE lStdHandle{ 0 };
		CONSOLE_SCREEN_BUFFER_INFO coninfo{};
		FILE* fp{ nullptr };

		AllocConsole();

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
		coninfo.dwSize.Y = 500;
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

		lStdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		hConHandle = _open_osfhandle(reinterpret_cast<intptr_t>(lStdHandle), _O_TEXT);

		fp = _fdopen(hConHandle, "w");

		*stdout = *fp;

		setvbuf(stdout, NULL, _IONBF, 0);

		lStdHandle = GetStdHandle(STD_INPUT_HANDLE);
		hConHandle = _open_osfhandle(reinterpret_cast<intptr_t>(lStdHandle), _O_TEXT);

		fp = _fdopen(hConHandle, "r");
		*stdin = *fp;
		setvbuf(stdin, NULL, _IONBF, 0);

		lStdHandle = GetStdHandle(STD_ERROR_HANDLE);
		hConHandle = _open_osfhandle(reinterpret_cast<intptr_t>(lStdHandle), _O_TEXT);

		fp = _fdopen(hConHandle, "w");

		*stderr = *fp;

		setvbuf(stderr, NULL, _IONBF, 0);
		std::ios::sync_with_stdio();
	}

}

#endif
