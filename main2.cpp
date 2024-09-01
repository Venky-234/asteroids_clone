#include <iostream>
#include <raylib.h>
#include "line_segment.h"

int main() {
	InitWindow(500, 500, "test");
	SetTargetFPS(60);
	line_segment line1(Vector2{0, 0}, Vector2{300, 300});
	line_segment line2(Vector2{30, 10}, Vector2{80, 400});
	
	Vector2 mouse_pos;
	while (!WindowShouldClose()) {
		mouse_pos = GetMousePosition();
		
		float x1 = line1.point_A.x;
		float y1 = line1.point_A.y;
		float x2 = line1.point_B.x;
		float y2 = line1.point_B.y;

		
		if (IsKeyDown(KEY_W)) {
			line1.point_A.y -= 1;
			line1.point_B.y -= 1;
		}
		if (IsKeyDown(KEY_S)) {
			line1.point_A.y += 1;
			line1.point_B.y += 1;
		}
		if (IsKeyDown(KEY_A)) {
			line1.point_A.x -= 1;
			line1.point_B.x -= 1;
		}
		if (IsKeyDown(KEY_D)) {
			line1.point_A.x += 1;
			line1.point_B.x += 1;
		}
		BeginDrawing();
		ClearBackground(BLACK);
		line1.render_line();
		line2.render_line();
		EndDrawing();
	}
}