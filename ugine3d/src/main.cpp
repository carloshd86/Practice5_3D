#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "ugine3d.h"
#include "state.h"
#include "../lib/glfw/glfw3.h"
#include <iostream>
#include <vector>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main() {
	// init glfw
	if ( !glfwInit() ) {
		std::cout << "could not initialize glfw" << std::endl;
		return -1;
	}

	// create window
	//glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_SAMPLES, 8);
	GLFWwindow* win = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "", nullptr, nullptr);
	if (!win) {
		std::cout << "could not create opengl window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(win);

	// set input mode
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// init ugine3d
	if (!init()) {
		std::cout << "could not initialize engine" << std::endl;
		return -1;
	}

	// create world
	WorldPtr world = World::create();

	// load mesh
	MeshPtr mesh =  Mesh::load("data/asian_town.msh.xml");

	// create camera
	CameraPtr camera = Camera::create(glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT));
	camera->setClearColor(glm::vec3(0, 0, 0));
	camera->setPosition  (glm::vec3(0, 0.02f, 0));
	camera->setEuler     (glm::vec3(0, 0, 0));
	world->addEntity(camera);

	// create models
	ModelPtr model = Model::create(mesh);
	model->setEuler(glm::vec3(0, 0, 0));
	world->addEntity(model);

	// main loop
	float angle = 0;
	float translationSpeed = 0.05f;
	float rotationSpeed = 30.f;
	double mouseX = 0, mouseY = 0, lastMX = 0, lastMY = 0;
	int speedMX = 0, speedMY = 0;
	glm::vec2 vMouse;

	double lastTime = glfwGetTime();
	const float MAX_ROT_X = 30;
	const float MAX_ROT_Y = 15;
	while ( !glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE) ) {
		// get delta time
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// get window size
		int screenWidth, screenHeight;
		glfwGetWindowSize(win, &screenWidth, &screenHeight);

		// update mouse
		glfwGetCursorPos(win, &mouseX, &mouseY);
		speedMX = static_cast<int>(mouseX - lastMX);
		speedMY = static_cast<int>(mouseY - lastMY);
		lastMX = mouseX;
		lastMY = mouseY;

		// update camera
		float aspectRatio = 0;
		if (screenHeight)  aspectRatio = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);
		camera->setProjection(glm::perspective(glm::radians(60.0f), aspectRatio, 0.01f, 100.0f));
		camera->setViewport(glm::ivec4(0, 0, screenWidth, screenHeight));
		
		glm::vec3 cameraEuler = camera->getEuler();
		cameraEuler.x -= speedMY * rotationSpeed * deltaTime;
		cameraEuler.y -= speedMX * rotationSpeed * deltaTime;
		cameraEuler.x = std::max(cameraEuler.x, -60.f);
		cameraEuler.x = std::min(cameraEuler.x, 60.f);
		if (cameraEuler.y > 360) cameraEuler.y -= 360;
		if (cameraEuler.y < 0) cameraEuler.y += 360;
		camera->setEuler(cameraEuler);

		/*glm::quat cameraQuaternion = camera->getQuaternion();
		cameraQuaternion.x -= glm::radians(speedMY * rotationSpeed * deltaTime);
		cameraQuaternion.y -= glm::radians(speedMX * rotationSpeed * deltaTime);
		cameraQuaternion.x = std::max(cameraQuaternion.x, glm::radians(-60.f));
		cameraQuaternion.x = std::min(cameraQuaternion.x, glm::radians(60.f));
		camera->setQuaternion(cameraQuaternion);*/

		glm::vec3 movement;
		if (glfwGetKey(win, GLFW_KEY_W))    movement.z = -translationSpeed * deltaTime;
		if (glfwGetKey(win, GLFW_KEY_A))    movement.x = -translationSpeed * deltaTime;		
		if (glfwGetKey(win, GLFW_KEY_S))    movement.z =  translationSpeed * deltaTime;
		if (glfwGetKey(win, GLFW_KEY_D))    movement.x =  translationSpeed * deltaTime;	
		if (glfwGetKey(win, GLFW_KEY_UP))   movement.y =  translationSpeed * deltaTime;
		if (glfwGetKey(win, GLFW_KEY_DOWN)) movement.y = -translationSpeed * deltaTime;	
		camera->move(movement);
		

		// update world
		world->update(deltaTime);

		// draw world
		world->draw();

		// refresh screen
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	// shutdown
	glfwTerminate();
}