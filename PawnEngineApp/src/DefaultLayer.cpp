﻿#include "pch.h"
#include "DefaultLayer.h"
#include "Application.h"

namespace pawn {

	DefaultLayer::DefaultLayer() {
		Application& application = Application::Instance();
		m_GraphicsContext = application.GetGraphicsContext();
		m_GraphicsAPI = application.GetGraphicsAPI();

		int32_t width, height, bitsPerPixel;
		unsigned char* data = StbImageLoader::Load("res\\textures\\brick.jpg", &width, &height, &bitsPerPixel);
		StbImageLoader::Free(data);
		
#ifdef PAWN_DIRECTX11
		m_VertexBuffer.reset(new DirectX11VertexBuffer());
		m_IndexBuffer.reset(new DirectX11IndexBuffer());
		m_ContantBuffer.reset(new DirectX11ContantBuffer());
		m_Shader.reset(new DirectX11Shader());
		m_InputLayout.reset(new DirectX11InputLayout());
		m_GraphicsRenderer.reset(new DirectX11BasicRenderer(m_GraphicsContext));

		m_VertexShaderPath = L"res\\shaders\\directx_shaders\\VertexShader.cso";
		m_PixelShaderPath = L"res\\shaders\\directx_shaders\\PixelShader.cso";
#elif PAWN_OPENGL
		m_VertexBuffer.reset(new OpenglVertexBuffer());
		m_IndexBuffer.reset(new OpenglIndexBuffer());
		m_ContantBuffer.reset(new OpenglConstantBuffer());
		m_Shader.reset(new OpenglShader());
		m_InputLayout.reset(new OpenglInputLayout());
		m_GraphicsRenderer.reset(new OpenglBasicRenderer(m_GraphicsContext));

		m_VertexShaderPath = L"res\\shaders\\opengl_shaders\\VertexShader.vertex";
		m_PixelShaderPath = L"res\\shaders\\opengl_shaders\\PixelShader.fragment";
#else
		m_VertexBuffer.reset(new GraphicsBuffer());
		m_Shader.reset(new GraphicsShader());
		m_InputLayout.reset(new GraphicsInputLayout());
		m_GraphicsRenderer.reset(new GraphicsRenderer(m_GraphicsContext));
#endif
	}
	
	void DefaultLayer::OnInit() {
		ColoredVertex vertices[] = {
			{ { 0.0f,  0.5f }, { 1.0f, 0.0f, 0.0f } },
			{ { 0.5f, -0.5f }, { 0.0f, 1.0f, 1.0f } },
			{ {-0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f } }
		};

		uint16_t indices[] = { 0, 1, 2 };

		Transformation transformation = {
			{
				(3.0f / 4.0f) * std::cos(0.0f),		std::sin(0.0f), 0.0f,	0.0f,
				(3.0f / 4.0f) * -std::sin(0.0f),	std::cos(0.0f), 0.0f,	0.0f,
				0.0f,								0.0f,			 1.0f,	0.0f,
				0.0f,								0.0f,			 0.0f,	1.0f
			}
		};
		
		const std::initializer_list<GraphicsInputElement> inputElements = {
			{ "Position", GraphicsInputElementType::Float2 },
			{ "Color", GraphicsInputElementType::Float3 }
		};
		
		m_VertexBuffer->Init(m_GraphicsContext, vertices, 3, sizeof(ColoredVertex), GraphicsBufferUsageTypeEnum::StaticBuffer);
		m_VertexBuffer->Bind(m_GraphicsContext);

		m_IndexBuffer->Init(m_GraphicsContext, indices, 3, sizeof(uint16_t), GraphicsBufferUsageTypeEnum::StaticBuffer);
		m_IndexBuffer->Bind(m_GraphicsContext);
		
		if (!m_Shader->InitVertexShader(m_GraphicsContext, m_VertexShaderPath)) {
			spdlog::get("console")->error("Vertex shader initialization failed");
		}

		void* vertexShaderInfo = m_Shader->GetVertexShaderInfo();

		if (!m_Shader->InitPixelShader(m_GraphicsContext, m_PixelShaderPath)) {
			spdlog::get("console")->error("Pixel shader initialization failed");
		}

		if (!m_Shader->Link()) {
			spdlog::get("console")->error("Shader linking failed");
		}
		
		m_Shader->Bind(m_GraphicsContext);
		
		m_ContantBuffer->Init(m_GraphicsContext, &transformation, 1, sizeof(Transformation), GraphicsBufferUsageTypeEnum::DynamicBuffer);
		m_ContantBuffer->InitLocation(m_GraphicsContext, m_Shader, "Transformation");
		m_ContantBuffer->Bind(m_GraphicsContext);

		m_InputLayout->Init(m_GraphicsContext, inputElements, vertexShaderInfo);
		m_InputLayout->Bind(m_GraphicsContext);
	}
	
	void DefaultLayer::OnUpdate(Clock clock) {
		float angle = clock.TotalTime();
		Transformation transformation = {
			{
				(3.0f / 4.0f) * std::cos(angle),	std::sin(angle), 0.0f,	0.0f,
				(3.0f / 4.0f) * -std::sin(angle),	std::cos(angle), 0.0f,	0.0f,
				0.0f,								0.0f,			 1.0f,	0.0f,
				0.0f,								0.0f,			 0.0f,	1.0f
			}
		};

		m_ContantBuffer->Update(m_GraphicsContext, &transformation, 1, sizeof(Transformation));
		m_ContantBuffer->Bind(m_GraphicsContext);
		m_IndexBuffer->Bind(m_GraphicsContext);
		
		m_GraphicsRenderer->DrawIndexed(m_IndexBuffer);
	}
	
	void DefaultLayer::OnRelease() {}
	
}