#pragma once

#include "common.h"
#include "shader.h"
#include "light.h"

class State {
public:
	static ShaderPtr	         defaultShader;
	static glm::mat4 	         projectionMatrix;
	static glm::mat4 	         viewMatrix;
	static glm::mat4 	         modelMatrix;
	static std::vector<LightPtr> lights;
	static glm::vec3             ambient;
protected:
	State()  {}
	~State() {}
};

