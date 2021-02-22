#pragma once

#ifdef PAWN_DIRECTX11

#if defined(DEBUG) | defined(_DEBUG)

#include "dxerr.h"

void DirectX11CallDebug(HRESULT result, const char* file, unsigned int line, const char* expression);

#ifndef DirectX11Call
#define DirectX11Call(x) \
{ \
	HRESULT result = (x); \
	DirectX11CallDebug(result, __FILE__, __LINE__, #x);\
} \

#endif
#else
#ifndef DirectX11Call
#define DirectX11Call(x) (x);
#endif
#endif

#endif
