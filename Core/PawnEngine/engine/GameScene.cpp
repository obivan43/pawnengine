#include "GameScene.h"
#include "GameEntity.h"
#include "Renderer.h"

#include "scripts/ScriptEngine.h"

#include "components/TransformationComponent.h"
#include "components/TagComponent.h"
#include "components/CameraComponent.h"
#include "components/MeshComponent.h"
#include "components/ScriptComponent.h"

#include <string>

namespace pawn {

	namespace engine {

		GameEntity GameScene::CreateEntity(const std::string& name) {
			const entt::entity entityID = m_EnttRegistry.create();

			m_EnttRegistry.emplace<TransformationComponent>(entityID);
			m_EnttRegistry.emplace<TagComponent>(entityID, name == "" ? ("Entity") : name);

			const GameEntity entity(entityID, this);
			return entity;
		}

		void GameScene::DeleteEntity(entt::entity entity) {
			m_EnttRegistry.destroy(entity);
		}

		void GameScene::FindActiveCamera() {
			math::Camera* activeCamera{ nullptr };
			glm::mat4 acitveCameraTransformation;
			auto cameraGroup = m_EnttRegistry.view<TransformationComponent, CameraComponent>();

			for (auto& entity : cameraGroup) {
				auto [transformationComponent, cameraComponent] = cameraGroup.get<TransformationComponent, CameraComponent>(entity);

				if (cameraComponent.IsActiveCamera) {
					activeCamera = &cameraComponent.Camera;
					acitveCameraTransformation = transformationComponent.GetTransformation();
					break;
				}
			}

			m_ActiveCamera = activeCamera;
			m_ActiveCameraView = glm::inverse(acitveCameraTransformation);
		}

		void GameScene::OnCreate(std::shared_ptr<ScriptEngine>& scriptEngine) {
			auto sciptableEntities = m_EnttRegistry.view<ScriptComponent>();
			for (auto& entity : sciptableEntities) {
				auto scriptComponent = sciptableEntities.get<ScriptComponent>(entity);
				
				if (!scriptComponent.FileName.empty()) {
					scriptEngine->ExecOnCreate(scriptComponent.FileName);
				}
			}
		}

		void GameScene::OnUpdate(utils::Clock& clock, std::shared_ptr<ScriptEngine>& scriptEngine) {
			FindActiveCamera();

			auto sciptableEntities = m_EnttRegistry.view<ScriptComponent>();
			for (auto& entity : sciptableEntities) {
				auto scriptComponent = sciptableEntities.get<ScriptComponent>(entity);

				if (!scriptComponent.FileName.empty()) {
					scriptEngine->ExecOnUpdate(scriptComponent.FileName, clock);
				}
			}
		}

		void GameScene::OnRender(utils::Clock& clock, std::shared_ptr<Renderer>& renderer) {
			if (m_ActiveCamera) {
				renderer->BeginScene(*m_ActiveCamera, m_ActiveCameraView);

				auto meshGroup = m_EnttRegistry.view<TransformationComponent, MeshComponent>();
				for (auto& entity : meshGroup) {
					auto [transformationComponent, meshComponent] = meshGroup.get<TransformationComponent, MeshComponent>(entity);
					renderer->DrawMesh(transformationComponent, meshComponent);
				}

				renderer->EndScene();
			}
		}

	}

}
