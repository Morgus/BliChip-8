/* Chip-8 Display
 * Aleksi Blinnikka 7.10.2012-
 */

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <stdlib.h>
#include <stdint.h>

typedef struct _Display
{
	uint8_t pixel[32][64];
} Display;

Display* CreateDisplay();
void DestroyDisplay(Display* disp);

#endif /* _DISPLAY_H_ */
