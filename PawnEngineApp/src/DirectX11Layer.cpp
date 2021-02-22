#include "pch.h"
#include "DirectX11Layer.h"
#include "Application.h"

namespace pawn {

	void DirectX11Layer::OnInit() {
		Application& application = Application::Instance();
		m_GraphicsContext = application.GetGraphicsContext();
		m_GraphicsAPI = application.GetGraphicsAPI();

		static Vertex vertices[] = {
			{ 0.0f,  0.5f },
			{ 0.5f, -0.5f },
			{-0.5f, -0.5f }
		};
		
		const std::initializer_list<GraphicsInputElement> inputElements = {
			{ "Position", GraphicsInputElementType::Float2 }
		};

#ifdef PAWN_DIRECTX11
		m_VertexBuffer.reset(new DirectX11VertexBuffer());
		m_Shader.reset(new DirectX11Shader());
		m_InputLayout.reset(new DirectX11InputLayout());
		m_GraphicsRenderer.reset(new DirectX11BasicRenderer(m_GraphicsContext));
#elif PAWN_OPENGL
		m_VertexBuffer.reset(new OpenglVertexBuffer());
		m_Shader.reset(new OpenglShader());
		m_InputLayout.reset(new OpenglInputLayout());
		m_GraphicsRenderer.reset(new OpenglBasicRenderer(m_GraphicsContext));
#endif
		
		m_VertexBuffer->Init(m_GraphicsContext, vertices, std::size(vertices), sizeof(Vertex));
		m_VertexBuffer->Bind(m_GraphicsContext);

#ifdef PAWN_DIRECTX11
		if (!m_Shader->InitVertexShader(m_GraphicsContext, L"VertexShader.cso")) {
			spdlog::get("console")->error("Vertex shader initialization failed");
		}

		if (!m_Shader->InitPixelShader(m_GraphicsContext, L"PixelShader.cso")) {
			spdlog::get("console")->error("Pixel shader initialization failed");
		}
#elif PAWN_OPENGL
		if (!m_Shader->InitVertexShader(m_GraphicsContext, L"res\\VertexShader.vertex")) {
			spdlog::get("console")->error("Vertex shader initialization failed");
		}

		if (!m_Shader->InitPixelShader(m_GraphicsContext, L"res\\PixelShader.fragment")) {
			spdlog::get("console")->error("Pixel shader initialization failed");
		}
#endif

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
	
	void DirectX11Layer::OnUpdate(Clock clock) {
		UNUSED(clock)
		m_GraphicsRenderer->Draw(m_VertexBuffer);
	}
	
	void DirectX11Layer::OnRelease() {}
	
}
