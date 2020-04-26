#pragma once

#include "Application.h"
#include "Renderer2D.h"

// Forward declaration
class physics_scene;
class circle;
class aabb;

class physicsApp : public aie::Application 
{
public:

	physicsApp();
	virtual ~physicsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D* m_2dRenderer;
	aie::Font* m_font;

	physics_scene* m_physics_scene;
	circle* m_star;

	float m_timer;
};