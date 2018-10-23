#pragma once

#include "common.h"

class Texture;
class Shader;

class Material {

public:
	Material(const std::shared_ptr<Texture>& tex = nullptr, const std::shared_ptr<Shader>& shader = nullptr, const glm::vec4& color = { 1.f, 1.f, 1.f, 1.f }, uint8_t shininess = 255);

	const std::shared_ptr<Shader>&  getShader() const;
	std::shared_ptr<Shader>&        getShader();
	void                            setShader(const std::shared_ptr<Shader>& shader);
	const std::shared_ptr<Texture>& getTexture() const;
	void                            setTexture(const std::shared_ptr<Texture>& tex);
	const glm::vec4&                getColor() const;
	void                            setColor(const glm::vec4& color);
	uint8_t                         getShininess() const;
	void                            setShininess(uint8_t shininess);
	void                            prepare();

private:
	std::shared_ptr<Texture> m_texture;
	std::shared_ptr<Shader>  m_shader;
	glm::vec4                m_color;
	uint8_t                  m_shininess;
};
