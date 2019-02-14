#include "light.h"
#include "shader.h"
#include "state.h"

const float Light::CONSTANT_ATTENUATION  = 1.f;
const float Light::QUADRATIC_ATTENUATION = 0.f;

LightPtr Light::create(Type type, const glm::vec3& color, float linearAttenuation) {
	std::shared_ptr<Light> p(new Light(type, color, linearAttenuation), [](Light* p) {
		delete p;
	});

	return p;
}

void Light::prepare(int index, std::shared_ptr<Shader>& shader) const {
	glm::mat4 modelviewMatrix = State::viewMatrix * State::modelMatrix;
	glm::vec4 mvPosition = modelviewMatrix * glm::vec4(getPosition(), 1);

	if (DIRECTIONAL == m_type) {
		mvPosition.w = 0;
	}
	else {
		mvPosition.w = 1;
	}

	std::string indexString;
	indexString.append("[").append(std::to_string(index)).append("]");

	shader->setVec4  (shader->getLocation("lightPosition" + indexString)             , mvPosition);
	shader->setInt   (shader->getLocation("lightType" + indexString)                 , static_cast<const int>(m_type));
	shader->setVec3  (shader->getLocation("lightColor" + indexString)                , m_color);
	shader->setFloat (shader->getLocation("lightLinearAttenuation" + indexString)    , m_linearAttenuation);
	shader->setFloat (shader->getLocation("lightConstantAttenuation" + indexString)  , Light::CONSTANT_ATTENUATION);
	shader->setFloat (shader->getLocation("lightQuadraticAttenuation" + indexString) , Light::QUADRATIC_ATTENUATION);
}