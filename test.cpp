#include <iostream>
#include <raylib.h>
#include <vector>
#include "line_segment.h"

int SCREEN_WIDTH = 500;
int SCREEN_HEIGHT = 500;

int main() {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Test"); 
	SetTargetFPS(60);
	
	line_segment line_a(Vector2{ 50, 50 }, Vector2{ 400, 400 });
	line_segment line_b(Vector2{ 100, 50 }, Vector2{ 350, 90});

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		
		line_b.point_B = GetMousePosition();
		
		line_b.calculate_intersection_point(line_a);
		
		if (line_b.is_intersecting)
			DrawCircleV(line_b.intersection_point, 4, Color{ GREEN.r, GREEN.g, GREEN.b, 255});

		line_a.render_line();
		line_b.render_line();
		EndDrawing();
	}
	CloseWindow();
}