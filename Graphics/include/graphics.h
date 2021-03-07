#pragma once

#include "../src/Mesh.h"

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
#include "../src/DirectX11Context.h"
#include "../src/DirectX11API.h"
#include "../src/DirectX11VertexBuffer.h"
#include "../src/DirectX11ContantBuffer.h"
#include "../src/DirectX11IndexBuffer.h"
#include "../src/DirectX11Shader.h"
#include "../src/DirectX11InputLayout.h"
#include "../src/DirectX11BasicRenderer.h"
#include "../src/DirectX11Texture2D.h"

#elif PAWN_OPENGL

#include "../src/Opengl.h"
#include "../src/OpenglDebug.h"
#include "../src/OpenglContext.h"
#include "../src/OpenglAPI.h"
#include "../src/OpenglVertexBuffer.h"
#include "../src/OpenglConstantBuffer.h"
#include "../src/OpenglIndexBuffer.h"
#include "../src/OpenglShader.h"
#include "../src/OpenglInputLayout.h"
#include "../src/OpenglBasicRenderer.h"
#include "../src/OpenglTexture2D.h"
#include "../src/OpenglUniformManager.h"

#endif

#include "../src/Window.h"
#include "../src/WinAPIWindow.h"
