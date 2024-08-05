#include "polygon_object.h"
#include <math.h>
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

polygon_object::polygon_object() {

}
polygon_object::polygon_object(std::vector<Vector2> points, Vector2 velocity, Vector2 origin) {
	for (int i = 0; i < points.size(); i++) {

		if(i != points.size() - 1)
			lines.push_back(line_segment(points[i], points[i+1]));

		else
			lines.push_back(line_segment(points[i], points[0]));
	}
	polygon_object::velocity = velocity;
	polygon_object::origin = origin;
}

void polygon_object::render_polygon() {
	for (int i = 0; i < lines.size(); i++) {
		lines[i].render_line();
	}
}

void polygon_object::apply_velocity() {
	for (int i = 0; i < lines.size(); i++) {
		lines[i].point_A.x += velocity.x;
		lines[i].point_B.x += velocity.x;

		lines[i].point_A.y += velocity.y;
		lines[i].point_B.y += velocity.y;
	}
	origin.x += velocity.x;
	origin.y += velocity.y;
}
void polygon_object::move_object(Vector2 displacement_vector) {
	for (int i = 0; i < lines.size(); i++) {
		lines[i].point_A.x += displacement_vector.x;
		lines[i].point_B.x += displacement_vector.x;

		lines[i].point_A.y += displacement_vector.y;
		lines[i].point_B.y += displacement_vector.y;
	}
	origin.x += displacement_vector.x;
	origin.y += displacement_vector.y;
}
void polygon_object::place_object(Vector2 origin) {
	Vector2 displacement{
		origin.x - polygon_object::origin.x,
		origin.y - polygon_object::origin.y
	};
	move_object(displacement);
	polygon_object::origin = origin;
}
bool polygon_object::is_colliding(polygon_object& object2) {
	for (int i = 0; i < lines.size(); i++) {

		for (int j = 0; j < object2.lines.size(); j++) {

			lines[i].calculate_intersection_point(object2.lines[j]);

			if (lines[i].is_intersecting) {
				return true;
			}

		}

	}
	return false;
}

std::vector<Vector2> polygon_object::get_collision_points(polygon_object& object2) {
	std::vector<Vector2> collision_points;

	for (int i = 0; i < lines.size(); i++) {

		for (int j = 0; j < object2.lines.size(); j++) {

			lines[i].calculate_intersection_point(object2.lines[j]);

			if (lines[i].is_intersecting) {
				collision_points.push_back(lines[i].intersection_point);
			}

		}

	}
	return collision_points;
}

Vector2 rotate_point(Vector2 P, Vector2 Q, float rotation) {
	return Vector2{
		Q.x + (P.x - Q.x) * (float)cos(rotation) - (P.y - Q.y) * (float)sin(rotation),
		Q.y + (P.x - Q.x) * (float)sin(rotation) + (P.y - Q.y) * (float)cos(rotation)
	};
}
void polygon_object::rotate_object(float rotation) {
	for (int i = 0; i < lines.size(); i++) {
		lines[i].point_A = rotate_point(lines[i].point_A, origin ,rotation);
		lines[i].point_B = rotate_point(lines[i].point_B, origin ,rotation);
	}
}

void polygon_object::render_origin() {
	DrawCircleV(origin, 3, WHITE);
}

float polygon_object::get_rotation() {
	return rotation;
}

void polygon_object::teleport_object() {
	bool teleport_to_left = false;
	bool teleport_to_right = false;
	bool teleport_to_up = false;
	bool teleport_to_down = false;


	for (int i = 0; i < lines.size(); i++) {
		if (lines[i].point_A.x > SCREEN_WIDTH &&
			lines[i].point_B.x > SCREEN_WIDTH &&
			velocity.x > 0
		) 
		{
			teleport_to_left = true;
		}
		else {
			teleport_to_left = false;
			break;
		}
	}

	for (int i = 0; i < lines.size(); i++) {
		if (lines[i].point_A.x < 0 &&
			lines[i].point_B.x < 0 &&
			velocity.x < 0
			)
		{
			teleport_to_right = true;
		}
		else {
			teleport_to_right = false;
			break;
		}
	}
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i].point_A.y > SCREEN_HEIGHT &&
			lines[i].point_B.y > SCREEN_HEIGHT &&
			velocity.y > 0
			)
		{
			teleport_to_up = true;
		}
		else {
			teleport_to_up = false;
			break;
		}

	}
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i].point_A.y < 0 &&
			lines[i].point_B.y < 0 &&
			velocity.y < 0
			)
		{
			teleport_to_down = true;
		}
		else {
			teleport_to_down = false;
			break;
		}

	}

	if (teleport_to_left) {
		float max = 0;
		for (int i = 0; i < lines.size(); i++) {
			if (lines[i].point_A.x > max) {
				max = lines[i].point_A.x;
			}
		}
		move_object(Vector2{ -max,0 });
		teleport_to_left = false;
	}

	if (teleport_to_right) {
		float min = lines[0].point_A.x;
		for (int i = 1; i < lines.size(); i++) {
			if (lines[i].point_A.x < min) {
				min = lines[i].point_A.x;
			}
		}
		move_object(Vector2{ SCREEN_WIDTH + abs(min), 0 });
		teleport_to_right = false;
	}
	if (teleport_to_up) {
		float max = 0;
		for (int i = 0; i < lines.size(); i++) {
			if (lines[i].point_A.y > max) {
				max = lines[i].point_A.y;
			}
		}
		move_object(Vector2{ 0, -max });
		teleport_to_left = false;
	}
	if (teleport_to_down) {
		float min = lines[0].point_A.y;
		for (int i = 1; i < lines.size(); i++) {
			if (lines[i].point_A.y < min) {
				min = lines[i].point_A.y;
			}
		}
		move_object(Vector2{ 0, SCREEN_HEIGHT + abs(min) });
	}
}
