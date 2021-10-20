#pragma once

namespace pawn::engine {

	struct LightComponent {

		LightComponent() = default;
		LightComponent(const LightComponent& other) = default;
		LightComponent(LightComponent&& other) noexcept = default;

		LightComponent& operator=(const LightComponent& other) = default;
		LightComponent& operator=(LightComponent&& other) noexcept = default;
	};

}
