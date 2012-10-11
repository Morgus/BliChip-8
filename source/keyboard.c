/* Keyboard
 * Aleksi Blinnikka 8.10.2012-
 */

#include "keyboard.h"

void UpdateKeyboard(Keyboard* keyb)
{
	keyb->state = SDL_GetKeyboardState(NULL);
	
	if (keyb->state[KEY_0])
		keyb->key[0x0] = 1;
	else
		keyb->key[0x0] = 0;
	
	if (keyb->state[KEY_1])
		keyb->key[0x1] = 1;
	else
		keyb->key[0x1] = 0;
	
	if (keyb->state[KEY_2])
		keyb->key[0x2] = 1;
	else
		keyb->key[0x2] = 0;
	
	if (keyb->state[KEY_3])
		keyb->key[0x3] = 1;
	else
		keyb->key[0x3] = 0;
	
	if (keyb->state[KEY_4])
		keyb->key[0x4] = 1;
	else
		keyb->key[0x4] = 0;
	
	if (keyb->state[KEY_5])
		keyb->key[0x5] = 1;
	else
		keyb->key[0x5] = 0;
	
	if (keyb->state[KEY_6])
		keyb->key[0x6] = 1;
	else
		keyb->key[0x6] = 0;
	
	if (keyb->state[KEY_7])
		keyb->key[0x7] = 1;
	else
		keyb->key[0x7] = 0;
	
	if (keyb->state[KEY_8])
		keyb->key[0x8] = 1;
	else
		keyb->key[0x8] = 0;
	
	if (keyb->state[KEY_9])
		keyb->key[0x9] = 1;
	else
		keyb->key[0x9] = 0;
	
	if (keyb->state[KEY_A])
		keyb->key[0xA] = 1;
	else
		keyb->key[0xA] = 0;
	
	if (keyb->state[KEY_B])
		keyb->key[0xB] = 1;
	else
		keyb->key[0xB] = 0;
	
	if (keyb->state[KEY_C])
		keyb->key[0xC] = 1;
	else
		keyb->key[0xC] = 0;
	
	if (keyb->state[KEY_D])
		keyb->key[0xD] = 1;
	else
		keyb->key[0xD] = 0;
	
	if (keyb->state[KEY_E])
		keyb->key[0xE] = 1;
	else
		keyb->key[0xE] = 0;
	
	if (keyb->state[KEY_F])
		keyb->key[0xF] = 1;
	else
		keyb->key[0xF] = 0;
}

Keyboard* CreateKeyboard()
{
	Keyboard* keyb;
	keyb = (Keyboard*) malloc(sizeof(Keyboard));
	InitKeyboard(keyb);
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
