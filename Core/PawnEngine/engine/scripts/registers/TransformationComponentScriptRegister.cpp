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
				"viewForward", sol::property(&pawn::engine::TransformationComponent::GetViewForward),
				"viewUp", sol::property(&pawn::engine::TransformationComponent::GetViewUp),
				"viewForwardUpCross", sol::property(&pawn::engine::TransformationComponent::GetViewForwardUpCross),
				"viewPosition", sol::property(&pawn::engine::TransformationComponent::GetViewPosition)
			);
		}

	}

}