#include "pch.h"
#include "Scene.h"
#include "Entity.h"
#include "Components.h"
#include "Renderer.h"

namespace pawn {

	Entity Scene::CreateEntity(const std::string& name) {
		static uint32_t namedEntityID = 0;
		const entt::entity entityID = m_EnttRegistry.create();
		
		m_EnttRegistry.emplace<TransformationComponent>(entityID);
		m_EnttRegistry.emplace<NameComponent>(entityID, name == "" ? ("Entity_" + namedEntityID++) : name);
		
		const Entity entity(entityID, this);
		return entity;
	}
	
	void Scene::DeleteEntity(Entity& entity) {
		m_EnttRegistry.destroy(entity);
	}

	void Scene::OnUpdate(Clock& clock) {
		Camera* activeCamera = nullptr;
		glm::mat4 acitveCameraTransformation;
		auto cameraGroup = m_EnttRegistry.view<TransformationComponent, CameraComponent>();
		for (auto& entity : cameraGroup) {
			auto [transformationComponent, cameraComponent] = cameraGroup.get<TransformationComponent, CameraComponent>(entity);

			if (cameraComponent.m_IsActiveCamera) {
				activeCamera = &cameraComponent.m_Camera;
				acitveCameraTransformation = transformationComponent.m_Transformation;
				break;
			}
		}

		if (activeCamera) {
			glm::mat4 view = glm::inverse(acitveCameraTransformation);
			Renderer::BeginScene(*activeCamera, view);

			auto meshGroup = m_EnttRegistry.view<TransformationComponent, MeshComponent>();
			for (auto& entity : meshGroup) {
				auto [transformationComponent, meshComponent] = meshGroup.get<TransformationComponent, MeshComponent>(entity);
				Renderer::DrawMesh(transformationComponent, meshComponent);
			}

			Renderer::EndScene();
		}
	}

}