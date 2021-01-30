#pragma once

#ifdef PAWN_DIRECTX11

#if defined(DEBUG) | defined(_DEBUG)

#include "dxerr.h"

#ifndef DirectX11Call
#define DirectX11Call(x) \
{ \
	HRESULT result = (x); \
	if (FAILED(result)) \
	{ \
		DXTrace(__FILEW__, (DWORD)__LINE__, result, L#x, true); \
		__debugbreak(); \
	} \
} \

#endif
#else
#ifndef DirectX11Call
#define DirectX11Call(x) (x)
#endif
#endif

#endif
