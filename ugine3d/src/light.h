#pragma once

#include "entity.h"

class Light;
class Shader;
typedef std::shared_ptr<Light> LightPtr;

class Light : public Entity {
public:

	enum Type {
		DIRECTIONAL = 0,
		POINT = 1
	};

	static LightPtr create(Type type, const glm::vec3& color, float linearAttenuation = 1.0f);

	Type getType() const    { return m_type; }
	void setType(Type type) { m_type = type; }

	const glm::vec3& getColor() const                 { return m_color; }
	void             setColor(const glm::vec3& color) { m_color = color; }

	float getLinearAttenuation() const   { return m_linearAttenuation; }
	void setLinearAttenuation(float att) { m_linearAttenuation = att; }

	void prepare(int index, std::shared_ptr<Shader>& shader) const;

protected:
	Light(Type type, const glm::vec3& color, float linearAttenuation = 1.0f) : Entity(), m_type(type), m_color(color), m_linearAttenuation(linearAttenuation) {}
	virtual ~Light() {}
private:
	static const float CONSTANT_ATTENUATION;
	static const float QUADRATIC_ATTENUATION;

	Type m_type;
	glm::vec3 m_color;
	float m_linearAttenuation;
};