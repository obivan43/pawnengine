#include "Engine.h"

#include "PawnUtils/utils/logger/Logger.h"

#include "PawnSystem/system/input/KeyboardManager.h"

namespace pawn {

	namespace engine {

		void Engine::Init(HWND handle, uint32_t width, uint32_t height) {
			m_Context = graphics::GraphicsContext::Create();
			m_GraphicsAPI = graphics::GraphicsAPI::Create();

			m_Context->Init(handle, width, height);
			m_GraphicsAPI->SetContext(m_Context);

			m_GraphicsAPI->SetClearColor(0.1f, 0.1f, 0.1f);

			m_MeshManager.reset(new MeshManager());

			m_Shader = graphics::GraphicsShader::Create();
			if (!m_Shader->InitVertexShader(m_Context, L"res\\assets\\shaders\\directx_shaders\\VertexShader.cso")) {
				CONSOLE_ERROR("Vertex shader initialization failed")
			}

			if (!m_Shader->InitPixelShader(m_Context, L"res\\assets\\shaders\\directx_shaders\\PixelShader.cso")) {
				CONSOLE_ERROR("Pixel shader initialization failed")
			}

			m_Renderer.reset(new Renderer());
			m_Renderer->Init(m_Context, m_GraphicsAPI, width, height);
			m_Renderer->SetShader(m_Context, m_Shader);

			m_Scene.reset(new GameScene());
		}

		const std::shared_ptr<graphics::GraphicsMesh>& Engine::GetMeshByPath(const std::string& path) {
			return m_MeshManager->GetMeshByPath(path);
		}

		bool Engine::HasMeshByPath(const std::string& path) {
			return m_MeshManager->HasMeshByPath(path);
		}

		void Engine::UploadMeshFromFile(const std::string& file) {
			m_MeshManager->UploadMeshFromFile(m_Context, m_Shader, file);
		}

		void Engine::Clear() {
			m_GraphicsAPI->Clear();
		}

		void Engine::OnInput() {
			system::KeyboardManager::Update();
		}

		void Engine::OnUpdate(utils::Clock& clock) {
			m_Scene->OnUpdate(clock, m_Renderer);
		}

		void Engine::SwapBuffers() {
			m_Context->SwapBuffers();
		}

	}

}