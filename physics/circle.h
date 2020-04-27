#pragma once
#include "rigid_body.h"

class circle : public rigid_body
{
public:
	/*	\brief Constructor for circle
		\param a_position The centre m_position of the circle
		\param a_velocity The current direction and force the circle is travelling
		\param a_mass How much "m_mass" the object has (how hard it is to change momentum)
		\param a_radius The size of the circle
		\param a_colour The colour that the circle will be displayed using
	*/
	circle(glm::vec2 a_position,
		glm::vec2 a_velocity = glm::vec2(0.0f),
		float a_mass = 1.0f,
		float a_radius = 1.0f,
		glm::vec4 a_colour = glm::vec4(0.1f, 0.1f, 0.8f, 1.0f));

	~circle();

	// Create the gizmo (draw on screen)
	virtual void make_gizmo();
	// Checks the collision of this object with another
	virtual bool check_collision(physics_object* pOther);

	// Get the current size of the circle
	const float get_radius() const;
	// Set the size of the circle
	void set_radius(const float a_radius);

	// TODO: set up debug
	virtual void debug() override
	{

	}

protected:
	// The size of the circle
	float m_radius;
};


