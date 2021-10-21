#pragma once

#include "GameScene.h"
#include "MeshManager.h"
#include "Renderer.h"
#include "TextureManager.h"

#include "components/CameraComponent.h"
#include "components/MeshComponent.h"
#include "components/ScriptComponent.h"
#include "components/TagComponent.h"
#include "components/TransformationComponent.h"

#include "PawnEngine/engine/scripts/ScriptEngine.h"
#include "PawnEngine/engine/serializer/JsonFileSerializer.h"
#include "PawnEngine/engine/serializer/JsonSerializer.h"
#include "PawnEngine/engine/geometry/Mesh.h"
#include "PawnGraphics/graphics/GraphicsAPI.h"
#include "PawnGraphics/graphics/GraphicsContext.h"
#include "PawnGraphics/graphics/GraphicsShader.h"
#include "PawnGraphics/graphics/GraphicsTexture2D.h"
#include "PawnSystem/system/windows/WindowsAPI.h"
#include "PawnUtils/utils/time/Clock.h"

#include <memory>

namespace pawn::engine {

	class Engine {

		public:
			Engine() = default;
			Engine(const Engine& other) = delete;
			Engine(Engine&& other) noexcept = delete;

			Engine& operator=(const Engine& other) = delete;
			Engine& operator=(Engine&& other) noexcept = delete;

			bool GetEngineRunning() const;
			void SetEngineRunning(bool state);

			bool GetEnginePaused() const;
			void SetEnginePaused(bool state);

			void Init();
			void Init(HWND handle, uint32_t width, uint32_t height);
			void InitGraphics(HWND handle, uint32_t width, uint32_t height);

			void Clear();
			void OnInput();
			void OnCreate();
			void OnUpdate(utils::Clock& clock);
			void OnRender();

			void SaveState(const std::string& path);
			void LoadState(const std::string& path);

			bool HasMeshByName(const std::string& name);
			bool UploadMeshFromFile(const std::string& path);
			const std::shared_ptr<Mesh>& GetMeshByName(const std::string& name);

			bool HasTextureByName(const std::string& name);
			bool UploadTextureFromFile(const std::string& path);
			const std::shared_ptr<graphics::GraphicsTexture2D>& GetTextureByName(const std::string& name);

			inline std::shared_ptr<MeshManager>& GetMeshManager() noexcept { return m_MeshManager; }
			inline std::shared_ptr<TextureManager>& GetTextureManager() noexcept { return m_TextureManager; }
			inline std::shared_ptr<ScriptEngine>& GetScriptEngine() noexcept { return m_ScriptEngine; }
			inline std::shared_ptr<GameScene>& GetScene() noexcept { return m_Scene; }
			inline std::shared_ptr<JsonSerializer>& GetJsonSerializer() noexcept { return m_JsonSerializer; }

			inline std::shared_ptr<graphics::GraphicsContext>& GetContext() noexcept { return m_Context; }
			inline std::shared_ptr<graphics::GraphicsAPI>& GetAPI() noexcept { return m_GraphicsAPI; }
			inline std::shared_ptr<Renderer>& GetRenderer() noexcept { return m_Renderer; }

		private:
			bool m_IsEngineRunning;
			bool m_IsEnginePaused;
			std::shared_ptr<MeshManager> m_MeshManager;
			std::shared_ptr<TextureManager> m_TextureManager;
			std::shared_ptr<ScriptEngine> m_ScriptEngine;
			std::shared_ptr<GameScene> m_Scene;
			std::shared_ptr<JsonSerializer> m_JsonSerializer;

			std::shared_ptr<graphics::GraphicsContext> m_Context;
			std::shared_ptr<graphics::GraphicsAPI> m_GraphicsAPI;
			std::shared_ptr<graphics::GraphicsShader> m_Shader;
			std::shared_ptr<Renderer> m_Renderer;

	};

}
