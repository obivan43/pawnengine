#include "Environment.h"

namespace pawn::engine {

	Environment::Environment() 
		: m_AmbientLightColor(1.0, 1.0, 1.0)
		, m_AmbientLightIntensity(1.0f)
		, m_DirectionalLightPosition(0.0, 0.0, 0.0)
		, m_DirectionalLightColor(1.0, 1.0, 1.0)
		, m_DirectionalLightIntensity(1.0f) {}

}
