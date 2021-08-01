#include "Vec3ScriptRegister.h"

#include "glm.hpp"

namespace pawn {

	namespace engine {

		void Vec3ScriptRegister::Register(sol::state& lua) {
			lua.new_usertype<glm::vec3>("vec3",
				sol::constructors<glm::vec3(), glm::vec3(float), glm::vec3(float, float, float)>(),
				"x", &glm::vec3::x,
				"y", &glm::vec3::y,
				"z", &glm::vec3::z,
				"__add", [](const glm::vec3& l, const glm::vec3& r) { return l + r; },
				"__sub", [](const glm::vec3& l, const glm::vec3& r) { return l - r; },
				"__mul", [](const glm::vec3& l, const glm::vec3& r) { return l * r; }
			);

			lua.set_function("vec3MulScalar", [](const glm::vec3& l, float r) {
				return l * r;
			});
		}

	}

}