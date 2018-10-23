#include "light.h"
#include "shader.h"

const float Light::CONSTANT_ATTENUATION  = 1.f;
const float Light::QUADRATIC_ATTENUATION = 0.f;

inline LightPtr Light::create(Type type, const glm::vec3& color, float linearAttenuation) {
	std::shared_ptr<Light> p(new Light(type, color, linearAttenuation), [](Light* p) {
		delete p;
	});
	return p;
}

void Light::prepare(int index, std::shared_ptr<Shader>& shader) const {
	// TODO pasar en el espacio del observador los datos de la luz
	shader->setVec3(index, m_color);
}