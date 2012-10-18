/* Chip-8 Display
 * Aleksi Blinnikka 7.10.2012-12.10.2012
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

/* Sets all screen pixels to 0 and updates the screen.
 * Called by opcode 00E0. */
void ClearDisplay(Display* disp);
/* Draws a sprite (max 8 * 15 pixels) using XOR for every pixel to be placed.
 * If this causes any pixels to be erased, the function returns 1, otherwise 0.
 * Called by opcode DXYN. */
uint8_t DrawSprite(Display* disp, uint8_t* sprite, int len, uint8_t x, uint8_t y);
/* Called everytime the screen has ben updated (when DrawSprite has been called). */
void UpdateDisplay(Display* disp);

/* Init/Shutdown */
Display* CreateDisplay();
void DestroyDisplay(Display* disp);

#endif /* _DISPLAY_H_ */
