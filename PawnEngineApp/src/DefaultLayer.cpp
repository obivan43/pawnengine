#include "pch.h"
#include "DefaultLayer.h"
#include "Application.h"

namespace pawn {

	DefaultLayer::DefaultLayer() {
		Application& application = Application::Instance();
		m_GraphicsContext = application.GetGraphicsContext();
		m_GraphicsAPI = application.GetGraphicsAPI();
		
#ifdef PAWN_DIRECTX11
		m_VertexBuffer.reset(new DirectX11VertexBuffer());
		m_Shader.reset(new DirectX11Shader());
		m_InputLayout.reset(new DirectX11InputLayout());
		m_GraphicsRenderer.reset(new DirectX11BasicRenderer(m_GraphicsContext));

		m_VertexShaderPath = L"VertexShader.cso";
		m_PixelShaderPath = L"PixelShader.cso";
#elif PAWN_OPENGL
		m_VertexBuffer.reset(new OpenglVertexBuffer());
		m_Shader.reset(new OpenglShader());
		m_InputLayout.reset(new OpenglInputLayout());
		m_GraphicsRenderer.reset(new OpenglBasicRenderer(m_GraphicsContext));

		m_VertexShaderPath = L"res\\VertexShader.vertex";
		m_PixelShaderPath = L"res\\PixelShader.fragment";
#else
		m_VertexBuffer.reset(new GraphicsBuffer());
		m_Shader.reset(new GraphicsShader());
		m_InputLayout.reset(new GraphicsInputLayout());
		m_GraphicsRenderer.reset(new GraphicsRenderer(m_GraphicsContext));
#endif
	}
	
	void DefaultLayer::OnInit() {
		static Vertex vertices[] = {
			{ 0.0f,  0.5f },
			{ 0.5f, -0.5f },
			{-0.5f, -0.5f }
		};
		
		const std::initializer_list<GraphicsInputElement> inputElements = {
			{ "Position", GraphicsInputElementType::Float2 }
		};
		
		m_VertexBuffer->Init(m_GraphicsContext, vertices, static_cast<uint32_t>(std::size(vertices)), sizeof(Vertex));
		m_VertexBuffer->Bind(m_GraphicsContext);

		if (!m_Shader->InitVertexShader(m_GraphicsContext, m_VertexShaderPath)) {
			spdlog::get("console")->error("Vertex shader initialization failed");
		}

		if (!m_Shader->InitPixelShader(m_GraphicsContext, m_PixelShaderPath)) {
			spdlog::get("console")->error("Pixel shader initialization failed");
		}

		if (!m_Shader->Link()) {
			spdlog::get("console")->error("Shader linking failed");
		}
		
		m_Shader->Bind(m_GraphicsContext);

#ifdef PAWN_DIRECTX11
		Microsoft::WRL::ComPtr<ID3DBlob> blob;
		D3DReadFileToBlob(L"VertexShader.cso", &blob);
		m_InputLayout->Init(m_GraphicsContext, inputElements, blob.Get());
#else
		m_InputLayout->Init(m_GraphicsContext, inputElements, nullptr);
#endif
		
		m_InputLayout->Bind(m_GraphicsContext);
	}
	
	void DefaultLayer::OnUpdate(Clock clock) {
		UNUSED(clock)
		m_GraphicsRenderer->Draw(m_VertexBuffer);
	}
	
	void DefaultLayer::OnRelease() {}
	
}
