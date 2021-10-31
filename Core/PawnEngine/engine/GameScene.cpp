#include "GameScene.h"

#include "GameEntity.h"
#include "Renderer.h"

#include "components/CameraComponent.h"
#include "components/MeshComponent.h"
#include "components/ScriptComponent.h"
#include "components/TagComponent.h"
#include "components/Texture2DComponent.h"
#include "components/TransformationComponent.h"
#include "scripts/ScriptEngine.h"

#include "PawnMath/math/Functions.h"

namespace pawn::engine {

	GameScene::GameScene() : m_ActiveCamera(nullptr), m_ActiveCameraView(glm::mat4(1.0f)), m_ActiveCameraEyePosition(glm::vec3(0.0)) {}

	GameEntity GameScene::CreateEntity(const std::string& name) {
		const entt::entity entityID = m_EnttRegistry.create();

		m_EnttRegistry.emplace<TransformationComponent>(entityID);
		m_EnttRegistry.emplace<TagComponent>(entityID, name == std::string() ? ("Entity") : name);

		const GameEntity entity(entityID, this);
		return entity;
	}

	GameEntity GameScene::CreateEntity(uint32_t hint, const std::string& name) {
		const entt::entity entityID = m_EnttRegistry.create(static_cast<entt::entity>(hint));

		m_EnttRegistry.emplace<TransformationComponent>(entityID);
		m_EnttRegistry.emplace<TagComponent>(entityID, name == std::string() ? ("Entity") : name);

		const GameEntity entity(entityID, this);
		return entity;
	}

	void GameScene::DeleteEntity(entt::entity entity) {
		m_EnttRegistry.destroy(entity);
	}

	void GameScene::Clear() {
		m_EnttRegistry.clear();
		m_ActiveCamera = nullptr;
		m_ActiveCameraView = glm::mat4(1.0f);
	}

	void GameScene::FindActiveCamera() {
		math::Camera* activeCamera{ nullptr };

		glm::vec3 cameraPosition(0.0f);
		float pitch = 0.0f;
		float yaw = 0.0f;

		auto cameraGroup = m_EnttRegistry.view<TransformationComponent, CameraComponent>();

		for (auto& entity : cameraGroup) {
			auto [transformationComponent, cameraComponent] = cameraGroup.get<TransformationComponent, CameraComponent>(entity);

			if (cameraComponent.IsActiveCamera) {
				activeCamera = &cameraComponent.Camera;
				cameraPosition = transformationComponent.Position;

				if (transformationComponent.Rotation.x > 90.0f) {
					transformationComponent.Rotation.x = 89.95f;
				}
				else if (transformationComponent.Rotation.x < -90.0f) {
					transformationComponent.Rotation.x = -89.95f;
				}

				pitch = transformationComponent.Rotation.x;
				yaw = transformationComponent.Rotation.y;
				break;
			}
		}

		m_ActiveCamera = activeCamera;
		m_ActiveCameraView = pawn::math::cameraMatrix(cameraPosition, pitch, yaw);
		m_ActiveCameraEyePosition = cameraPosition;
	}

	void GameScene::OnCreate(std::shared_ptr<ScriptEngine>& scriptEngine) {
		if (scriptEngine.get() && !scriptEngine->GetIsPaused()) {
			auto sciptableEntities = m_EnttRegistry.view<ScriptComponent>();
			for (auto& entity : sciptableEntities) {
				auto scriptComponent = sciptableEntities.get<ScriptComponent>(entity);

				if (!scriptComponent.FileName.empty()) {
					scriptEngine->ExecOnCreate(scriptComponent.FileName, pawn::engine::GameEntity(entity, this));
				}
			}
		}
	}

	void GameScene::OnUpdate(utils::Clock& clock, std::shared_ptr<ScriptEngine>& scriptEngine) {
		FindActiveCamera();

		if (scriptEngine.get() && !scriptEngine->GetIsPaused()) {
			auto sciptableEntities = m_EnttRegistry.view<ScriptComponent>();
			for (auto& entity : sciptableEntities) {
				auto scriptComponent = sciptableEntities.get<ScriptComponent>(entity);

				if (!scriptComponent.FileName.empty()) {
					scriptEngine->ExecOnUpdate(scriptComponent.FileName, clock, pawn::engine::GameEntity(entity, this));
				}
			}
		}
	}

	void GameScene::OnRender(std::shared_ptr<Renderer>& renderer) {
		if (renderer.get() && m_ActiveCamera) {
			renderer->BeginScene(*m_ActiveCamera, m_ActiveCameraView);

			auto directionalLights = m_EnttRegistry.view<DirectionalLightComponent>();
			for (auto& entity : directionalLights) {
				auto directionalLightComponent = directionalLights.get<DirectionalLightComponent>(entity);
				renderer->UpdateLights(directionalLightComponent, m_ActiveCameraEyePosition);
				break;
			}

			auto texturedMeshGroup = m_EnttRegistry.view<TransformationComponent, MeshComponent, Texture2DComponent>();
			for (auto& entity : texturedMeshGroup) {
				auto [transformationComponent, meshComponent, texture2DComponent] = texturedMeshGroup.get<TransformationComponent, MeshComponent, Texture2DComponent>(entity);
				renderer->DrawMesh(transformationComponent, meshComponent, texture2DComponent);
			}

			renderer->EndScene();
		}
	}

}
