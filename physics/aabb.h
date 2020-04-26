#pragma once
#include "rigid_body.h"

class aabb : public rigid_body
{
public:
	/*	\brief Constructor for aabb
		\param a_position The centre m_position of the aabb
		\param a_extents The size of the aabb
		\param a_velocity The current direction and force the aabb is travelling
		\param a_mass How much "m_mass" the object has (how hard it is to change momentum)
	*/
	aabb(const glm::vec2& a_position,
		const glm::vec2& a_extents = glm::vec2(1.0f),
		const glm::vec2& a_velocity = glm::vec2(0.0f),
		const float a_mass = 1.0f);

	// Getter and setter for m_position
	const glm::vec2 get_position() const;
	void set_position(const glm::vec2& a_position);

	// Getter and setter for m_extents (size)
	const glm::vec2 get_extents() const;
	void set_extents(const glm::vec2& a_extents);

	// Getters for m_width and m_height (size)
	const float get_width() const;
	const float get_height() const;

	// Get the smallest value for x and y
	const glm::vec2 get_min() const;
	// Get the biggest value for x and y
	const glm::vec2 get_max() const;

	// Implementation of the base class virtual members
	void debug() override {}
	// Unused virtual function
	bool check_collision(physics_object* a_other) override { return false; }
	void make_gizmo() override
	{
		aie::Gizmos::add2DAABBFilled(m_position, m_extents * 0.5f, color);
	}

private:
	union
	{
		glm::vec2 m_extents;
		struct
		{
			float m_width;
			float m_height;
		};
	};
};

