/* Chip-8 Display
 * Aleksi Blinnikka 7.10.2012-
 */

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <SDL.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct _Display
{
	uint8_t pixel[32][64];
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Rect pixelRect[32][64];
} Display;

void ClearDisplay(Display* disp);
uint8_t DrawSprite(Display* disp, uint8_t* sprite, uint8_t x, uint8_t y);
void UpdateDisplay(Display* disp);

Display* CreateDisplay();
void DestroyDisplay(Display* disp);

#endif /* _DISPLAY_H_ */
