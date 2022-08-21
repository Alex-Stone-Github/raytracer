#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#include "../include/vector3.hpp"
#include "../include/box.hpp"
#include "../include/ray.hpp"
#include "../include/camera.hpp"

#define HORIZONTAL_FOV 90
#define VERTICAL_FOV 60
#define VIEWPORT_WIDTH 600
#define VIEWPORT_HEIGHT 520


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

	//
	

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
		for (int x = 0; x < VIEWPORT_WIDTH; x ++) {
			for (int y = 0; y < VIEWPORT_HEIGHT; y ++) {
				int brightness = 200;
				SDL_SetRenderDrawColor(renderer, brightness, brightness, brightness, 255);
				SDL_RenderDrawPoint(renderer, x, y);
			}
		}
		SDL_RenderPresent(renderer);
		SDL_Delay(3000/60);
	}
exit:
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
