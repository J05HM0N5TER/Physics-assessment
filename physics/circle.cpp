#include "circle.h"
#include <cmath>

#include "collision_manager.h"

circle::circle(glm::vec2 a_position, glm::vec2 a_velocity, float a_mass, float a_radius, glm::vec4 a_colour) :
	rigid_body(shape::circle, a_position, a_velocity, a_mass), m_radius(a_radius)
{
	m_color = a_colour;
}

circle::~circle() {}

const float circle::get_radius() const
{
	return m_radius;
}
void circle::set_radius(const float a_radius)
{
	m_radius = abs(a_radius);
}

void circle::make_gizmo()
{
	aie::Gizmos::add2DCircle(m_position, m_radius, 32, m_color);
}

bool circle::check_collision(physics_object* a_other)
{
	return false;
	//return collision_manager::circle_vs_circle(*this, (circle&)*a_other);
}

