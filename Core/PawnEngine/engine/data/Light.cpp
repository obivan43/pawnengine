#include "Light.h"

namespace pawn::engine {

	Light::Light()
		: m_LightPosition(0.0, 0.0, 0.0)
		, m_LightColor(1.0, 1.0, 1.0)
		, m_AmbientIntensity(1.0f)
		, m_DiffuseIntensity(1.0f) {}

}