#pragma once

#ifdef PAWN_DIRECTX11

#if defined(DEBUG) | defined(_DEBUG)

#include "dxerr.h"

void DirectX11CallDebug(HRESULT result, const char* function);

#ifndef DirectX11Call
#define DirectX11Call(x) \
{ \
	HRESULT result = (x); \
	DirectX11CallDebug(result, #x);\
} \

#endif
#else
#ifndef DirectX11Call
#define DirectX11Call(x) (x);
#endif
#endif

#endif
