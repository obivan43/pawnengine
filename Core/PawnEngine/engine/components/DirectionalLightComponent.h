#pragma once

#include "PawnEngine/engine/data/DirectionalLight.h"

namespace pawn::engine {

	struct DirectionalLightComponent {

		DirectionalLightComponent() = default;
		DirectionalLightComponent(const DirectionalLight& light);

		DirectionalLightComponent(const DirectionalLightComponent& other) = default;
		DirectionalLightComponent(DirectionalLightComponent&& other) noexcept = default;

		DirectionalLightComponent& operator=(const DirectionalLightComponent& other) = default;
		DirectionalLightComponent& operator=(DirectionalLightComponent&& other) noexcept = default;

		inline operator DirectionalLight& () noexcept { return Light; }
		inline operator const DirectionalLight& () const noexcept { return Light; }

		DirectionalLight Light;
	};

}
