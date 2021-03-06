#pragma once
#include "circle.h"
#include "line.h"
#include "aabb.h"

class collision_manager
{
public:
	static glm::vec2 circle_vs_circle(const physics_object* a_circle_A,
		const physics_object* a_circle_B);

	static glm::vec2 aabb_vs_aabb(const physics_object* a_aabb_A,
		const physics_object* a_aabb_B);

	static glm::vec2 line_vs_line(const physics_object* a_line_A,
		const physics_object* a_line_B);

	static glm::vec2 aabb_vs_circle(const physics_object* a_aabb,
		const physics_object* a_circle);

	static glm::vec2 circle_vs_aabb(const physics_object* a_circle,
		const physics_object* a_aabb);

	static glm::vec2 circle_vs_line(const physics_object* a_circle,
		const physics_object* a_line);

	static glm::vec2 line_vs_circle(const physics_object* a_line,
		const physics_object* a_circle);

	static glm::vec2 aabb_vs_line(const physics_object* a_aabb,
		const physics_object* a_line);

	static glm::vec2 line_vs_aabb(const physics_object* a_line,
		const physics_object* a_aabb);
};

