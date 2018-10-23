#pragma once

#include "common.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 textCoords;
	glm::vec3 normals;

	Vertex(const glm::vec3& pos, const glm::vec3& color, const glm::vec2& textCoords, const glm::vec3& normals) : position(pos), color(color), textCoords(textCoords), normals(normals) {}
};
