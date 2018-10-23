#pragma once

#include "camera.h"
#include "common.h"
#include "entity.h"
#include "light.h"

class World;
typedef std::shared_ptr<World> WorldPtr;

class World {
public:
	static WorldPtr create();

	void addEntity(const EntityPtr& entity);
	void removeEntity(const EntityPtr& entity);

	const EntityPtr findEntity(const std::string& name) const;
	EntityPtr findEntity(const std::string& name);

	const glm::vec3& getAmbient() const                   { return m_ambient; }
	void             setAmbient(const glm::vec3& ambient) { m_ambient = ambient; }
	
	void update(float deltaTime);
	void draw();
protected:
	World();
	~World() {}
private:
	std::forward_list<EntityPtr>	m_entities;
	std::forward_list<CameraPtr>	m_cameras;
	std::forward_list<LightPtr>	    m_lights;
	glm::vec3                       m_ambient;
};