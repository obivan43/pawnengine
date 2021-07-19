#include "Engine.h"

#include "PawnUtils/utils/logger/Logger.h"

#include "PawnSystem/system/input/KeyboardManager.h"
#include "PawnSystem/system/input/MouseManager.h"

namespace pawn {

	namespace engine {

		void Engine::Init(HWND handle, uint32_t width, uint32_t height) {
			m_Context = graphics::GraphicsContext::Create();
			m_GraphicsAPI = graphics::GraphicsAPI::Create();

			m_Context->Init(handle, width, height);
			m_GraphicsAPI->SetContext(m_Context);

			m_GraphicsAPI->SetClearColor(0.1f, 0.1f, 0.1f);

			m_MeshManager.reset(new MeshManager());
			m_TextureManager.reset(new TextureManager());

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

			m_ScriptEngine.reset(new ScriptEngine());

			m_Scene.reset(new GameScene());
		}

		const std::shared_ptr<graphics::GraphicsMesh>& Engine::GetMeshByName(const std::string& name) {
			return m_MeshManager->GetMeshByName(name);
		}

		bool Engine::HasMeshByName(const std::string& name) {
			return m_MeshManager->HasMeshByName(name);
		}

		bool Engine::UploadMeshFromFile(const std::string& file) {
			return m_MeshManager->UploadMeshFromFile(m_Context, m_Shader, file);
		}

		bool Engine::HasTextureByName(const std::string& name) {
			return m_TextureManager->HasTextureByName(name);
		}

		bool Engine::UploadTextureFromFile(const std::string& file) {
			return m_TextureManager->UploadTextureFromFile(m_Context, file);
		}

		const std::shared_ptr<graphics::GraphicsTexture2D>& Engine::GetTextureByName(const std::string& name) {
			return m_TextureManager->GetTextureByName(name);
		}


		void Engine::Clear() {
			m_GraphicsAPI->Clear();
		}

		void Engine::OnInput() {
			system::MouseManager::Update();
			system::KeyboardManager::Update();

#ifdef TRACE_MOUSE_INPUT
			if (system::MouseManager::ButtonPressed(system::MouseButton::LeftButton)) {
				CONSOLE_TRACE("LEFT BUTTON PRESS")
			}

			if (system::MouseManager::ButtonPressed(system::MouseButton::RightButton)) {
				CONSOLE_TRACE("RIGHT BUTTON PRESS")
			}

			if (system::MouseManager::ButtonReleased(system::MouseButton::LeftButton)) {
				CONSOLE_TRACE("LEFT BUTTON RELEASE")
			}

			if (system::MouseManager::ButtonReleased(system::MouseButton::RightButton)) {
				CONSOLE_TRACE("RIGHT BUTTON RELEASE")
			}

			int32_t x{ system::MouseManager::GetRawMouseX() };
			CONSOLE_TRACE("X {}", x)

			int32_t y{ system::MouseManager::GetRawMouseY() };
			CONSOLE_TRACE("Y {}", y)

			int32_t wheel{ system::MouseManager::GetMouseWheel() };
			CONSOLE_TRACE("WHEEL {}", wheel)
#endif
		}

		void Engine::OnUpdate(utils::Clock& clock) {
			m_Scene->OnUpdate(clock, m_Renderer);
		}

		void Engine::SwapBuffers() {
			m_Context->SwapBuffers();
		}

	}

}
