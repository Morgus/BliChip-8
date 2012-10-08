/* Chip-8 Keyboard
 * Aleksi Blinnikka 8.10.2012-
 */

#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <stdlib.h>
#include <stdint.h>

typedef struct _Keypad
{
	uint8_t key[16];
} Keyboard;

void UpdateKeyboard(Keyboard* keyb);
Keyboard* InitKeyboard();
void DestroyKeyboard(Keyboard* keyb);

#endif /* _KEYBOARD_H_ */
