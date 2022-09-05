#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#include "../include/vector3.hpp"
#include "../include/box.hpp"
#include "../include/ray.hpp"
#include "../include/camera.hpp"

#define HORIZONTAL_FOV 90
#define VERTICAL_FOV 90
#define VIEWPORT_WIDTH 800
#define VIEWPORT_HEIGHT 600

std::vector<Box> boxes;

double map(double value, double a, double b, double x, double y) {
	double percent = (value - a) / (b - a);
	return percent * (y - x) + x;
}

void render(double* fb, const Camera& c) {
	for (int x = 0; x < VIEWPORT_WIDTH; x ++) {
		for (int y = 0; y < VIEWPORT_HEIGHT; y ++) {
			// blank it out
			int i = (x * VIEWPORT_HEIGHT + y) * 3;
			fb[i] = 0;
			fb[i + 1] = 0;
			fb[i + 2] = 200;
			double offset_aangle = map(x, 0, VIEWPORT_WIDTH, -((double)HORIZONTAL_FOV/2), (double)HORIZONTAL_FOV/2);
			double offset_hangle = map(y, 0, VIEWPORT_HEIGHT, -((double)VERTICAL_FOV/2), (double)VERTICAL_FOV/2);
			#define PI 3.141592653589793
			offset_aangle = offset_aangle / 180 * PI;
			offset_hangle = offset_hangle / 180 * PI;
			
			Vector3 direction(
					std::sin(c.aangle / 180 * PI + offset_aangle),
					std::sin(c.hangle / 180 * PI + offset_hangle),
					std::cos(c.aangle / 180 * PI + offset_aangle));

			col_info collision = ray_march(Vector3(0, 0, 0), direction, boxes);
			if (collision.collided) {
				fb[i] = collision.box.color.x;
				fb[i + 1] = collision.box.color.y;
				fb[i + 2] = collision.box.color.z;
			}
		}
	}
}

int main() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow(
			"Window",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			800,
			600,
			SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	// creating things
	Camera camera = {Vector3(0, 0, 0), 0, 0};
	camera.aangle = 30;
	boxes.push_back(Box{
			position: Vector3(0, 0, 70),
			size: Vector3(20, 20, 20),
			color: Vector3(0, 255, 0)
			});	
	boxes.push_back(Box{
			position: Vector3(-10, -10, 90),
			size: Vector3(20, 20, 20),
			color: Vector3(200, 200, 0)
			});	

	while (true) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_QUIT:
					goto exit;
					break;
				default:
					break;
			}
		}
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderClear(renderer);

		// rendering
		double* framebuffer = new double[VIEWPORT_WIDTH * VIEWPORT_HEIGHT * 3]; // 3 for colors
		render(framebuffer, camera);
		for (int x = 0; x < VIEWPORT_WIDTH; x ++) {
			for (int y = 0; y < VIEWPORT_HEIGHT; y ++) {
				int r = framebuffer[(x * VIEWPORT_HEIGHT + y) * 3];
				int g = framebuffer[(x * VIEWPORT_HEIGHT + y) * 3 + 1];
				int b = framebuffer[(x * VIEWPORT_HEIGHT + y) * 3 + 2];
				SDL_SetRenderDrawColor(renderer, r, g, b, 255);
				SDL_RenderDrawPoint(renderer, x, y);
			}
		}
		delete[] framebuffer;

		SDL_RenderPresent(renderer);
		SDL_Delay(1000/60);
	}
exit:
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
