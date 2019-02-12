#include "material.h"
#include "texture.h"
#include "shader.h"
#include "state.h"


Material::Material(const std::shared_ptr<Texture>& tex, const std::shared_ptr<Shader>& shader, const glm::vec4& color, uint8_t shininess) :
	m_texture   (tex),
	m_shader    (shader),
	m_color     (color),
	m_shininess (shininess) {
}

/******************/

const std::shared_ptr<Shader>& Material::getShader() const {
	if (!m_shader) return const_cast<const std::shared_ptr<Shader>&>(State::defaultShader);
	else          return const_cast<const std::shared_ptr<Shader>&>(m_shader);
}

/******************/

std::shared_ptr<Shader>& Material::getShader() {
	if (!m_shader) return State::defaultShader;
	else          return m_shader;
}

/******************/

void Material::setShader(const std::shared_ptr<Shader>& shader) {
	m_shader = shader;
}

/******************/

const std::shared_ptr<Texture>& Material::getTexture() const {
	return const_cast<const std::shared_ptr<Texture>&>(m_texture);
}

/******************/

void Material::setTexture(const std::shared_ptr<Texture>& tex) {
	m_texture = tex;
}

/******************/

const glm::vec4& Material::getColor() const {
	return m_color;
}

/******************/

void Material::setColor(const glm::vec4& color) {
	m_color = color;
}

/******************/

uint8_t Material::getShininess() const {
	return m_shininess;
}

/******************/

void Material::setShininess(uint8_t shininess) {
	m_shininess = shininess;
}

/******************/

void Material::prepare() {
	ShaderPtr shaderUsed = getShader();
	shaderUsed->use();
	glm::mat4 mvpMatrix = State::projectionMatrix * State::viewMatrix * State::modelMatrix;
	State::defaultShader->setMatrix(shaderUsed->getLocation("mvp"), mvpMatrix);
	int isTexture = m_texture ? 1 : 0;
	State::defaultShader->setInt(shaderUsed->getLocation("isTexture"), isTexture);
	State::defaultShader->setInt(shaderUsed->getLocation("texSampler"), 0);
	if (isTexture) m_texture->bind();

	int numLights = static_cast<int>(State::lights.size());
	State::defaultShader->setInt(shaderUsed->getLocation("numLights"), numLights);
	State::defaultShader->setVec4(shaderUsed->getLocation("diffuseColor"), m_color);
	State::defaultShader->setInt(shaderUsed->getLocation("shininess"), m_shininess);
	State::defaultShader->setVec3(shaderUsed->getLocation("ambientLight"), State::ambient);
	for (int i = 0; i < numLights; ++i) {
		State::lights[i]->prepare(i, State::defaultShader);
	}
}