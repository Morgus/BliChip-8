/* Keyboard
 * Aleksi Blinnikka 8.10.2012-
 */

#include "keyboard.h"

void UpdateKeyboard(Keyboard* keyb)
{
}

Keyboard* InitKeyboard()
{
	int i;
	Keyboard* keyb;
	keyb = (Keyboard*) malloc(sizeof(Keyboard));
	for (i = 0; i < 16; ++i)
		keyb->key[i] = 0;
	return keyb;
}

void DestroyKeyboard(Keyboard* keyb)
{
	free(keyb);
}
