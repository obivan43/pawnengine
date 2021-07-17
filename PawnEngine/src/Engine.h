#pragma once

#include "GameScene.h"
#include "MeshManager.h"
#include "Renderer.h"

#include "PawnGraphics/src/GraphicsContext.h"
#include "PawnGraphics/src/GraphicsAPI.h"

#include "PawnUtils/utils/time/Clock.h"

#include "PawnSystem/system/windows/WindowsAPI.h"

#include <memory>

namespace pawn {

	class Engine {

		public:
			Engine() = default;
			Engine(const Engine& other) = delete;
			Engine(Engine&& other) noexcept = delete;

			Engine& operator=(const Engine& other) = delete;
			Engine& operator=(Engine&& other) noexcept = delete;

			void Init(HWND handle, uint32_t width, uint32_t height);

			void Clear();
			void OnInput();
			void OnUpdate(Clock& clock);
			void SwapBuffers();

			bool HasMeshByPath(const std::string& path);
			void UploadMeshFromFile(const std::string& file);
			const std::shared_ptr<GraphicsMesh>& GetMeshByPath(const std::string& path);

			std::shared_ptr<GameScene>& GetScene() { return m_Scene; }
			std::shared_ptr<MeshManager>& GetMeshManager() { return m_MeshManager; }
			std::shared_ptr<GraphicsContext>& GetContext() { return m_Context; }
			std::shared_ptr<GraphicsAPI>& GetAPI() { return m_GraphicsAPI; }
			std::shared_ptr<Renderer>& GetRenderer() { return m_Renderer; }

		private:
			std::shared_ptr<MeshManager> m_MeshManager;
			std::shared_ptr<GraphicsContext> m_Context;
			std::shared_ptr<GraphicsAPI> m_GraphicsAPI;
			std::shared_ptr<GraphicsShader> m_Shader;
			std::shared_ptr<Renderer> m_Renderer;
			std::shared_ptr<GameScene> m_Scene;
	};

}
