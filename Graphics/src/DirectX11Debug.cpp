#include "pch.h"
#include "DirectX11Debug.h"

#if defined(DEBUG) | defined(_DEBUG)
#ifdef DirectX11Call

void DirectX11CallDebug(HRESULT result, const char* file, unsigned int line, const char* expression) {
	if (FAILED(result))  {
		spdlog::get("console")->error("DirectX call error: {}, {}, {}", file, line, expression);
		__debugbreak();
	}
	
	spdlog::get("console")->trace("DirectX call: {}, {}, {}", file, line, expression);
}

#endif
#endif