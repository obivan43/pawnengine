#include "pch.h"
#include "DefaultLayer.h"
#include "Application.h"

namespace pawn {

	DefaultLayer::DefaultLayer() : m_Camera({0.0f, 0.0f, 4.0f}) {
		Application& application = Application::Instance();
		m_GraphicsContext = application.GetGraphicsContext();
		m_GraphicsAPI = application.GetGraphicsAPI();

		m_VertexBuffer = GraphicsBuffer::Create(GraphicsBufferEnum::VertexBuffer);
		m_IndexBuffer = GraphicsBuffer::Create(GraphicsBufferEnum::IndexBuffer);
		m_Transformation = GraphicsBuffer::Create(GraphicsBufferEnum::ConstantBuffer);
		m_ViewProjection = GraphicsBuffer::Create(GraphicsBufferEnum::ConstantBuffer);
		m_Texture = GraphicsTexture2D::Create();

		m_Shader = GraphicsShader::Create();
		m_InputLayout = GraphicsInputLayout::Create();
		m_GraphicsRenderer = GraphicsRenderer::Create(m_GraphicsContext);
		
#ifdef PAWN_DIRECTX11
		m_VertexShaderPath = L"res\\shaders\\directx_shaders\\VertexShader.cso";
		m_PixelShaderPath = L"res\\shaders\\directx_shaders\\PixelShader.cso";
#elif PAWN_OPENGL
		m_VertexShaderPath = L"res\\shaders\\opengl_shaders\\VertexShader.vertex";
		m_PixelShaderPath = L"res\\shaders\\opengl_shaders\\PixelShader.fragment";
#endif
	}
	
	void DefaultLayer::OnInit() {
		m_ModelLoader.LoadModel("res\\models\\cube.obj");
		std::vector<float>* vertices = m_ModelLoader.GetVertexData();
		std::vector<uint16_t>* indices = m_ModelLoader.GetIndexData();
		
		const std::initializer_list<GraphicsInputElement> inputElements = {
			{ "Position", GraphicsInputElementType::Float3 },
			{ "Normal", GraphicsInputElementType::Float3 },
			{ "TextureCoordinates", GraphicsInputElementType::Float2 }
		};
		
		m_VertexBuffer->Init(m_GraphicsContext, vertices->data(), static_cast<uint32_t>(vertices->size()), sizeof(Vertex), GraphicsBufferUsageTypeEnum::StaticBuffer);
		m_VertexBuffer->Bind(m_GraphicsContext);

		m_IndexBuffer->Init(m_GraphicsContext, indices->data(), static_cast<uint32_t>(indices->size()), sizeof(uint16_t), GraphicsBufferUsageTypeEnum::StaticBuffer);
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

		glm::mat4 transformationMatrix = m_TransformationMatrix.GetModelMatrix();
		m_Transformation->Init(m_GraphicsContext, &transformationMatrix, 1, sizeof(glm::mat4), GraphicsBufferUsageTypeEnum::StaticBuffer);
		m_Transformation->InitLocation(m_GraphicsContext, m_Shader, "Transformation", 0);
		m_Transformation->Bind(m_GraphicsContext);

		m_Camera.RecalculateView();
		m_ViewProjectionMatrix = { m_Camera.GetProjection(), m_Camera.GetView() };
		m_ViewProjection->Init(m_GraphicsContext, &m_ViewProjectionMatrix, 1, sizeof(ViewProjection), GraphicsBufferUsageTypeEnum::DynamicBuffer);
		m_ViewProjection->InitLocation(m_GraphicsContext, m_Shader, "ViewProjection", 1);
		m_ViewProjection->Bind(m_GraphicsContext);
		
#ifdef PAWN_OPENGL
		OpenglUniformManager::SetUniform(m_Shader, "Texture", 0);
#endif
	}
	
	void DefaultLayer::OnUpdate(Clock clock) {
		m_CameraMovement.MoveCamera(m_Camera, clock);
		m_Camera.RecalculateView();
		
		m_ViewProjectionMatrix = { m_Camera.GetProjection(), m_Camera.GetView() };
		m_ViewProjection->Update(m_GraphicsContext, &m_ViewProjectionMatrix, 1, sizeof(ViewProjection));
		m_ViewProjection->Bind(m_GraphicsContext);
		m_IndexBuffer->Bind(m_GraphicsContext);

		m_Transformation->Bind(m_GraphicsContext);
		m_GraphicsRenderer->DrawIndexed(m_IndexBuffer);
	}
	
	void DefaultLayer::OnRelease() {}
	
}
