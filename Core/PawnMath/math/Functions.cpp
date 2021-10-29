#include "pch.h"
#include "Functions.h"

namespace pawn::math {

	glm::mat4 cameraMatrix(const glm::vec3& cameraPosition, float pitch, float yaw) {
		glm::mat4 rotationMatrix = glm::mat4(1.0);

		float finalPitchDegree = glm::radians(pitch);
		float finalYawDegree = glm::radians(yaw);

		rotationMatrix = glm::rotate(rotationMatrix, finalPitchDegree, glm::vec3(1.0, 0.0, 0.0));
		rotationMatrix = glm::rotate(rotationMatrix, finalYawDegree, glm::vec3(0.0, 1.0, 0.0));

		glm::vec3 lookVector = glm::vec4(0.0, 0.0, 1.0, 0.0) * rotationMatrix;
		glm::vec3 cameraTarget = cameraPosition + lookVector;

		return glm::lookAtLH(cameraPosition, cameraTarget, glm::vec3(0.0, 1.0, 0.0));
	}

	glm::mat4 inverseTranspose(const glm::mat4& matrix) {
		glm::mat4 result = glm::mat4(1.0);

		result = glm::transpose(glm::inverse(matrix));

		return result;
	}

}
