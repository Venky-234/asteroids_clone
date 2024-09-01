#pragma once
#include <raylib.h>
#include "line_segment.h"
#include <iostream>

float lerp(float a, float b, float t) {
	return a + (b - a) * t;
}
line_segment::line_segment(Vector2 pointA, Vector2 pointB) {
	point_A = pointA;
	point_B = pointB;
}

void line_segment::render_line() {
	DrawLineV(point_A, point_B, WHITE);
}

void line_segment::calculate_intersection_point(line_segment line2) {
	Vector2 A = Vector2(point_A);
	Vector2 B = Vector2(point_B);
	Vector2 C = Vector2(line2.point_A);
	Vector2 D = Vector2(line2.point_B);

	float t_top = (D.x - C.x) * (A.y - C.y) - (D.y - C.y) * (A.x - C.x);
	float u_top = (C.y - A.y) * (A.x - B.x) - (C.x - A.x) * (A.y - B.y);
	float bottom = (D.y - C.y) * (B.x - A.x) - (D.x - C.x) * (B.y - A.y);

	float u = u_top / bottom;
	float t = t_top / bottom;

	intersection_point = Vector2{
		lerp(point_A.x, point_B.x, t),
		lerp(point_A.y, point_B.y, t)
	};
		
	if (bottom != 0) {
		if (
			t >= 0.0f && t <= 1.0f &&
			u >= 0.0f && u <= 1.0f
		) 
		{
			is_intersecting = true;
		}
		else {
			is_intersecting = false;
		}
	}
	else {
		is_intersecting = false;
	}
}
