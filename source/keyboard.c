/* Keyboard
 * Aleksi Blinnikka 8.10.2012-
 */

#include "keyboard.h"

void UpdateKeyboard(Keyboard* keyb)
{
}

Keyboard* CreateKeyboard()
{
	Keyboard* keyb;
	keyb = (Keyboard*) malloc(sizeof(Keyboard));
	return keyb;
}

void InitKeyboard(Keyboard* keyb)
{
	int i;
	for (i = 0; i < 16; ++i)
		keyb->key[i] = 0;
}

void DestroyKeyboard(Keyboard* keyb)
{
	free(keyb);
}
