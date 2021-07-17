#pragma once

#include "../graphics/GraphicsAPI.h"
#include "../graphics/GraphicsContext.h"
#include "../graphics/GraphicsBindableResource.h"
#include "../graphics/GraphicsAPI.h"
#include "../graphics/GraphicsBuffer.h"
#include "../graphics/GraphicsShader.h"
#include "../graphics/GraphicsInputLayout.h"
#include "../graphics/GraphicsRenderer.h"
#include "../graphics/GraphicsTexture2D.h"

#ifdef PAWN_DIRECTX11

#include "../graphics/directx/buffer/DirectX11VertexBuffer.h"
#include "../graphics/directx/buffer/DirectX11ContantBuffer.h"
#include "../graphics/directx/buffer/DirectX11IndexBuffer.h"
#include "../graphics/directx/debug/DirectX11Debug.h"
#include "../graphics/directx/Directx11Context.h"
#include "../graphics/directx/DirectX11API.h"
#include "../graphics/directx/DirectX11Texture2D.h"
#include "../graphics/directx/DirectX11Shader.h"
#include "../graphics/directx/DirectX11InputLayout.h"
#include "../graphics/directx/DirectX11Renderer.h"

#endif

#include "../graphics/data/GraphicsMesh.h"