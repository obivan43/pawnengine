#include "GameScene.h"
#include "GameEntity.h"
#include "Renderer.h"

#include "components/TransformationComponent.h"
#include "components/TagComponent.h"
#include "components/CameraComponent.h"
#include "components/MeshComponent.h"

namespace pawn {

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

	void GameScene::OnUpdate(utils::Clock& clock, std::shared_ptr<Renderer>& renderer) {
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

		if (activeCamera) {
			glm::mat4 view = glm::inverse(acitveCameraTransformation);
			renderer->BeginScene(*activeCamera, view);

			auto meshGroup = m_EnttRegistry.view<TransformationComponent, MeshComponent>();
			for (auto& entity : meshGroup) {
				auto [transformationComponent, meshComponent] = meshGroup.get<TransformationComponent, MeshComponent>(entity);
				renderer->DrawMesh(transformationComponent, meshComponent);
			}

			renderer->EndScene();
		}
	}

}
