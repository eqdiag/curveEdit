#ifndef UTIL_H
#define UTIL_H

#include <glm/glm.hpp>
#include <cstdlib>

namespace core {

	inline void deterministicSeed() {
		std::srand(0);
	}

	inline float randFloat() {
		return static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
	}

	inline glm::vec3 randVec3() {
		return glm::vec3(randFloat() * 2.0 - 1.0, randFloat() * 2.0 - 1.0, randFloat() * 2.0 - 1.0);
	}

	inline glm::vec3 getOrthoVector(const glm::vec3& v) {
		glm::vec3 w;
		do {
			w = randVec3();
		} while (glm::length(glm::normalize(w) - glm::normalize(v)) < 0.001);

		return glm::normalize(glm::cross(w, v));
	}

}


#endif