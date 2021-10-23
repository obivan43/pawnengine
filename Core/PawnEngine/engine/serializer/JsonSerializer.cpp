#include "JsonSerializer.h"

#include "PawnEngine/engine/GameEntity.h"
#include "PawnEngine/engine/components/CameraComponent.h"
#include "PawnEngine/engine/components/MeshComponent.h"
#include "PawnEngine/engine/components/ScriptComponent.h"
#include "PawnEngine/engine/components/TagComponent.h"
#include "PawnEngine/engine/components/Texture2DComponent.h"
#include "PawnEngine/engine/components/TransformationComponent.h"

namespace pawn::engine {

	JsonSerializer::JsonSerializer(std::shared_ptr<GameScene>& scene) : m_Scene(scene) {}

	nlohmann::json JsonSerializer::JsonScene() {
		nlohmann::json jsonScene;
		
		jsonScene["entities"] = JsonEntities();
		jsonScene["environment"] = JsonEnvironment();

		return jsonScene;
	}

	nlohmann::json JsonSerializer::JsonEnvironment() {
		nlohmann::json json;

		const glm::vec3& ambientLightColor = m_Scene->GetEnvironment()->GetAmbientLightColor();
		const glm::vec3& directionalLightColor = m_Scene->GetEnvironment()->GetDirectionalLightColor();
		const glm::vec3& directionalLightPosition = m_Scene->GetEnvironment()->GetDirectionalLightPosition();
		json = {  
			{
				"ambientLightColor", {
						{ "x", ambientLightColor.x },
						{ "y", ambientLightColor.y },
						{ "z", ambientLightColor.z }
				}
			},
			{
				"ambientLightIntensity", m_Scene->GetEnvironment()->GetAmbientLightIntensity()
			},
			{
				"directionalLightColor", {
						{ "x", directionalLightColor.x },
						{ "y", directionalLightColor.y },
						{ "z", directionalLightColor.z }
				}
			},
			{
				"directionalLightPosition", {
						{ "x", directionalLightPosition.x },
						{ "y", directionalLightPosition.y },
						{ "z", directionalLightPosition.z }
				}
			},
			{
				"directionalLightIntensity", m_Scene->GetEnvironment()->GetDirectionalLightIntensity()
			}
		};

		return json;
	}

	nlohmann::json JsonSerializer::JsonEntities() {
		nlohmann::json json = nlohmann::json::array();

		std::vector<entt::entity> entities;
		entt::registry& registry = m_Scene->GetRegistry();
		registry.each([&](entt::entity entity) {
			entities.push_back(entity);
		});

		for (entt::entity id : entities) {
			nlohmann::json tmp = JsonEntityById(id);
			json.push_back(tmp);
		}

		return json;
	}

	nlohmann::json JsonSerializer::JsonEntityIds() {
		std::vector<entt::entity> entities;
		entt::registry& registry = m_Scene->GetRegistry();
		registry.each([&](entt::entity entity) {
			entities.push_back(entity);
		});

		return nlohmann::json::parse(entities);
	}

