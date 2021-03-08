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
		Window& window = application.GetWindow();
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

		Renderer::Init(application.GetGraphicsContext(), application.GetGraphicsAPI(), window.GetWidth(), window.GetHeight());
		Renderer::SetShader(context, m_Shader);

		m_MeshManager.UploadMeshFromFile(context, m_Shader, "res\\models\\smoothsphere.obj");
		m_MeshManager.UploadMeshFromFile(context, m_Shader, "res\\models\\sphere.obj");
		m_MeshManager.UploadMeshFromFile(context, m_Shader, "res\\models\\cube.obj");

		auto entity = m_Scene.CreateEntity("sphere");
		entity.AddComponent<MeshComponent>(m_MeshManager.GetMeshByName("sphere"));

		auto camera = m_Scene.CreateEntity("camera");
		CameraComponent& cameraComponent = camera.AddComponent<CameraComponent>();
		cameraComponent.m_Camera.SetPerspective();
		cameraComponent.m_IsActiveCamera = true;

		TransformationComponent& transformationComponent = camera.GetComponent<TransformationComponent>();
		transformationComponent.m_Transformation[3].z = 4.0f;
	}
	
	void DefaultLayer::OnUpdate(Clock& clock) {
		m_Scene.OnUpdate(clock);
	}
	
	void DefaultLayer::OnRelease() {}
	
}
