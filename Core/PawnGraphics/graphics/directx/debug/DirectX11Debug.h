#pragma once

#include "DirectX11DebugInfoManager.h"

#ifdef PAWN_DIRECTX11

	#if defined(DEBUG) | defined(_DEBUG)

	#include "dxerr.h"

	void DirectX11CallDebug(HRESULT result, const char* file, unsigned int line, const char* expression, pawn::graphics::DirectX11DebugInfoManager& infoManager);

		#ifndef DirectX11Call
			#define DirectX11Call(x) \
			{ \
				pawn::graphics::DirectX11DebugInfoManager& infoManager = pawn::graphics::DirectX11DebugInfoManager::Instance(); \
				infoManager.Set(); \
				HRESULT result = (x); \
				DirectX11CallDebug(result, __FILE__, __LINE__, #x, infoManager);\
			} \

		#endif
	#else
		#ifndef DirectX11Call
			#define DirectX11Call(x) (x);
		#endif
	#endif

#endif
