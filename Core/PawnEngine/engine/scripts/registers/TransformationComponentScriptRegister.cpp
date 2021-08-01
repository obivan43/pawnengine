#include "TransformationComponentScriptRegister.h"

#include "PawnEngine/engine/components/TransformationComponent.h"

#include "glm.hpp"

namespace pawn {

	namespace engine {

		void TransformationComponentScriptRegister::Register(sol::state& lua) {
			lua.new_usertype<pawn::engine::TransformationComponent>("TransformationComponent",
				sol::constructors<pawn::engine::TransformationComponent(), pawn::engine::TransformationComponent(const pawn::engine::TransformationComponent&)>(),
				"position", &pawn::engine::TransformationComponent::Position,
				"rotation", &pawn::engine::TransformationComponent::Rotation,
				"scale", &pawn::engine::TransformationComponent::Scale,
				"__add_position", [](const pawn::engine::TransformationComponent& l, const glm::vec3& r) { return  glm::vec3(l.Position + r); },
				"__add_position_x", [](const pawn::engine::TransformationComponent& l, float r) { return l.Position.x + r; },
				"__add_position_y", [](const pawn::engine::TransformationComponent& l, float r) { return l.Position.y + r; },
				"__add_position_z", [](const pawn::engine::TransformationComponent& l, float r) { return l.Position.z + r; },
				"__add_rotation", [](const pawn::engine::TransformationComponent& l, const glm::vec3& r) { return  glm::vec3(l.Rotation + r); },
				"__add_rotation_x", [](const pawn::engine::TransformationComponent& l, float r) { return l.Rotation.x + r; },
				"__add_rotation_y", [](const pawn::engine::TransformationComponent& l, float r) { return l.Rotation.y + r; },
				"__add_rotation_z", [](const pawn::engine::TransformationComponent& l, float r) { return l.Rotation.z + r; },
				"__add_scale", [](const pawn::engine::TransformationComponent& l, const glm::vec3& r) { return  glm::vec3(l.Scale + r); },
				"__add_scale_x", [](const pawn::engine::TransformationComponent& l, float r) { return l.Scale.x + r; },
				"__add_scale_y", [](const pawn::engine::TransformationComponent& l, float r) { return l.Scale.y + r; },
				"__add_scale_z", [](const pawn::engine::TransformationComponent& l, float r) { return l.Scale.z + r; },
				"__sub_position", [](const pawn::engine::TransformationComponent& l, const glm::vec3& r) { return  glm::vec3(l.Position - r); },
				"__sub_position_x", [](const pawn::engine::TransformationComponent& l, float r) { return l.Position.x - r; },
				"__sub_position_y", [](const pawn::engine::TransformationComponent& l, float r) { return l.Position.y - r; },
				"__sub_position_z", [](const pawn::engine::TransformationComponent& l, float r) { return l.Position.z - r; },
				"__sub_rotation", [](const pawn::engine::TransformationComponent& l, const glm::vec3& r) { return  glm::vec3(l.Rotation - r); },
				"__sub_rotation_x", [](const pawn::engine::TransformationComponent& l, float r) { return l.Rotation.x - r; },
				"__sub_rotation_y", [](const pawn::engine::TransformationComponent& l, float r) { return l.Rotation.y - r; },
				"__sub_rotation_z", [](const pawn::engine::TransformationComponent& l, float r) { return l.Rotation.z - r; },
				"__sub_scale", [](const pawn::engine::TransformationComponent& l, const glm::vec3& r) { return  glm::vec3(l.Scale - r); },
				"__sub_scale_x", [](const pawn::engine::TransformationComponent& l, float r) { return l.Scale.x - r; },
				"__sub_scale_y", [](const pawn::engine::TransformationComponent& l, float r) { return l.Scale.y - r; },
				"__sub_scale_z", [](const pawn::engine::TransformationComponent& l, float r) { return l.Scale.z - r; }
			);
		}

	}

}