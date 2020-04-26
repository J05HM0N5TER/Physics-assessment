#include "physicsApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Gizmos.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "physics_scene.h"
#include "circle.h"
#include "aabb.h"
#include "line.h"

physicsApp::physicsApp() { }

physicsApp::~physicsApp()  { }

bool physicsApp::startup()
{
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_physics_scene = new physics_scene();
	m_physics_scene->set_time_step(0.01f);
	m_physics_scene->set_gravity(glm::vec2(0.0f));

	m_timer = 0;


	// Borders to keep everything on screen
	line* base = new line(glm::vec2(0.0f, 1.0f), -15.0f);
	line* lid = new line(glm::vec2(0.0f, -1.0f), -15.0f);
	line* lhs = new line(glm::vec2(1.0f, 0.0f), -30.0f);
	line* rhs = new line(glm::vec2(-1.0f, 0.0f), -30.0f);
	line* lhd = new line(glm::vec2(1.0f), -25.0f);
	line* rhd = new line(glm::vec2(-1.0f, 1.0f), -25.0f);
	line* lhdu = new line(glm::vec2(-1.0f), -25.0f);
	line* rhdu = new line(glm::vec2(1.0f, -1.0f), -25.0f);
	m_physics_scene->add_object(base);
	m_physics_scene->add_object(lid);
	m_physics_scene->add_object(lhs);
	m_physics_scene->add_object(rhs);
	m_physics_scene->add_object(lhd);
	m_physics_scene->add_object(rhd);
	m_physics_scene->add_object(lhdu);
	m_physics_scene->add_object(rhdu);

	// Add a whole lot of circles
	for (int x = 0; x < 10; ++x)
	{
		for (int y = 0; y < 10; ++y)
		{
			m_physics_scene->add_object(new circle(glm::vec2(-8 + x, 3 - y)));
		}
	}

	return true;
}

void physicsApp::shutdown() 
{
	aie::Gizmos::destroy();

	delete m_physics_scene;

	delete m_font;
	delete m_2dRenderer;

}

void physicsApp::update(float deltaTime)
{

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();

	// Update the camera m_position using the arrow keys
	float camPosX;
	float camPosY;
	m_2dRenderer->getCameraPos(camPosX, camPosY);

	if (input->isKeyDown(aie::INPUT_KEY_UP))
		camPosY += 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		camPosY -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		camPosX -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		camPosX += 500.0f * deltaTime;

	m_2dRenderer->setCameraPos(camPosX, camPosY);

	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
	{
		m_physics_scene->set_gravity(glm::vec2(0.0f, -10.0f));
	}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();


	aie::Gizmos::clear();

	m_physics_scene->update(deltaTime);
	m_physics_scene->update_gizmos();
}

void physicsApp::draw() 
{
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	// Draw all batched Gizmos
	aie::Gizmos::draw2D(glm::ortho<float>(-32, 32, -18, 18, -1, 1));

	// done drawing sprites
	m_2dRenderer->end();
}
