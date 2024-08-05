#pragma once
class line_segment{
public:
	Vector2 point_A;
	Vector2 point_B;
	Vector2 intersection_point;
	bool is_intersecting;
	bool is_overlapping;

	line_segment(Vector2 pointA, Vector2 pointB);
	void render_line();
	void calculate_intersection_point(line_segment line2);

};

