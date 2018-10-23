#include "world.h"
#include "state.h"

WorldPtr World::create() {
	std::shared_ptr<World> p(new World, [](World* p) {
		delete p;
	});
	return p;
}

World::World() {

}

void World::addEntity(const EntityPtr& entity) {
	m_entities.push_front(entity);
	
	CameraPtr cam = std::dynamic_pointer_cast<Camera>(entity);
	if (cam) m_cameras.push_front(cam);

	LightPtr light = std::dynamic_pointer_cast<Light>(entity);
	if (light) m_lights.push_front(light);
}

void World::removeEntity(const EntityPtr& entity) {
	m_entities.remove(entity);
	
	CameraPtr cam = std::dynamic_pointer_cast<Camera>(entity);
	if (cam) m_cameras.remove(cam);

	LightPtr light = std::dynamic_pointer_cast<Light>(entity);
	if (light) m_lights.remove(light);
}

const EntityPtr World::findEntity(const std::string& name) const {
	for ( const EntityPtr& e : m_entities ) {
		if (e->getName() == name) return e;
	}
	return nullptr;
}

EntityPtr World::findEntity(const std::string& name) {
	for (EntityPtr& e : m_entities) {
		if (e->getName() == name) return e;
	}
	return nullptr;
}

void World::update(float deltaTime) {
	for (EntityPtr& e : m_entities) {
		e->update(deltaTime);
	}
}

void World::draw() {
	State::lights.clear();
	for (LightPtr& light : m_lights) {
		State::lights.push_back(light);
	}
	State::ambient = m_ambient;

	for (CameraPtr& c : m_cameras) {
		c->prepare();
		for (EntityPtr& e : m_entities) {
			e->draw();
		}
	}
}
