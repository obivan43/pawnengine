#include "TransformationComponentScriptRegister.h"

#include "PawnEngine/engine/components/TransformationComponent.h"

#include "glm.hpp"

namespace pawn::engine {

	void TransformationComponentScriptRegister::Register(sol::state& lua) {
		lua.new_usertype<pawn::engine::TransformationComponent>("TransformationComponent",
			sol::constructors<pawn::engine::TransformationComponent(), pawn::engine::TransformationComponent(const pawn::engine::TransformationComponent&)>(),
			"position", &pawn::engine::TransformationComponent::Position,
			"rotation", &pawn::engine::TransformationComponent::Rotation,
			"scale", &pawn::engine::TransformationComponent::Scale,
			"front", sol::property(&pawn::engine::TransformationComponent::GetFront),
			"frontUpCross", sol::property(&pawn::engine::TransformationComponent::GetFrontUpCross)
			);
	}

}
