#pragma once

#include "entity.h"

class Camera;
typedef std::shared_ptr<Camera> CameraPtr;

class Camera : public Entity {
public:
	static CameraPtr create(const glm::ivec2& viewportSize);

	const glm::mat4& getProjection() const { return m_projection; }
	void setProjection(const glm::mat4& proj) { m_projection = proj; }

	const glm::ivec4& getViewport() const { return m_viewport; }
	void setViewport(const glm::ivec4& vp) { m_viewport = vp; }

	const glm::vec3& getClearColor() const { return m_clearColor; }
	void setClearColor(const glm::vec3& color) { m_clearColor = color; }

	void prepare();
protected:
	Camera(const glm::ivec2& viewportSize);
private:
	glm::mat4	m_projection;
	glm::ivec4	m_viewport;
	glm::vec3	m_clearColor;
};