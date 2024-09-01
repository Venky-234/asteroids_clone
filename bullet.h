#pragma once
#include <raylib.h>
#include "line_segment.h"
#include "polygon_object.h"

class bullet{
public:
	line_segment line_to_follow = line_segment(Vector2{ 0,0 }, Vector2{ 0,0 });
	line_segment collision_line = line_segment(Vector2{ 0,0 }, Vector2{ 0,0 });
	Vector2 position;
	float extrapolation_constant;
	float bullet_speed;
	bool release_bullet;
	float bullet_size = 6;
	
	bullet(Vector2 point_a, Vector2 point_b, float bullet_speed);
	void update_bullet_position();
	void render_bullet();
	bool is_in_polygon(polygon_object obj);
};

