#include "pch.h"
#include "DefaultLayer.h"
#include "Application.h"

namespace pawn {

	DefaultLayer::DefaultLayer() {
		m_Shader = GraphicsShader::Create();
		
#ifdef PAWN_DIRECTX11
		m_VertexShaderPath = L"res\\shaders\\directx_shaders\\VertexShader.cso";
		m_PixelShaderPath = L"res\\shaders\\directx_shaders\\PixelShader.cso";
#elif PAWN_OPENGL
		m_VertexShaderPath = L"res\\shaders\\opengl_shaders\\VertexShader.glsl";
		m_PixelShaderPath = L"res\\shaders\\opengl_shaders\\PixelShader.glsl";
#endif
	}
	
	void DefaultLayer::OnInit() {
		Application& application = Application::Instance();
		std::shared_ptr<GraphicsContext>& context = application.GetGraphicsContext();

		if (!m_Shader->InitVertexShader(context, m_VertexShaderPath)) {
			spdlog::get("console")->error("Vertex shader initialization failed");
		}

		if (!m_Shader->InitPixelShader(context, m_PixelShaderPath)) {
			spdlog::get("console")->error("Pixel shader initialization failed");
		}

		if (!m_Shader->Link()) {
			spdlog::get("console")->error("Shader linking failed");
		}

		Renderer::SetShader(context, m_Shader);
		Renderer::Init(application.GetGraphicsContext(), application.GetGraphicsAPI());

		m_MeshManager.UploadMeshFromFile(context, m_Shader, "res\\models\\smoothsphere.obj");
		m_MeshManager.UploadMeshFromFile(context, m_Shader, "res\\models\\sphere.obj");
		m_MeshManager.UploadMeshFromFile(context, m_Shader, "res\\models\\cube.obj");

		m_Entity = m_Scene.CreateEntity("sphere");
		m_Entity.AddComponent<MeshComponent>(m_MeshManager.GetMeshByName("smoothsphere"));

		m_Camera = m_Scene.CreateEntity("camera");
		CameraComponent& cameraComponent = m_Camera.AddComponent<CameraComponent>();
		cameraComponent.m_Camera.SetPerspective();
		cameraComponent.m_IsActiveCamera = true;

		TransformationComponent& transformationComponent = m_Camera.GetComponent<TransformationComponent>();
		glm::vec4& position = transformationComponent.m_Transformation[3];
		position.z = 4.0f;
	}
	
	void DefaultLayer::OnUpdate(Clock& clock) {
		CameraComponent& cameraComponent = m_Camera.GetComponent<CameraComponent>();
		glm::mat4 view = glm::inverse(m_Camera.GetComponent<TransformationComponent>().m_Transformation);

		Renderer::BeginScene(cameraComponent.m_Camera, view);

		Renderer::Submit(m_Entity);

		Renderer::EndScene();
	}
	
	void DefaultLayer::OnRelease() {}
	
}
