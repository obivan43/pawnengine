#include "pch.h"
#include "DefaultLayer.h"
#include "Application.h"

namespace pawn {

	DefaultLayer::DefaultLayer() : m_Camera({0.0f, 0.0f, 4.0f}) {
		Application& application = Application::Instance();
		m_GraphicsContext = application.GetGraphicsContext();
		m_GraphicsAPI = application.GetGraphicsAPI();

		m_Transformation = GraphicsBuffer::Create(GraphicsBufferEnum::ConstantBuffer);
		m_ViewProjection = GraphicsBuffer::Create(GraphicsBufferEnum::ConstantBuffer);

		m_Shader = GraphicsShader::Create();
		m_GraphicsRenderer = GraphicsRenderer::Create(m_GraphicsContext);
		
#ifdef PAWN_DIRECTX11
		m_VertexShaderPath = L"res\\shaders\\directx_shaders\\VertexShader.cso";
		m_PixelShaderPath = L"res\\shaders\\directx_shaders\\PixelShader.cso";
#elif PAWN_OPENGL
		m_VertexShaderPath = L"res\\shaders\\opengl_shaders\\VertexShader.glsl";
		m_PixelShaderPath = L"res\\shaders\\opengl_shaders\\PixelShader.glsl";
#endif
	}
	
	void DefaultLayer::OnInit() {
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

		m_MeshManager.UploadMeshFromFile(m_GraphicsContext, m_Shader, "res\\models\\smoothsphere.obj");

		m_Transformation->Init(m_GraphicsContext, nullptr, 1, sizeof(glm::mat4), GraphicsBufferUsageTypeEnum::DynamicBuffer);
		m_Transformation->InitLocation(m_GraphicsContext, m_Shader, "Transformation", 0);
		m_Transformation->Bind(m_GraphicsContext);

		m_ViewProjection->Init(m_GraphicsContext, nullptr, 1, sizeof(ViewProjection), GraphicsBufferUsageTypeEnum::DynamicBuffer);
		m_ViewProjection->InitLocation(m_GraphicsContext, m_Shader, "ViewProjection", 1);
		m_ViewProjection->Bind(m_GraphicsContext);

		m_Sphere = m_Scene.CreateEntity();
		m_Sphere.AddComponent<MeshComponent>(m_MeshManager.GetMeshByName("smoothsphere"));
	}
	
	void DefaultLayer::OnUpdate(Clock clock) {
		m_CameraMovement.MoveCamera(m_Camera, clock);
		m_Camera.RecalculateView();

		m_ViewProjectionMatrix = { m_Camera.GetProjection(), m_Camera.GetView() };
		m_ViewProjection->Update(m_GraphicsContext, &m_ViewProjectionMatrix, 1, sizeof(ViewProjection));
		m_ViewProjection->Bind(m_GraphicsContext);

		TransformComponent& transformComponent = m_Sphere.GetComponent<TransformComponent>();
		m_Transformation->Update(m_GraphicsContext, &transformComponent.m_Transform, 1, sizeof(glm::mat4));
		m_Transformation->Bind(m_GraphicsContext);

		MeshComponent& meshComponent = m_Sphere.GetComponent<MeshComponent>();
		meshComponent.m_Mesh->Bind(m_GraphicsContext);
		m_GraphicsRenderer->DrawIndexed(meshComponent.m_Mesh->GetIndexBuffer());
	}
	
	void DefaultLayer::OnRelease() {}
	
}
