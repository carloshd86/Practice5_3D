#include "camera.h"
#include "state.h"

CameraPtr Camera::create(const glm::ivec2& viewportSize) {
	std::shared_ptr<Camera> p(new Camera(viewportSize), [](Camera* p) {
		delete p;
	});
	return p;
}

Camera::Camera(const glm::ivec2& viewportSize) {
	setProjection(glm::perspective<float>(
		glm::radians(60.0f),
		static_cast<float>(viewportSize.x) / viewportSize.y,
		1, 1000));
	setViewport(glm::ivec4(0, 0, viewportSize.x, viewportSize.y));
	setClearColor(glm::vec3(0, 0, 0.5f));
}

void Camera::prepare() {
	State::projectionMatrix = m_projection;

	glm::mat4 view = glm::mat4(1);
	view = glm::rotate(view, -glm::angle(getQuaternion()), glm::axis(getQuaternion()));
	view = glm::translate(view, -getPosition());
	State::viewMatrix = view;

	glViewport(m_viewport.x, m_viewport.y, m_viewport.z, m_viewport.w);
	glScissor(m_viewport.x, m_viewport.y, m_viewport.z, m_viewport.w);

	glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
