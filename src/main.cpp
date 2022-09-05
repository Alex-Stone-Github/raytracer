#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#include "../include/vector3.hpp"
#include "../include/box.hpp"
#include "../include/ray.hpp"

#define HORIZONTAL_FOV 90
#define VERTICAL_FOV 90
#define VIEWPORT_WIDTH 600
#define VIEWPORT_HEIGHT 520

std::vector<Box> boxes;

double map(double value, double a, double b, double x, double y) {
	double percent = (value - a) / (b - a);
	return percent * (y - x) + x;
}

void render(double* fb) {
	for (int x = 0; x < VIEWPORT_WIDTH; x ++) {
		for (int y = 0; y < VIEWPORT_HEIGHT; y ++) {
			// blank it out
			int i = x * VIEWPORT_HEIGHT + y;
			fb[i] = 100;
			double aangle = map(x, 0, VIEWPORT_WIDTH, -((double)HORIZONTAL_FOV/2), (double)HORIZONTAL_FOV/2);
			double hangle = map(y, 0, VIEWPORT_HEIGHT, -((double)VERTICAL_FOV/2), (double)VERTICAL_FOV/2);
			#define PI 3.141592653589793
			aangle = aangle / 180 * PI;
			hangle = hangle / 180 * PI;
			
			Vector3 direction(
					std::sin(aangle),
					std::sin(hangle),
					std::cos(aangle));

			bool raymarch = ray_march(Vector3(0, 0, 0), direction, boxes);
			if (raymarch) {
				fb[i] = 0;
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

	boxes.push_back(Box{
			position: Vector3(0, 0, 70),
			size: Vector3(10, 10, 10)
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
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderClear(renderer);

		// rendering
		double* framebuffer = new double[VIEWPORT_WIDTH * VIEWPORT_HEIGHT];
		render(framebuffer);
		for (int x = 0; x < VIEWPORT_WIDTH; x ++) {
			for (int y = 0; y < VIEWPORT_HEIGHT; y ++) {
				int brightness = framebuffer[x * VIEWPORT_HEIGHT + y];
				SDL_SetRenderDrawColor(renderer, brightness, brightness, brightness, 255);
				SDL_RenderDrawPoint(renderer, x, y);
			}
		}
		delete[] framebuffer;

		SDL_RenderPresent(renderer);
		SDL_Delay(7000/60);

	}
exit:
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
