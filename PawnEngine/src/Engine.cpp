#include "pch.h"
#include "Engine.h"

namespace pawn {

	void Engine::Init(HWND handle, uint32_t width, uint32_t height) {
		m_Context = GraphicsContext::Create();
		m_GraphicsAPI = GraphicsAPI::Create();

		m_Context->Init(handle, width, height);
		m_GraphicsAPI->SetContext(m_Context);

		m_GraphicsAPI->SetClearColor(0.1f, 0.1f, 0.1f);

		m_MeshManager.reset(new MeshManager());

		m_Shader = GraphicsShader::Create();
		if (!m_Shader->InitVertexShader(m_Context, L"res\\assets\\shaders\\directx_shaders\\VertexShader.cso")) {
			CONSOLE_ERROR("Vertex shader initialization failed")
		}

		if (!m_Shader->InitPixelShader(m_Context, L"res\\assets\\shaders\\directx_shaders\\PixelShader.cso")) {
			CONSOLE_ERROR("Pixel shader initialization failed")
		}

		m_Renderer.reset(new Renderer());
		m_Renderer->Init(m_Context, m_GraphicsAPI, width, height);
		m_Renderer->SetShader(m_Context, m_Shader);

		m_Scene.reset(new Scene());
	}

	const std::shared_ptr<Mesh>& Engine::GetMeshByName(const std::string& name) {
		return m_MeshManager->GetMeshByName(name);
	}

	void Engine::UploadMeshFromFile(const std::string& file) {
		m_MeshManager->UploadMeshFromFile(m_Context, m_Shader, file);
	}

	void Engine::Clear() {
		m_GraphicsAPI->Clear();
	}

	void Engine::OnUpdate(Clock& clock) {
		m_Scene->OnUpdate(clock, m_Renderer);
	}

	void Engine::SwapBuffers() {
		m_Context->SwapBuffers();
	}

}

