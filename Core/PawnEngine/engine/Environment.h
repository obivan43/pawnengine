#pragma once

#include "data/Light.h"

namespace pawn::engine {

	class Environment {

		public:
			Environment();
			Environment(const Environment& other) = delete;
			Environment(Environment&& other) noexcept = delete;

			Environment& operator=(const Environment& other) = delete;
			Environment& operator=(Environment&& other) noexcept = delete;

			inline Light& GetLight() noexcept { return m_Light; }
			inline const Light& GetLight() const noexcept { return m_Light; }

			inline void SetLight(const Light& light) noexcept { m_Light = light; }

		private:
			Light m_Light;
		
	};

}
