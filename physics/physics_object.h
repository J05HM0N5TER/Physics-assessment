#include "glm/glm.hpp"
#include "Gizmos.h"

#pragma once
#ifndef  _PHYSICS_OBJECT_H_
#define  _PHYSICS_OBJECT_H_

enum class shape : char
{
	circle = 0,
	aabb,
	line,
	shape_count
};

class physics_object
{
protected:
	// What shape it is (used for collision)
	shape m_shape_type;

	/*	brief Constructor for the physics_object
		\param a_shape the shape of the object used for collision
	*/
	physics_object(shape a_shape)
	{
		m_shape_type = a_shape;
	}
	// Constructor requires a shape to do collision
	physics_object() = delete;

public:
	virtual void fixed_update(glm::vec2 a_gravity, float a_time_step) = 0;
	virtual void debug() = 0;
	virtual void make_gizmo() = 0;
	virtual void resetPosition() {};

	// Sets the colour that the shape will be displayed as
	void set_color(glm::vec4 a_color)
	{
		color = a_color;
	}

	// The colour the shape will be displayed as
	glm::vec4 color = glm::vec4(1.0f);

	// Returns the shape that the physics object is set to
	shape get_shape() const
	{
		return m_shape_type;
	}

	// The force applied to both m_objects when a collision applies
	float m_elasticity = 0.5f;
};

#endif // !
