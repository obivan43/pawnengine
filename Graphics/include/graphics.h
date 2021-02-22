#pragma once

#include "../src/GraphicsContext.h"
#include "../src/GraphicsBindableResource.h"
#include "../src/GraphicsAPI.h"
#include "../src/GraphicsBuffer.h"
#include "../src/GraphicsShader.h"
#include "../src/GraphicsInputLayout.h"
#include "../src/GraphicsRenderer.h"

#ifdef PAWN_DIRECTX11

#include "../src/DirectX11Debug.h"
#include "../src/DirectX11Context.h"
#include "../src/DirectX11API.h"
#include "../src/DirectX11VertexBuffer.h"
#include "../src/DirectX11Shader.h"
#include "../src/DirectX11InputLayout.h"
#include "../src/DirectX11BasicRenderer.h"

#elif PAWN_OPENGL

#include "../src/OpenglDebug.h"
#include "../src/OpenglContext.h"
#include "../src/OpenglAPI.h"
#include "../src/OpenglVertexBuffer.h"
#include "../src/OpenglShader.h"
#include "../src/OpenglInputLayout.h"
#include "../src/OpenglBasicRenderer.h"

#endif

#include "../src/Window.h"
#include "../src/WinAPIWindow.h"
