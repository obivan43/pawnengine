#include "pch.h"
#include "DirectX11Debug.h"

void DirectX11CallDebug(HRESULT result, const char* function) {
	if (FAILED(result))  {
		spdlog::error("DirectX call error: {}, {}, {}", __FILE__, __LINE__, function);
		__debugbreak();
	}
	
	spdlog::debug("DirectX call: {}, {}, {}", __FILE__, __LINE__, function);
}