#include "physics_scene.h"
#include "physics_object.h"
#include "rigid_body.h"

#include <list>


const collision_function physics_scene::collision_functions[] =
{
	collision_manager::circle_vs_circle, collision_manager::circle_vs_aabb, collision_manager::circle_vs_line,
	collision_manager::aabb_vs_circle,   collision_manager::aabb_vs_aabb,   collision_manager::aabb_vs_line,
	collision_manager::line_vs_circle,   collision_manager::line_vs_aabb,   collision_manager::line_vs_line
};


physics_scene::physics_scene() : m_time_step(0.01f), m_gravity(glm::vec2(0, 0))
{

}
physics_scene::~physics_scene()
{
	for (int i = 0; i < m_objects.size(); ++i)
	{
		delete m_objects[i];
		m_objects[i] = nullptr;
	}
	m_objects.clear();
}

void physics_scene::add_object(physics_object* a_actor)
{
	m_objects.push_back(a_actor);
}

void physics_scene::remove_object(physics_object* a_actor)
{
	auto location = std::find(m_objects.begin(), m_objects.end(), a_actor);
	m_objects.erase(location);
	delete a_actor;
	a_actor = nullptr;
}

void physics_scene::update(float a_delta_time)
{

	m_accumulated_time += a_delta_time;

	// Catch up with the current time by calculating for all the times that were missed
	while (m_accumulated_time >= m_time_step)
	{
		for (auto p_object : m_objects)
		{
			p_object->fixed_update(m_gravity, m_time_step);
		}
		m_accumulated_time -= m_time_step;
	}

	// The objects that have been checked
	static std::list<physics_object*> dirty;

	int object_count = m_objects.size();

	//need to check for collisions against all m_objects except this one.
	for (int outer = 0; outer < object_count - 1; outer++)
	{
		for (int inner = outer + 1; inner < object_count; inner++)
		{
			physics_object* object1 = m_objects[outer];
			physics_object* object2 = m_objects[inner];
			shape shapeId1 = object1->get_shape();
			shape shapeId2 = object2->get_shape();

			// using function pointers
			int functionIdx = (int(shapeId1) * int(shape::shape_count)) + int(shapeId2);
			collision_function collisionFunctionPtr = collision_functions[functionIdx];
			if (collisionFunctionPtr != nullptr)
			{
				// did a collision occur?
				auto result = collisionFunctionPtr(object1, object2);
				if (glm::length(result) > 0.001)
				{
					// Dirty forces stop, remove asap
					rigid_body* r1 = dynamic_cast<rigid_body*>(object1);
					rigid_body* r2 = dynamic_cast<rigid_body*>(object2);

					// Resolve collision
					// Separate
					if (r1 && r2) // both are movable objects
					{
						r1->set_position(r1->get_position() + 0.5f * result);
						r2->set_position(r2->get_position() - 0.5f * result);
						// apply reaction force
						r1->resolve_collision(r2, result);
					}
					else if (r1) // r2 is line
					{
						r1->set_position(r1->get_position() + result);

						line* l = dynamic_cast<line*>(object2);
						// apply reaction force
						l->resolve_collision(r1);

					}
					else if (r2) // r1 is line
					{
						r2->set_position(r2->get_position() + result);
						line* l = dynamic_cast<line*>(object1);
						// apply reaction force
						l->resolve_collision(r2);
					}

				}
			}
		}
	}
}

void physics_scene::update_gizmos()
{
	for (auto p_object : m_objects)
	{
		p_object->make_gizmo();
	}
}

