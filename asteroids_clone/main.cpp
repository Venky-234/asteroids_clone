#include <iostream>
#include <raylib.h>
#include <vector>
#include <chrono>
#include <iterator>
#include <assert.h>
#include <list>

#include "polygon_object.h"
#include "bullet.h"

int SCREEN_WIDTH = 1000;
int SCREEN_HEIGHT = 700;

void mouse_debug() {
	std::cout << "x: " << GetMousePosition().x << "\t";
	std::cout << "y: " << GetMousePosition().y << std::endl;
}
std::vector<Vector2> pts0;
std::vector<Vector2> pts1;
std::vector<Vector2> pts2;

polygon_object make_asteroid(int id) {
	// WRITE THE FUCKING FUCNTION NEXT TIME YOU COME HERE YOU BASTARD
	// DONT FUCKING FORGET OR ELSE YOU WILL CRY OVER YOUR CODE FOR THE NEXT 3 HOURS
	// DONT MAKE THE FUCKING MISTAKE
	polygon_object asteroid;
	if (id == 0) {
		asteroid = polygon_object(pts0, Vector2{ 0,0 }, Vector2{ 78, 76 });
	}
	else if (id == 1) {
		asteroid = polygon_object(pts1, Vector2{ 0,0 }, Vector2{ 34, 35 });
	}
	else if (id == 2) {
		asteroid = polygon_object(pts2, Vector2{ 0,0 }, Vector2{ 20, 20 });
	}
	else {
		assert(false);
	}

	asteroid.rotate_object((float)GetRandomValue(0, 2) + (float)rand() / RAND_MAX);
	float velocities[] = { -1.8, -1, 1, 1.8 };
	int ran = GetRandomValue(0, 3);
	switch (ran){
	case 0:
		asteroid.place_object(
			Vector2{
				-100, (float)GetRandomValue(0, SCREEN_HEIGHT)
			}
		);
		asteroid.velocity.x = velocities[GetRandomValue(0, 1)];
		asteroid.velocity.y = velocities[GetRandomValue(0, 3)];
		break;

	case 1:
		asteroid.place_object(
			Vector2{
				(float)GetRandomValue(0, SCREEN_WIDTH), (float)SCREEN_HEIGHT + 100
			}
		);
		asteroid.velocity.y = velocities[GetRandomValue(2, 3)];
		asteroid.velocity.x = velocities[GetRandomValue(0, 3)];
		break;

	case 2:
		asteroid.place_object(
			Vector2{
				(float)SCREEN_WIDTH + 100, (float)GetRandomValue(0, SCREEN_HEIGHT)
			}
		);
		asteroid.velocity.x = velocities[GetRandomValue(2, 3)];
		asteroid.velocity.y = velocities[GetRandomValue(0, 3)];
		break;

	case 3:
		asteroid.place_object(
			Vector2{
				(float)GetRandomValue(0, SCREEN_WIDTH), -100 
			}
		);
		asteroid.velocity.y = velocities[GetRandomValue(0, 1)];
		asteroid.velocity.x = velocities[GetRandomValue(0, 3)];
		break;
	}
	asteroid.id = id;
	return asteroid;
} 

