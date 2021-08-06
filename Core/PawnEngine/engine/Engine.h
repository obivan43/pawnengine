#pragma once

#include "GameScene.h"
#include "MeshManager.h"
#include "Renderer.h"
#include "TextureManager.h"

#include "components\TagComponent.h"
#include "components\CameraComponent.h"
#include "components\TransformationComponent.h"
#include "components\MeshComponent.h"
#include "components\ScriptComponent.h"

#include "PawnEngine/engine/scripts/ScriptEngine.h"
#include "PawnEngine/engine/serializer/JsonSerializer.h"

#include "PawnGraphics/graphics/GraphicsContext.h"
#include "PawnGraphics/graphics/GraphicsAPI.h"
#include "PawnGraphics/graphics/GraphicsShader.h"
#include "PawnGraphics/graphics/GraphicsTexture2D.h"

#include "PawnUtils/utils/time/Clock.h"

#include "PawnSystem/system/windows/WindowsAPI.h"

#include <memory>

namespace pawn {

	namespace engine {

		class Engine {

			public:
				Engine() = default;
				Engine(const Engine & other) = delete;
				Engine(Engine && other) noexcept = delete;

				Engine& operator=(const Engine & other) = delete;
				Engine& operator=(Engine && other) noexcept = delete;

				bool GetEngineRunning() const;
				void SetEngineRunning(bool state);

				void Init();
				void Init(HWND handle, uint32_t width, uint32_t height);
				void InitGraphics(HWND handle, uint32_t width, uint32_t height);

				void Clear();
				void OnInput();
				void OnCreate();
				void OnUpdate(utils::Clock& clock);
				void OnRender();

				bool HasMeshByName(const std::string & name);
				bool UploadMeshFromFile(const std::string & file);
				const std::shared_ptr<graphics::GraphicsMesh>& GetMeshByName(const std::string & name);

				bool HasTextureByName(const std::string& name);
				bool UploadTextureFromFile(const std::string& file);
				const std::shared_ptr<graphics::GraphicsTexture2D>& GetTextureByName(const std::string& name);

				std::shared_ptr<MeshManager>& GetMeshManager() { return m_MeshManager; }
				std::shared_ptr<TextureManager>& GetTextureManager() { return m_TextureManager; }
				std::shared_ptr<ScriptEngine>& GetScriptEngine() { return m_ScriptEngine; }
				std::shared_ptr<GameScene>& GetScene() { return m_Scene; }
				std::shared_ptr<JsonSerializer>& GetJsonSerializer() { return m_JsonSerializer; }

				std::shared_ptr<graphics::GraphicsContext>& GetContext() { return m_Context; }
				std::shared_ptr<graphics::GraphicsAPI>& GetAPI() { return m_GraphicsAPI; }
				std::shared_ptr<Renderer>& GetRenderer() { return m_Renderer; }

			private:
				bool m_IsEngineRunning;
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

}
