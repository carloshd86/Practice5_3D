#pragma once

#include "common.h"

class Entity;
typedef std::shared_ptr<Entity> EntityPtr;

class Entity {
public:
	static EntityPtr create();

	const std::string&	getName() const { return m_name; }
	void				setName(const std::string& name) { m_name = name; }

	const glm::vec3&	getPosition() const { return m_position; }
	void				setPosition(const glm::vec3& pos) { m_position = pos; }
	
	const				glm::vec3& getEuler() const { return m_euler; }
	const void			setEuler(const glm::vec3& rot) { m_euler = rot; m_quat = glm::quat(glm::radians(rot)); }
	
	const glm::quat&	getQuaternion() const { return m_quat; }
	const void			setQuaternion(const glm::quat& q) { m_quat = q; m_euler = glm::degrees(glm::eulerAngles(q)); }
	
	const glm::vec3&	getScale() const { return m_scale; }
	void				setScale(const glm::vec3& scale) { m_scale = scale; }

	void				move(const glm::vec3& vec) { m_position += m_quat * vec; }

	virtual void		update(float deltaTime) {}
	virtual void		draw() {}
protected:
	Entity() : m_scale(1, 1, 1) {}
	virtual ~Entity() {}
private:
	std::string	m_name;
	glm::vec3	m_position;
	glm::vec3	m_euler;
	glm::quat	m_quat;
	glm::vec3	m_scale;
};

inline EntityPtr Entity::create() {
	std::shared_ptr<Entity> p(new Entity, [](Entity* p) {
		delete p;
	});
	return p;
}