int main() {

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "asteroids clone");
	SetTargetFPS(60);

	pts0 = std::vector<Vector2>({
		Vector2{0, 39},
		Vector2{27, 15},
		Vector2{39, 22},
		Vector2{50, 0},
		Vector2{86, 7},
		Vector2{104 ,0},
		Vector2{135, 21},
		Vector2{131, 37},
		Vector2{148, 40},
		Vector2{144, 64},
		Vector2{139, 74},
		Vector2{149, 86},
		Vector2{138, 104},
		Vector2{143, 128},
		Vector2{104, 145},
		Vector2{64, 144},
		Vector2{54, 148},
		Vector2{32, 131},
		Vector2{23, 133},
		Vector2{10, 118},
		Vector2{2, 102},
		Vector2{11, 78}
	});

	pts1 = std::vector<Vector2> ({
		Vector2{0, 30},
		Vector2{4, 18},
		Vector2{45, 4},
		Vector2{60, 13},
		Vector2{63, 25},
		Vector2{57, 41},
		Vector2{67, 51},
		Vector2{64, 62},
		Vector2{47, 61},
		Vector2{33, 67},
		Vector2{15, 58},
	});

	pts2 = std::vector<Vector2>({
		Vector2{1, 18},
		Vector2{3, 10},
		Vector2{12, 2},
		Vector2{25, 3},
		Vector2{37, 10},
		Vector2{38, 26},
		Vector2{34, 33},
		Vector2{27, 37},
		Vector2{14, 36},
		Vector2{14, 36},
		Vector2{6, 30},
		Vector2{6, 30},
		Vector2{1, 21}
	});
	
	std::vector<Vector2> spaceship_points({
		Vector2{35, 0},
		Vector2{70, 70},
		Vector2{35, 50},
		Vector2{0, 70}
	});


	int number_of_asteroids = 5;
	std::vector<polygon_object> asteroids;

	for (int i = 0; i < number_of_asteroids; i++) {
		asteroids.push_back(make_asteroid(GetRandomValue(0, 2)));
	}

	polygon_object spaceship(spaceship_points, Vector2{ 0,0 }, Vector2{ 35, 40 });
	spaceship.move_object(Vector2{ (float) SCREEN_WIDTH / 2, (float) SCREEN_HEIGHT / 2 });

	polygon_object obj(pts2, Vector2{0, 0}, Vector2{78, 76});

	std::vector<bullet> bullets;

	int bullet_index = 0;
	float bullet_delay = .1f;

	float spaceship_acceleration = 0.005;
	float spaceship_retardation = 0.02;

	float explosion_radius = 50.f;
	float explosion_velocity = 4.f;
	//float explosion_acceleration = 0.5f;
	Color explosion_color = WHITE;

	int score = 0;

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);

		float mag = sqrt(spaceship.velocity.x * spaceship.velocity.x + spaceship.velocity.y * spaceship.velocity.y);
		if (spaceship.id == 0) {
			if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) && mag <= 10) {
				Vector2 displacement = { spaceship.lines[0].point_A.x - spaceship.origin.x, spaceship.lines[0].point_A.y - spaceship.origin.y };
				displacement.x *= spaceship_acceleration;
				displacement.y *= spaceship_acceleration;
				spaceship.velocity.x += displacement.x;
				spaceship.velocity.y += displacement.y;
			}
			else {
				if (spaceship.velocity.x < 0) {
					spaceship.velocity.x += spaceship_retardation * -spaceship.velocity.x;
					if (spaceship.velocity.x + spaceship_retardation > 0) {
						spaceship.velocity.x = 0;
					}
				}
				if (spaceship.velocity.y < 0) {
					spaceship.velocity.y += spaceship_retardation * -spaceship.velocity.y;
					if (spaceship.velocity.y + spaceship_retardation > 0) {
						spaceship.velocity.y = 0;
					}
				}
				if (spaceship.velocity.x > 0) {
					spaceship.velocity.x -= spaceship_retardation * spaceship.velocity.x;
					if (spaceship.velocity.x - spaceship_retardation < 0) {
						spaceship.velocity.x = 0;
					}
				}
				if (spaceship.velocity.y > 0) {
					spaceship.velocity.y -= spaceship_retardation * spaceship.velocity.y;
					if (spaceship.velocity.y - spaceship_retardation < 0) {
						spaceship.velocity.y = 0;
					}
				}
			}
			spaceship.apply_velocity();
			spaceship.teleport_object();

			if (spaceship.id == 0 && (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))) {
				spaceship.rotate_object(-0.07);
			}
			if (spaceship.id == 0 && (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))) {
				spaceship.rotate_object(0.07);
			}


			if (IsKeyPressed(KEY_SPACE)) {
				bullet bul(spaceship.origin, spaceship.lines[0].point_A, 0.3f);
				bul.release_bullet = true;
				bullets.push_back(bul);
			}
		}
		
		for (int i = 0; i < bullets.size(); i++) {
			if (bullets[i].release_bullet) {
				bullets[i].render_bullet();
				bullets[i].update_bullet_position();
			}
			if (bullets[i].position.x < 0 || bullets[i].position.x >= SCREEN_WIDTH ||
				bullets[i].position.y < 0 || bullets[i].position.y >= SCREEN_HEIGHT
				)
			{
				bullets[i].release_bullet = false;
			}
		}
		for (int i = 0; i < bullets.size(); i++) {
			if(bullets[i].release_bullet == false)
			{
				bullets[i].release_bullet = false;
				bullets.erase(bullets.begin() + i);
				std::cout << "bullet erased index : " << i << std::endl;
				break;
			}
		}
		for (int i = 0; i < asteroids.size(); i++) {
			if (asteroids[i].id == -1) {
				asteroids.erase(asteroids.begin() + i);
				std::cout << "asteroid at index " << i << "erased" << std::endl;
				// create more asteroids if limit is low
				break;
			}
		}
		if (asteroids.size() < number_of_asteroids) {
			asteroids.push_back(
				make_asteroid(
					GetRandomValue(0, 2)
				)
			);
			std::cout << "[LOG] made asteroid : " << std::endl;
		}

		for(int i = 0; i < asteroids.size(); i++){
			if (spaceship.is_colliding(asteroids[i])) {
				// write some explosion code or some sort of death code here
				spaceship.id = -1;
			}
			for (int j = 0; j < bullets.size(); j++) {
				if (bullets[j].is_in_polygon(asteroids[i]) && bullets[j].release_bullet) {
					bullets[j].release_bullet = false;
					if (asteroids[i].id < 2) {
						Vector2 prev_origin = asteroids[i].origin;
						polygon_object ast = make_asteroid(asteroids[i].id + 1);
						ast.place_object(
							Vector2{
								prev_origin.x + GetRandomValue(5, 8),
								prev_origin.y + GetRandomValue(5, 8)
							}
						);
						asteroids.push_back(ast);
						asteroids[i] = make_asteroid(asteroids[i].id + 1);
						asteroids[i].place_object(prev_origin);
					}

					else {
						asteroids[i].id = -1; // asteroid should be deleted
					}
					score++;
				}
			}

			asteroids[i].apply_velocity();
			asteroids[i].teleport_object();
			asteroids[i].render_polygon();
		}
		if(spaceship.id == 0)
			spaceship.render_polygon();
		else {
			// render death or explosion
			DrawText("Press R to restart", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, 30, WHITE);
			DrawCircleLinesV(spaceship.origin, explosion_radius, explosion_color);
			if(explosion_radius - 50 >= 0)
				DrawCircleLinesV(spaceship.origin, explosion_radius - 50, explosion_color);

			if (explosion_color.a - explosion_velocity > 0) {
				explosion_color.a -= explosion_velocity;
				explosion_radius += explosion_velocity;
				//explosion_velocity += explosion_acceleration;
			}
			if (IsKeyPressed(KEY_R)) {
				asteroids.clear();
				for (int i = 0; i < number_of_asteroids; i++) {
					asteroids.push_back(make_asteroid(GetRandomValue(0, 2)));
				}
				spaceship.id = 0;
				spaceship.velocity = Vector2{ 0,0 };
				spaceship.place_object(Vector2{ (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 });
				explosion_radius = 50.f;
				explosion_color = WHITE;
				score = 0;
			}

		}
		DrawText(TextFormat("Score : %d", score), 100, 10, 20, WHITE);
		DrawFPS(10, 10);
		EndDrawing();
	}
}
