#include "JsonSerializer.h"

#include "PawnEngine/engine/GameEntity.h"
#include "PawnEngine/engine/components/TagComponent.h"
#include "PawnEngine/engine/components/TransformationComponent.h"
#include "PawnEngine/engine/components/CameraComponent.h"
#include "PawnEngine/engine/components/MeshComponent.h"
#include "PawnEngine/engine/components/ScriptComponent.h"
#include "PawnEngine/engine/components/Texture2DComponent.h"

namespace pawn {

	namespace engine {

		JsonSerializer::JsonSerializer(std::shared_ptr<GameScene>& scene) : m_Scene(scene) {}

		json JsonSerializer::JsonEntities() {
			json j = json::array();
			
			std::vector<entt::entity> entities;
			entt::registry& registry = m_Scene->GetRegistry();
			registry.each([&](entt::entity entity) {
				entities.push_back(entity);
			});

			for (entt::entity id : entities) {
				json tmp = JsonEntityById(id);
				j.push_back(tmp);
			}

			return j;
		}

		json JsonSerializer::JsonEntityIds() {
			std::vector<entt::entity> entities;
			entt::registry& registry = m_Scene->GetRegistry();
			registry.each([&](entt::entity entity) {
				entities.push_back(entity);
			});

			return json::parse(entities);
		}

		json JsonSerializer::JsonEntityById(entt::entity id) {
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

			if (entity.HasComponent<Texture2DComponent>()) {
				Texture2DComponent& texture2DComponent = entity.GetComponent<Texture2DComponent>();
				j["has_texture2D_component"] = true;
				j["texture2D_component"] = {
					{ "name", texture2DComponent.TextureName },
					{ "color", {
						{ "x", texture2DComponent.Color.x },
						{ "y", texture2DComponent.Color.y },
						{ "z", texture2DComponent.Color.z }
					} }
				};
			}
			else {
				j["has_texture2D_component"] = false;
			}

			return j;
		}

		void JsonSerializer::ParseJsonEntities(const json& j, std::shared_ptr<MeshManager>& meshManager, std::shared_ptr<TextureManager>& textureManager) {
			for (auto& element : j) {
				uint32_t id = element["id"].get<uint32_t>();

				std::string tag;
				tag = element["tag_component"]["tag"].get<std::string>();

				GameEntity gameEntity = m_Scene->CreateEntity(id, tag);

				TransformationComponent& transformation = gameEntity.GetComponent<TransformationComponent>();
				transformation.Position.x = element["transformation_component"]["position"]["x"].get<float>();
				transformation.Position.y = element["transformation_component"]["position"]["y"].get<float>();
				transformation.Position.z = element["transformation_component"]["position"]["z"].get<float>();

				transformation.Rotation.x = element["transformation_component"]["rotation"]["x"].get<float>();
				transformation.Rotation.y = element["transformation_component"]["rotation"]["y"].get<float>();
				transformation.Rotation.z = element["transformation_component"]["rotation"]["z"].get<float>();

				transformation.Scale.x = element["transformation_component"]["scale"]["x"].get<float>();
				transformation.Scale.y = element["transformation_component"]["scale"]["y"].get<float>();
				transformation.Scale.z = element["transformation_component"]["scale"]["z"].get<float>();

				if (element.contains("has_camera_component") && element["has_camera_component"].get<bool>()) {
					CameraComponent& cameraComponent = gameEntity.AddComponent<CameraComponent>();
					cameraComponent.IsActiveCamera = element["camera_component"]["is_active"].get<bool>();
					
					uint32_t type = element["camera_component"]["projection"].get<uint32_t>();
					switch (type) {
						case pawn::math::CameraType::Perspective:
							cameraComponent.Camera.SetPerspective();
							break;
						case pawn::math::CameraType::Orthographic:
							cameraComponent.Camera.SetOrthographic();
							break;
						default:
							cameraComponent.Camera.SetPerspective();
							break;
					}
				}

				if (element.contains("has_mesh_component") && element["has_mesh_component"].get<bool>()) {
					std::string meshName = element["mesh_component"]["name"].get<std::string>();
					if (meshManager->HasMeshByName(meshName)) {
						gameEntity.AddComponent<MeshComponent>(meshManager->GetMeshByName(meshName), meshName);
					}
				}

				if (element.contains("has_script_component") && element["has_script_component"].get<bool>()) {
					std::string file = element["script_component"]["file"].get<std::string>();
					gameEntity.AddComponent<ScriptComponent>(file);
				}

				if (element.contains("has_texture2D_component") && element["has_texture2D_component"].get<bool>()) {
					std::string texture2DName = element["texture2D_component"]["name"].get<std::string>();
					if (textureManager->HasTextureByName(texture2DName)) {
						Texture2DComponent& texture2DComponent = gameEntity.AddComponent<Texture2DComponent>(textureManager->GetTextureByName(texture2DName), texture2DName);
						texture2DComponent.Color.x = element["texture2D_component"]["color"]["x"].get<float>();
						texture2DComponent.Color.y = element["texture2D_component"]["color"]["y"].get<float>();
						texture2DComponent.Color.z = element["texture2D_component"]["color"]["z"].get<float>();
					}
				}
			}
		}

	}

}
