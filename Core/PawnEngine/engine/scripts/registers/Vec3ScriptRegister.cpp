#include "Vec3ScriptRegister.h"

#include "glm.hpp"

namespace pawn::engine {

	void Vec3ScriptRegister::Register(sol::state& lua) const {
		lua.new_usertype<glm::vec3>("vec3",
			sol::constructors<glm::vec3(), glm::vec3(float), glm::vec3(float, float, float)>(),
			"x", &glm::vec3::x,
			"y", &glm::vec3::y,
			"z", &glm::vec3::z,
			"__add", [](const glm::vec3& left, const glm::vec3& right) { return left + right; },
			"__sub", [](const glm::vec3& left, const glm::vec3& right) { return left - right; },
			"__mul", [](const glm::vec3& left, const glm::vec3& right) { return left * right; }
		);

		lua.set_function("vec3MulScalar", [](const glm::vec3& vector, float scalar) {
			return vector * scalar;
		});
	}

}
