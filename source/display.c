/* Display
 * Aleksi Blinnikka 8.10.2012-
 */

#include "display.h"

const int SCALE = 4;
const int WINDOW_WIDTH = 4 * 64;
const int WINDOW_HEIGHT = 4 * 32;

void ClearDisplay(Display* disp)
{
	int i, j;
	SDL_SetRenderDrawColor(disp->renderer, 0, 0, 0, 255);
	SDL_RenderClear(disp->renderer);
	for (i = 0; i < 32; ++i)
		for (j = 0; j < 64; ++j)
			disp->pixel[i][j] = 0;
}

int CheckCoord(int coord, int axis)
{
	if (axis == 0) {
		if (coord < 0)
			coord += 32;
		else if (coord > 31)
			coord -= 32;
	}
	if (axis == 1) {
		if (coord < 0)
			coord += 64;
		else if (coord > 63)
			coord -= 64;
	}
	return coord;
}

uint8_t DrawSprite(Display* disp, uint8_t* sprite, int len, uint8_t x, uint8_t y)
{
	SDL_SetRenderDrawColor(disp->renderer, 255, 255, 255, 255);
	uint8_t VF = 0;
	uint8_t pixel;
	int temp_x, temp_y;
	int i, j;
	for (i = 0; i < len; ++i) {
		for (j = 0; j < 8; ++j) {
			pixel = (sprite[i] >> (7 - j)) & 0x01;
			temp_y = CheckCoord(y + i, 0);
			temp_x = CheckCoord(x + j, 1);
			if (!(pixel ^ disp->pixel[temp_y][temp_x])) {
				if (pixel == 1)
					VF = 1;
				disp->pixel[temp_y][temp_x] = 0;
			}
			else {
				disp->pixel[temp_y][temp_x] = 1;
			}
		}
	}
	UpdateDisplay(disp);
	return VF;
}

void UpdateDisplay(Display* disp)
{
	int i, j;
	for (i = 0; i < 32; ++i)
		for (j = 0; j < 64; ++j)
			if (disp->pixel[i][j])
				SDL_RenderFillRect(disp->renderer, &(disp->pixelRect[i][j]));
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
	free(disp);
}
