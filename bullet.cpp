#include "bullet.h"
float lerp(float a, float b, float t);
extern int SCREEN_WIDTH;

bullet::bullet(Vector2 point_a, Vector2 point_b, float bullet_speed) {
	line_to_follow = line_segment(point_a, point_b);
	extrapolation_constant = 1.0f;

	//position.x = lerp(line_to_follow.point_A.x, line_to_follow.point_B.x, extrapolation_constant);
	//position.y = lerp(line_to_follow.point_A.y, line_to_follow.point_B.y, extrapolation_constant);
	position = line_to_follow.point_B;
	position.x -= bullet_size / 2;
	position.y -= bullet_size / 2;

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
		DrawRectangleV(position, Vector2{bullet_size, bullet_size}, WHITE);
		//DrawCircleV(position, 2, WHITE);
	}
}
/*
bool bullet::is_in_polygon(polygon_object obj) {
	 // for circle
	float angle = 0.0f;
	int divisions = 10;

	int radius = 2;
	for (; radius > 0; radius--) {
		while (angle < 2 * PI) {
			float x = cos(angle) * radius;
			float y = sin(angle) * radius;

			x += position.x;
			y += position.y;

			int intersecting_points = 0;

			line_segment cl(Vector2{ x, y }, Vector2{ (float)SCREEN_WIDTH * 2, position.y });

			for (int k = 0; k < obj.lines.size(); k++) {
				// calculate for center point
				cl.calculate_intersection_point(obj.lines[k]);

				if (cl.is_intersecting) {
					intersecting_points++;
				}
			}

			// check if the polygon is inside the polygon
			if (intersecting_points % 2 == 1) {
				// point is in the poylgon nigga
				return true;
			}
			angle += (2 * PI) / (float)divisions;

			float prev_x = x - (line_to_follow.point_B.x - line_to_follow.point_A.x) * bullet_speed;
			float prev_y = y - (line_to_follow.point_B.y - line_to_follow.point_A.y) * bullet_speed;
			
			line_segment cl2(Vector2{ prev_x, prev_y }, Vector2{ x, y });

			for (int k = 0; k < obj.lines.size(); k++) {
				cl2.calculate_intersection_point(obj.lines[k]);
				
				if (cl2.is_intersecting) {
					return true;
				}
			}
		}
	}

	line_segment cl(position, Vector2{ (float)SCREEN_WIDTH * 2, position.y });
	int intersecting_points = 0;
	for (int k = 0; k < obj.lines.size(); k++) {
		// calculate for center point
		cl.calculate_intersection_point(obj.lines[k]);

		if (cl.is_intersecting) {
			intersecting_points++;
		}
	}

	if (intersecting_points % 2 == 1) {
		return true;
	}

	return false;
}
*/

bool bullet::is_in_polygon(polygon_object obj) {
	int spacing = 3;
	for (int y = -3; y <= bullet_size + 3; y += spacing) {
		for (int x = -3; x <= bullet_size + 3; x += spacing) {
			line_segment cl(Vector2{ position.x + x, position.y + y }, Vector2{ (float)SCREEN_WIDTH * 2, position.y + y });

            //DrawLineV(cl.point_A, cl.point_B, Color{GREEN.r,GREEN.g,GREEN.b,100});

			int intersecting_points = 0;
			for (int k = 0; k < obj.lines.size(); k++) {
				// calculate for center point
				cl.calculate_intersection_point(obj.lines[k]);

				if (cl.is_intersecting) {
					intersecting_points++;
				}
			}

			if (intersecting_points % 2 == 1) {
				return true;
			}
			
			float prev_x = (float)x - (line_to_follow.point_B.x - line_to_follow.point_A.x) * bullet_speed;
            float prev_y = (float)y - (line_to_follow.point_B.y - line_to_follow.point_A.y) * bullet_speed;

            line_segment cl2(Vector2{ prev_x + position.x, prev_y + position.y}, Vector2{ (float)x + position.x, (float)y + position.y});

            //DrawLineV(cl2.point_A, cl2.point_B, Color{GREEN.r,GREEN.g,GREEN.b,100});
            //cl2.render_line();

            //DrawLineV(cl2.point_A, cl2.point_B, Color{GREEN.r,GREEN.g,GREEN.b,100});
            for (int k = 0; k < obj.lines.size(); k++) {
                cl2.calculate_intersection_point(obj.lines[k]);

                if (cl2.is_intersecting) {
                    return true;
                }
            }

		}
	}
	return false;
}