	nlohmann::json JsonSerializer::JsonEntityById(entt::entity id) {
		GameEntity entity(id, m_Scene.get());

		nlohmann::json json;

		if (entity.HasComponent<TagComponent>()) {
			TagComponent& tagComponent = entity.GetComponent<TagComponent>();
			json["has_tag_component"] = true;
			json["tag_component"] = {
				{ "tag", tagComponent.Tag }
			};
		}
		else {
			json["has_tag_component"] = false;
		}

		if (entity.HasComponent<TransformationComponent>()) {
			TransformationComponent& transformationComponent = entity.GetComponent<TransformationComponent>();
			json["has_transformation_component"] = true;
			json["transformation_component"] = {
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
		}
		else {
			json["has_transformation_component"] = false;
		}


		if (entity.HasComponent<CameraComponent>()) {
			CameraComponent& cameraComponent = entity.GetComponent<CameraComponent>();
			json["has_camera_component"] = true;
			json["camera_component"] = {
				{ "is_active", cameraComponent.IsActiveCamera },
				{ "projection", static_cast<uint32_t>(cameraComponent.Camera.GetType()) }
			};
		}
		else {
			json["has_camera_component"] = false;
		}


		if (entity.HasComponent<MeshComponent>()) {
			MeshComponent& meshComponent = entity.GetComponent<MeshComponent>();
			json["has_mesh_component"] = true;
			json["mesh_component"] = {
				{ "name", meshComponent.MeshName }
			};
		}
		else {
			json["has_mesh_component"] = false;
		}

		if (entity.HasComponent<ScriptComponent>()) {
			ScriptComponent& scriptComponent = entity.GetComponent<ScriptComponent>();
			json["has_script_component"] = true;
			json["script_component"] = {
				{ "file", scriptComponent.FileName }
			};
		}
		else {
			json["has_script_component"] = false;
		}

		if (entity.HasComponent<Texture2DComponent>()) {
			Texture2DComponent& texture2DComponent = entity.GetComponent<Texture2DComponent>();
			json["has_texture2D_component"] = true;
			json["texture2D_component"] = {
				{ "name", texture2DComponent.TextureName },
				{ "color", {
					{ "x", texture2DComponent.Color.x },
					{ "y", texture2DComponent.Color.y },
					{ "z", texture2DComponent.Color.z }
				} }
			};
		}
		else {
			json["has_texture2D_component"] = false;
		}

		return json;
	}

	void JsonSerializer::ParseJsonScene(
		const nlohmann::json& json,
		std::shared_ptr<MeshManager>& meshManager,
		std::shared_ptr<TextureManager>& textureManager
	) {

		if (json.contains("entities")) {
			ParseJsonEntities(json["entities"], meshManager, textureManager);
		}

		if (json.contains("environment")) {
			ParseJsonEnvironment(json["environment"]);
		}
	}

	void JsonSerializer::ParseJsonEntities(
		const nlohmann::json& json,
		std::shared_ptr<MeshManager>& meshManager,
		std::shared_ptr<TextureManager>& textureManager
	) {
		for (auto& element : json) {
			std::string tag;
			tag = element["tag_component"]["tag"].get<std::string>();

			GameEntity gameEntity = m_Scene->CreateEntity(tag);

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

	void JsonSerializer::ParseJsonEnvironment(const nlohmann::json& json) {
		if (json.contains("ambientLightColor")) {
			glm::vec3 color;
			color.x = json["ambientLightColor"]["x"].get<float>();
			color.y = json["ambientLightColor"]["y"].get<float>();
			color.z = json["ambientLightColor"]["z"].get<float>();
			m_Scene->GetEnvironment()->SetAmbientLightColor(color);
		}

		if (json.contains("ambientLightIntensity")) {
			float intensity = json["ambientLightIntensity"].get<float>();
			m_Scene->GetEnvironment()->SetAmbientLightIntensity(intensity);
		}

		if (json.contains("directionalLightColor")) {
			glm::vec3 color;
			color.x = json["directionalLightColor"]["x"].get<float>();
			color.y = json["directionalLightColor"]["y"].get<float>();
			color.z = json["directionalLightColor"]["z"].get<float>();
			m_Scene->GetEnvironment()->SetDirectionalLightColor(color);
		}

		if (json.contains("directionalLightPosition")) {
			glm::vec3 position;
			position.x = json["directionalLightPosition"]["x"].get<float>();
			position.y = json["directionalLightPosition"]["y"].get<float>();
			position.z = json["directionalLightPosition"]["z"].get<float>();
			m_Scene->GetEnvironment()->SetDirectionalLightPosition(position);
		}

		if (json.contains("directionalLightIntensity")) {
			float intensity = json["directionalLightIntensity"].get<float>();
			m_Scene->GetEnvironment()->SetDirectionalLightIntensity(intensity);
		}
	}

}
