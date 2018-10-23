#include "state.h"

ShaderPtr             State::defaultShader = nullptr;
glm::mat4             State::projectionMatrix = glm::mat4(1);
glm::mat4             State::viewMatrix = glm::mat4(1);
glm::mat4             State::modelMatrix = glm::mat4(1);
std::vector<LightPtr> State::lights;
glm::vec3             State::ambient;