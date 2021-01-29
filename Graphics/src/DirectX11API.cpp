#include "pch.h"
#include "DirectX11API.h"

#ifdef PAWN_DIRECTX11

#pragma comment(lib, "d3d11.lib")

namespace pawn {
	
	DirectX11API::~DirectX11API() {}

	void DirectX11API::Clear() {}

	void DirectX11API::SetClearColor(float r, float g, float b, float a) {}
	
}

#endif
