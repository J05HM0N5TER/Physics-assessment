#pragma once
#ifndef _RIGID_BODY_H_
#define _RIGID_BODY_H_

#include "physics_object.h"
#include "glm/glm.hpp"

class rigid_body : public physics_object
{
public:
	glm::vec2 get_position() const { return m_position; }
	glm::vec2 get_velocity() const { return m_velocity; }
	float get_mass() const { return m_mass; }

	~rigid_body() {};

	// For updating all physics
	virtual void fixed_update(glm::vec2 a_gravity, float a_time_step);
	virtual void debug() {};

	// Probably remove this later
	virtual bool check_collision(physics_object* a_other) = 0;

	void apply_force(glm::vec2 force);
	void apply_force_to_object(rigid_body* a_object, glm::vec2 a_force);


	void resolve_collision(rigid_body* a_other, glm::vec2 a_collision_normal);

	void set_velocity(glm::vec2 a_velocity)
	{
		m_velocity = a_velocity;
	}

	void set_position(glm::vec2 a_position)
	{
		m_position = a_position;
	}

protected:
	rigid_body(shape a_shape, glm::vec2 a_position, glm::vec2 a_velocity, float a_mass);

	glm::vec2 m_position;
	glm::vec2 m_velocity;
	// How heavy the object is (how much energy it takes to change momentum)
	float m_mass;
	// The loss of momentum over time
	float m_drag = 0.5f;
};

#endif // !_RIGID_BODY_H_