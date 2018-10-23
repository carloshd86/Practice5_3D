#include "model.h"
#include "state.h"

ModelPtr Model::create(const MeshPtr& mesh) {
	if (!mesh) return nullptr;
	std::shared_ptr<Model> p(new Model(mesh), [](Model* p) {
		delete p;
	});
	return p;
}

void Model::draw() {
	glm::mat4 model = glm::translate(glm::mat4(1), getPosition());
	model = glm::rotate(model, glm::angle(getQuaternion()), glm::axis(getQuaternion()));
	model = glm::scale(model, getScale());
	State::modelMatrix = model;
	m_mesh->draw();
}
