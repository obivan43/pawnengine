#pragma once

#include "../src/GraphicsContext.h"
#include "../src/GraphicsBindableResource.h"
#include "../src/GraphicsAPI.h"
#include "../src/GraphicsBuffer.h"
#include "../src/GraphicsShader.h"
#include "../src/GraphicsInputLayout.h"
#include "../src/GraphicsRenderer.h"
#include "../src/GraphicsTexture2D.h"

#ifdef PAWN_DIRECTX11

#include "../src/DirectX11Debug.h"
#include "../src/Directx11Context.h"
#include "../src/DirectX11API.h"
#include "../src/DirectX11VertexBuffer.h"
#include "../src/DirectX11ContantBuffer.h"
#include "../src/DirectX11IndexBuffer.h"
#include "../src/DirectX11Texture2D.h"
#include "../src/DirectX11Shader.h"
#include "../src/DirectX11InputLayout.h"
#include "../src/DirectX11Renderer.h"

#endif

#include "../src/GraphicsMesh.h"