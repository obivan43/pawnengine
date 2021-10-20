#include "DirectX11Debug.h"
#include "DirectX11Exception.h"

#include "PawnUtils/utils/logger/Logger.h"

#if defined(DEBUG) | defined(_DEBUG)
#ifdef DirectX11Call

void DirectX11CallDebug(HRESULT result, const char* file, unsigned int line, const char* expression, pawn::graphics::DirectX11DebugInfoManager& infoManager) {
	if (FAILED(result))  {
		CONSOLE_ERROR("DirectX call error: {}, {}, {}", file, line, expression)
		{
			std::vector<std::string> messages = infoManager.GetMessages(); 
			if (!messages.empty()) {
				throw pawn::graphics::DirectX11Exception(result, file, line, expression, messages);
			}
		}
	}
}

#endif
#endif
