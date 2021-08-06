#include "JsonSerializer.h"

#include "PawnEngine/engine/GameEntity.h"
#include "PawnEngine/engine/components/TagComponent.h"
#include "PawnEngine/engine/components/TransformationComponent.h"
#include "PawnEngine/engine/components/CameraComponent.h"
#include "PawnEngine/engine/components/MeshComponent.h"
#include "PawnEngine/engine/components/ScriptComponent.h"

namespace pawn {

	namespace engine {

		JsonSerializer::JsonSerializer(std::shared_ptr<GameScene>& scene) : m_Scene(scene) {}

		json JsonSerializer::GetEntityIds() {
			std::vector<entt::entity> entities;
			entt::registry& registry = m_Scene->GetRegistry();
			registry.each([&](entt::entity entity) {
				entities.push_back(entity);
			});

			return json::parse(entities);
		}

		json JsonSerializer::GetEntityById(entt::entity id) {
			GameEntity entity(id, m_Scene.get());

			json j;
			j["id"] = entity.GetEntity();

			if (entity.HasComponent<TagComponent>()) {
				TagComponent& tagComponent = entity.GetComponent<TagComponent>();
				j["has_tag_component"] = true;
				j["tag_component"] = {
					{ "tag", tagComponent.Tag }
				};
			} else {
				j["has_tag_component"] = false;
			}

			if (entity.HasComponent<TransformationComponent>()) {
				TransformationComponent& transformationComponent = entity.GetComponent<TransformationComponent>();
				j["has_transformation_component"] = true;
				j["transformation_component"] = {
					{ "position", {
						{ "x", transformationComponent.Position.x },
						{ "y", transformationComponent.Position.y },
						{ "z", transformationComponent.Position.z }
					} },

					{ "rotation", {
						{ "x", transformationComponent.Rotation.x },
						{ "y", transformationComponent.Rotation.y },
						{ "z", transformationComponent.Rotation.z }
					} },

					{ "scale", {
						{ "x", transformationComponent.Scale.x },
						{ "y", transformationComponent.Scale.y },
						{ "z", transformationComponent.Scale.z }
					} },
				};
			} else {
				j["has_transformation_component"] = false;
			}


			if (entity.HasComponent<CameraComponent>()) {
				CameraComponent& cameraComponent = entity.GetComponent<CameraComponent>();
				j["has_camera_component"] = true;
				j["camera_component"] = {
					{ "is_active", cameraComponent.IsActiveCamera },
					{ "projection", static_cast<uint32_t>(cameraComponent.Camera.GetType()) }
				};
			} else {
				j["has_camera_component"] = false;
			}

			
			if (entity.HasComponent<MeshComponent>()) {
				MeshComponent& meshComponent = entity.GetComponent<MeshComponent>();
				j["has_mesh_component"] = true;
				j["mesh_component"] = {
					{ "name", meshComponent.MeshName }
				};
			} else {
				j["has_mesh_component"] = false;
			}

			if (entity.HasComponent<ScriptComponent>()) {
				ScriptComponent& scriptComponent = entity.GetComponent<ScriptComponent>();
				j["has_script_component"] = true;
				j["script_component"] = {
					{ "file", scriptComponent.FileName }
				};
			} else {
				j["has_script_component"] = false;
			}

			return j;
		}


	}

}