#include "pch.h"
#include "DefaultLayer.h"
#include "Application.h"

#include <DirectXMath.h>

namespace pawn {

	DefaultLayer::DefaultLayer() : m_Camera({0.0f, 0.0f, 4.0f}) {
		Application& application = Application::Instance();
		m_GraphicsContext = application.GetGraphicsContext();
		m_GraphicsAPI = application.GetGraphicsAPI();
		
#ifdef PAWN_DIRECTX11
		m_VertexBuffer.reset(new DirectX11VertexBuffer());
		m_IndexBuffer.reset(new DirectX11IndexBuffer());
		m_Transformation.reset(new DirectX11ContantBuffer());
		m_ViewProjection.reset(new DirectX11ContantBuffer());
		m_Texture.reset(new DirectX11Texture2D());
		m_Shader.reset(new DirectX11Shader());
		m_InputLayout.reset(new DirectX11InputLayout());
		m_GraphicsRenderer.reset(new DirectX11BasicRenderer(m_GraphicsContext));

		m_VertexShaderPath = L"res\\shaders\\directx_shaders\\VertexShader.cso";
		m_PixelShaderPath = L"res\\shaders\\directx_shaders\\PixelShader.cso";
#elif PAWN_OPENGL
		m_VertexBuffer.reset(new OpenglVertexBuffer());
		m_IndexBuffer.reset(new OpenglIndexBuffer());
		m_Transformation.reset(new OpenglConstantBuffer());
		m_ViewProjection.reset(new OpenglConstantBuffer());
		m_Texture.reset(new OpenglTexture2D());
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
		Vertex vertices[] = {
			{ { -0.5f, -0.5f, 0.0f },  { 0.0f, 0.0f } },
			{ { -0.5f,  0.5f, 0.0f },  { 1.0f, 0.0f } },
			{ {  0.5f,  0.5f, 0.0f },  { 1.0f, 1.0f } },
			{ {  0.5f, -0.5f, 0.0f },  { 0.0f, 1.0f } },
		};

		uint16_t indices[] = { 0, 1, 2, 0, 2, 3 };
		
		const std::initializer_list<GraphicsInputElement> inputElements = {
			{ "Position", GraphicsInputElementType::Float3 },
			{ "TextureCoordinates", GraphicsInputElementType::Float2 }
		};
		
		m_VertexBuffer->Init(m_GraphicsContext, vertices, 4, sizeof(Vertex), GraphicsBufferUsageTypeEnum::StaticBuffer);
		m_VertexBuffer->Bind(m_GraphicsContext);

		m_IndexBuffer->Init(m_GraphicsContext, indices, 6, sizeof(uint16_t), GraphicsBufferUsageTypeEnum::StaticBuffer);
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

		int32_t width, height, bitsPerPixel;
		unsigned char* data = StbImageLoader::Load("res\\textures\\brick.jpg", &width, &height, &bitsPerPixel);
		m_Texture->Init(
			m_GraphicsContext,
			data, width, height, bitsPerPixel,
			{ GraphicsTextureWrap::CLAMP, GraphicsTextureFilter::LINEAR, GraphicsTextureFormat::RGBA }
		);
		m_Texture->Bind(m_GraphicsContext);
		StbImageLoader::Free(data);

		m_InputLayout->Init(m_GraphicsContext, inputElements, vertexShaderInfo);
		m_InputLayout->Bind(m_GraphicsContext);

		Transformation transformation;
		glm::mat4 transformationMatrix = transformation.GetModelMatrix();
		m_Transformation->Init(m_GraphicsContext, &transformationMatrix, 1, sizeof(DirectX::XMMATRIX), GraphicsBufferUsageTypeEnum::StaticBuffer);
		m_Transformation->InitLocation(m_GraphicsContext, m_Shader, "Transformation", 0);
		m_Transformation->Bind(m_GraphicsContext);

		m_Camera.RecalculateView();
		m_viewProjectionMatrix = { m_Camera.GetProjection(), m_Camera.GetView() };
		m_ViewProjection->Init(m_GraphicsContext, &m_viewProjectionMatrix, 1, sizeof(ViewProjection), GraphicsBufferUsageTypeEnum::DynamicBuffer);
		m_ViewProjection->InitLocation(m_GraphicsContext, m_Shader, "ViewProjection", 1);
		m_ViewProjection->Bind(m_GraphicsContext);
		
#ifdef PAWN_OPENGL
		OpenglUniformManager::SetUniform(m_Shader, "Texture", 0);
#endif
	}
	
	void DefaultLayer::OnUpdate(Clock clock) {
		m_CameraMovement.MoveCamera(m_Camera, clock);
		
		m_Camera.RecalculateView();
		m_viewProjectionMatrix = { m_Camera.GetProjection(), m_Camera.GetView() };
		m_ViewProjection->Update(m_GraphicsContext, &m_viewProjectionMatrix, 1, sizeof(ViewProjection));
		
		m_IndexBuffer->Bind(m_GraphicsContext);
		m_Transformation->Bind(m_GraphicsContext);
		m_ViewProjection->Bind(m_GraphicsContext);
		
		m_GraphicsRenderer->DrawIndexed(m_IndexBuffer);
	}
	
	void DefaultLayer::OnRelease() {}
	
}
