/* Display
 * Aleksi Blinnikka 8.10.2012-
 */

#include "display.h"

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