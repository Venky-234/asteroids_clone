#include "bullet.h"
float lerp(float a, float b, float t);
extern int SCREEN_WIDTH;

bullet::bullet(Vector2 point_a, Vector2 point_b, float bullet_speed) {
	line_to_follow = line_segment(point_a, point_b);
	extrapolation_constant = 1.0f;

	position.x = lerp(line_to_follow.point_A.x, line_to_follow.point_B.x, extrapolation_constant);
	position.y = lerp(line_to_follow.point_A.y, line_to_follow.point_B.y, extrapolation_constant);
	bullet::bullet_speed = bullet_speed;
	release_bullet = false;
}

void bullet::update_bullet_position() {
	//extrapolation_constant += bullet_speed;
	//position.x = lerp(line_to_follow.point_A.x, line_to_follow.point_B.x, extrapolation_constant);
	//position.y = lerp(line_to_follow.point_A.y, line_to_follow.point_B.y, extrapolation_constant);
	position.x += (line_to_follow.point_B.x - line_to_follow.point_A.x) * bullet_speed;
	position.y += (line_to_follow.point_B.y - line_to_follow.point_A.y) * bullet_speed;

}

void bullet::render_bullet() {
	if (release_bullet) {
		DrawCircleV(position, 2, WHITE);
	}
}

bool bullet::is_in_polygon(polygon_object obj) {
	int intersecting_points = 0;

	collision_line.point_A = position;
	collision_line.point_B = Vector2{ (float)SCREEN_WIDTH * 2 , position.y };

	for (int k = 0; k< obj.lines.size(); k++) {
		collision_line.calculate_intersection_point(obj.lines[k]);
		if (collision_line.is_intersecting) {
			intersecting_points++;
		}
	}

	// check if the polygon is inside the polygon
	if (intersecting_points % 2 == 1) {
		// point is in the poylgon nigga
		return true;
	}

	return false;
}
