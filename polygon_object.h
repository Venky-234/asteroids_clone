#pragma once
#include <iostream>
#include <raylib.h>
#include "line_segment.h"
#include <vector>

class polygon_object
{
public:
	std::vector<line_segment> lines;
	Vector2 velocity;
	Vector2 origin;
	int id = 0;

	polygon_object();
	polygon_object(std::vector<Vector2> points, Vector2 velocity, Vector2 origin);
	void render_polygon();
	void apply_velocity();
	void move_object(Vector2 displacement_vector);
	void place_object(Vector2 origin);
	bool is_colliding(polygon_object& object2);
	std::vector<Vector2> get_collision_points(polygon_object& object2);
	void rotate_object(float rotation);
	void render_origin();
	float get_rotation();
	void teleport_object();

private:
	float rotation = 0.0f;
};

