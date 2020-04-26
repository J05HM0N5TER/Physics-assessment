#include "aabb.h"
#include <cmath>

aabb::aabb(
	const glm::vec2& a_position,
	const glm::vec2& a_extents, /* = glm::vec2(1.0f) */
	const glm::vec2& a_velocity, /* = glm::vec2(0.0f) */
	const float a_mass /* = 1.0f*/)
	:
	rigid_body(shape::aabb, a_position, a_velocity, a_mass),
	m_extents(a_extents)
{}

const glm::vec2 aabb::get_position() const
{
	return m_position;
}

void aabb::set_position(const glm::vec2& a_position)
{
	m_position = a_position;
}

const glm::vec2 aabb::get_extents() const
{
	return m_extents;
}

void aabb::set_extents(const glm::vec2& a_extents)
{
	m_extents = { abs(a_extents.x), abs(a_extents.y) };
}

const float aabb::get_width() const
{
	return m_width;
}

const float aabb::get_height() const
{
	return m_height;
}

const glm::vec2 aabb::get_min() const
{
	return m_position - 0.5f * m_extents;
}

const glm::vec2 aabb::get_max() const
{
	return m_position + 0.5f * m_extents;
}