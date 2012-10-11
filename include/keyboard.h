/* Chip-8 Keyboard
 * Aleksi Blinnikka 8.10.2012-
 */

#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <SDL.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum _Keys
{
	KEY_1 = SDL_SCANCODE_1, KEY_2 = SDL_SCANCODE_2, KEY_3 = SDL_SCANCODE_3, KEY_C = SDL_SCANCODE_4,
	KEY_4 = SDL_SCANCODE_Q, KEY_5 = SDL_SCANCODE_W, KEY_6 = SDL_SCANCODE_E, KEY_D = SDL_SCANCODE_R,
	KEY_7 = SDL_SCANCODE_A, KEY_8 = SDL_SCANCODE_S, KEY_9 = SDL_SCANCODE_D, KEY_E = SDL_SCANCODE_F,
	KEY_A = SDL_SCANCODE_Z, KEY_0 = SDL_SCANCODE_X, KEY_B = SDL_SCANCODE_C, KEY_F = SDL_SCANCODE_V,
} Keys;

typedef struct _Keypad
{
	uint8_t key[16];
	Uint8* state;
} Keyboard;

void UpdateKeyboard(Keyboard* keyb);

Keyboard* CreateKeyboard();
void InitKeyboard(Keyboard* keyb);
void DestroyKeyboard(Keyboard* keyb);

#endif /* _KEYBOARD_H_ */
