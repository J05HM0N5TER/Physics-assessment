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
	// Sets up all objects to be able to draw
	void update_gizmos();

	void set_gravity(const glm::vec2 a_gravity) { gravity = a_gravity; }

	// Returns the constant force that is being applied to all objects
	glm::vec2 get_gravity() const { return gravity; }

	void set_time_step(const float a_time_step) { time_step = a_time_step; }
	float get_time_step() const { return time_step; }

protected:
	// How often the calculations for physics are done
	float time_step;
	// The constant force applied to all objects
	glm::vec2 gravity;
	// The objects that this physics_scene in charge of 
	std::vector<physics_object*> objects;

	// The time that the physics engine has to catch up on
	float accumulated_time = 0.0f;

	// The function pointers to the collision functions
	static const collision_function collision_functions[];
};

#endif // ! _PHYSICS_SCENE_H_

