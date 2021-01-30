#include "pch.h"
#include "GraphicsAPI.h"

namespace pawn {
	
	GraphicsAPIEnum GraphicsAPI::m_graphicsApi =
#ifdef PAWN_DIRECTX11
		GraphicsAPIEnum::DirectX11;
#else
#ifdef PAWN_OPENGL
		GraphicsAPIEnum::OpenGL;
#else
#ifndef PAWN_DIRECTX11 && PAWN_OPENGL
		GraphicsAPIEnum::None;
#endif // None
#endif // PAWN_OPENGL
#endif // PAWN_DIRECTX11

	void GraphicsAPI::Clear(float r, float g, float b, float a) {}
	
}