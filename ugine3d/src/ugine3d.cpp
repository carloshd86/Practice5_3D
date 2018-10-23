#include "common.h"
#include "state.h"
#include "util.h"

bool init() {
	bool initOk = false;
	if (glewInit() == GLEW_OK) {
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_SCISSOR_TEST);
		State::defaultShader = Shader::create(readString("data/vertex.glsl"), readString("data/fragment.glsl"));
		initOk = (State::defaultShader != nullptr);
	}
	return initOk;
}
