/* Display
 * Aleksi Blinnikka 8.10.2012-
 */

#include "display.h"

void ClearDisplay(Display* disp)
{
}

uint8_t DrawSprite(Display* disp, uint8_t* sprite, uint8_t x, uint8_t y)
{
	return 0;
}

void UpdateDisplay(Display* disp)
{
}

Display* CreateDisplay()
{
	Display* disp;
	disp = (Display*) malloc(sizeof(Display));
	return disp;
}

void DestroyDisplay(Display* disp)
{
	free(disp);
}
