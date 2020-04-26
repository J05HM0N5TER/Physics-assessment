#include "rigid_body.h"
//rigid_body(shape a_shape, const glm::vec2& a_position)
//	: m_position(a_position), physics_object(a_shape) {}

rigid_body::rigid_body(
	shape a_shape,
	glm::vec2 a_position,
	glm::vec2 a_velocity,
	float a_mass) :
	physics_object(a_shape),
	m_position(a_position),
	m_velocity(a_velocity),
	m_mass(a_mass)
{}

void rigid_body::fixed_update(glm::vec2 a_gravity, float a_time_step)
{
	apply_force(a_gravity * m_mass * a_time_step);
	m_velocity -= m_velocity * m_drag * a_time_step;
	m_position += m_velocity * a_time_step;
}


void rigid_body::apply_force(glm::vec2 force)
{
	m_velocity += force / m_mass; // a = F / m
}

void rigid_body::apply_force_to_object(rigid_body* a_object, glm::vec2 force)
{
	a_object->apply_force(force);
	this->apply_force(-force);
}

void rigid_body::resolve_collision(rigid_body* a_other, glm::vec2 a_collision_normal)
{
	glm::vec2 normal = glm::normalize(a_collision_normal);

	glm::vec2 relativeVelocity = a_other->get_velocity() - m_velocity;


	float j =
		glm::dot(-(1 + (m_elasticity * a_other->m_elasticity)) * (relativeVelocity), normal)
		/
		glm::dot(normal, normal * ((1 / m_mass) + (1 / a_other->get_mass())));

	glm::vec2 force = normal * j;

	apply_force_to_object(a_other, force);
}

