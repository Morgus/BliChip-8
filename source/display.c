/* Display
 * Aleksi Blinnikka 8.10.2012-17.10.2012
 */

#include "display.h"

const int SCALE = 8;
const int WINDOW_WIDTH = 8 * 64;
const int WINDOW_HEIGHT = 8 * 32;

void ClearDisplay(Display* disp)
{
	int i, j;
	for (i = 0; i < 32; ++i)
		for (j = 0; j < 64; ++j)
			disp->pixel[i][j] = 0;
	SDL_SetRenderDrawColor(disp->renderer, 0, 0, 0, 255);
	SDL_RenderClear(disp->renderer);
	SDL_RenderPresent(disp->renderer);
}

uint8_t DrawSprite(Display* disp, uint8_t* sprite, int len, uint8_t x, uint8_t y)
{
	uint8_t VF = 0;
	uint8_t pixel;
	int temp_x, temp_y;
	int i, j;
	for (i = 0; i < len; ++i) {
		for (j = 0; j < 8; ++j) {
			pixel = (sprite[i] >> (7 - j)) & 0x01;
			temp_y = (y + i) % 32;
			temp_x = (x + j) % 64;
			disp->pixel[temp_y][temp_x] ^= pixel;
			if (disp->pixel[temp_y][temp_x] == 0) {
				if (pixel == 1)
					VF = 1;
			}
		}
	}
	return VF;
}

void UpdateDisplay(Display* disp)
{
	int i, j;
	
	SDL_SetRenderDrawColor(disp->renderer, 0, 0, 0, 255);
	SDL_RenderClear(disp->renderer);
	SDL_SetRenderDrawColor(disp->renderer, 255, 255, 255, 255);
	
	for (i = 0; i < 32; ++i) {
		for (j = 0; j < 64; ++j) {
			if (disp->pixel[i][j])
				SDL_RenderFillRect(disp->renderer, &(disp->pixelRect[i][j]));
		}
	}
	SDL_RenderPresent(disp->renderer);
}

Display* CreateDisplay()
{
	int i, j;
	Display* disp;
	disp = (Display*) malloc(sizeof(Display));
	
	disp->window = SDL_CreateWindow("Chip-8 Emulator", 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		WINDOW_WIDTH, WINDOW_HEIGHT, 
		SDL_WINDOW_SHOWN);
	disp->renderer = SDL_CreateRenderer(disp->window, -1, 
		SDL_RENDERER_ACCELERATED);
	
	for (i = 0; i < 32; ++i) {
		for (j = 0; j < 64; ++j) {
			disp->pixel[i][j] = 0;
			disp->pixelRect[i][j].x = SCALE * j;
			disp->pixelRect[i][j].y = SCALE * i;
			disp->pixelRect[i][j].w = SCALE;
			disp->pixelRect[i][j].h = SCALE;
		}
	}
	
	return disp;
}

void DestroyDisplay(Display* disp)
{
	SDL_DestroyRenderer(disp->renderer);
	SDL_DestroyWindow(disp->window);
	free(disp);
}
