#pragma once
#ifndef  _PHYSICS_SCENE_H_
#define _PHYSICS_SCENE_H_

// Supporting includes
#include "glm/glm.hpp"
#include "collision_manager.h"
#include <vector>

// The template for the function pointer
#include <functional>
using collision_function = std::function< glm::vec2(const physics_object*, const physics_object*) >;

// Forward declarations
class physics_object;

class physics_scene
{
public:
	physics_scene();
	~physics_scene();

	// Adds a new object for the physics_scene to be in charge of
	void add_object(physics_object* a_actor);
	void remove_object(physics_object* a_actor);
	// Calculates all physics
	void update(float a_delta_time);
	// Sets up all m_objects to be able to draw
	void update_gizmos();

	void set_gravity(const glm::vec2 a_gravity) { m_gravity = a_gravity; }

	// Returns the constant force that is being applied to all m_objects
	glm::vec2 get_gravity() const { return m_gravity; }

	void set_time_step(const float a_time_step) { m_time_step = a_time_step; }
	float get_time_step() const { return m_time_step; }

protected:
	// How often the calculations for physics are done
	float m_time_step;
	// The constant force applied to all m_objects
	glm::vec2 m_gravity;
	// The m_objects that this physics_scene in charge of 
	std::vector<physics_object*> m_objects;

	// The time that the physics engine has to catch up on
	float m_accumulated_time = 0.0f;

	// The function pointers to the collision functions
	static const collision_function collision_functions[];
};

#endif // ! _PHYSICS_SCENE_H_

