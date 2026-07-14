/*
 * (C) Gražvydas "notaz" Ignotas, 2012
 *
 * This work is licensed under the terms of any of these licenses
 * (at your option):
 *  - GNU GPL, version 2 or later.
 *  - GNU LGPL, version 2.1 or later.
 *  - MAME license.
 * See the COPYING file in the top-level directory.
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <SDL.h>
#include "input.h"
#include "in_sdl.h"

#ifdef USE_SDL2
#ifndef SDLK_LAST
#define SDLK_LAST SDL_NUM_SCANCODES
#endif
#ifndef SDL_DEFAULT_REPEAT_DELAY
#define SDL_DEFAULT_REPEAT_DELAY 500
#endif
#ifndef SDL_DEFAULT_REPEAT_INTERVAL
#define SDL_DEFAULT_REPEAT_INTERVAL 30
#endif
#ifndef SDL_ENABLE
#define SDL_ENABLE 1
#endif
#ifndef SDL_DISABLE
#define SDL_DISABLE 0
#endif
#ifndef SDL_KEYDOWNMASK
#define SDL_KEYDOWNMASK (1u << 0)
#endif
#ifndef SDL_KEYUPMASK
#define SDL_KEYUPMASK (1u << 1)
#endif
#ifndef SDL_JOYAXISMOTIONMASK
#define SDL_JOYAXISMOTIONMASK (1u << 2)
#endif
#ifndef SDL_JOYBALLMOTIONMASK
#define SDL_JOYBALLMOTIONMASK (1u << 3)
#endif
#ifndef SDL_JOYHATMOTIONMASK
#define SDL_JOYHATMOTIONMASK (1u << 4)
#endif
#ifndef SDL_JOYBUTTONDOWNMASK
#define SDL_JOYBUTTONDOWNMASK (1u << 5)
#endif
#ifndef SDL_JOYBUTTONUPMASK
#define SDL_JOYBUTTONUPMASK (1u << 6)
#endif
#ifndef SDL_ALLEVENTS
#define SDL_ALLEVENTS 0xffffffffu
#endif
#ifndef JOY_EVENTS
#define JOY_EVENTS (SDL_JOYAXISMOTIONMASK | SDL_JOYBALLMOTIONMASK | SDL_JOYHATMOTIONMASK \
		    | SDL_JOYBUTTONDOWNMASK | SDL_JOYBUTTONUPMASK)
#endif

#define SDLK_KP0 SDL_SCANCODE_KP_0
#define SDLK_KP1 SDL_SCANCODE_KP_1
#define SDLK_KP2 SDL_SCANCODE_KP_2
#define SDLK_KP3 SDL_SCANCODE_KP_3
#define SDLK_KP4 SDL_SCANCODE_KP_4
#define SDLK_KP5 SDL_SCANCODE_KP_5
#define SDLK_KP6 SDL_SCANCODE_KP_6
#define SDLK_KP7 SDL_SCANCODE_KP_7
#define SDLK_KP8 SDL_SCANCODE_KP_8
#define SDLK_KP9 SDL_SCANCODE_KP_9
#define SDLK_KP_PERIOD SDL_SCANCODE_KP_PERIOD
#define SDLK_KP_DIVIDE SDL_SCANCODE_KP_DIVIDE
#define SDLK_KP_MULTIPLY SDL_SCANCODE_KP_MULTIPLY
#define SDLK_KP_MINUS SDL_SCANCODE_KP_MINUS
#define SDLK_KP_PLUS SDL_SCANCODE_KP_PLUS
#define SDLK_KP_ENTER SDL_SCANCODE_KP_ENTER
#define SDLK_KP_EQUALS SDL_SCANCODE_KP_EQUALS
#define SDLK_NUMLOCK SDL_SCANCODE_NUMLOCKCLEAR
#define SDLK_SCROLLOCK SDL_SCANCODE_SCROLLLOCK
#define SDLK_RMETA SDL_SCANCODE_RGUI
#define SDLK_LMETA SDL_SCANCODE_LGUI
#define SDLK_LSUPER SDL_SCANCODE_LGUI
#define SDLK_RSUPER SDL_SCANCODE_RGUI
#define SDLK_COMPOSE SDL_SCANCODE_APPLICATION
#define SDLK_WORLD_0 (SDL_NUM_SCANCODES - 4)
#define SDLK_WORLD_1 (SDL_NUM_SCANCODES - 3)
#define SDLK_WORLD_2 (SDL_NUM_SCANCODES - 2)
#define SDLK_WORLD_3 (SDL_NUM_SCANCODES - 1)

/* SDL2 keycodes are not compact array indexes; keep this driver on scancodes. */
#undef SDLK_BACKSPACE
#undef SDLK_TAB
#undef SDLK_CLEAR
#undef SDLK_RETURN
#undef SDLK_PAUSE
#undef SDLK_ESCAPE
#undef SDLK_SPACE
#undef SDLK_EXCLAIM
#undef SDLK_QUOTEDBL
#undef SDLK_HASH
#undef SDLK_DOLLAR
#undef SDLK_AMPERSAND
#undef SDLK_QUOTE
#undef SDLK_LEFTPAREN
#undef SDLK_RIGHTPAREN
#undef SDLK_ASTERISK
#undef SDLK_PLUS
#undef SDLK_COMMA
#undef SDLK_MINUS
#undef SDLK_PERIOD
#undef SDLK_SLASH
#undef SDLK_0
#undef SDLK_1
#undef SDLK_2
#undef SDLK_3
#undef SDLK_4
#undef SDLK_5
#undef SDLK_6
#undef SDLK_7
#undef SDLK_8
#undef SDLK_9
#undef SDLK_COLON
#undef SDLK_SEMICOLON
#undef SDLK_LESS
#undef SDLK_EQUALS
#undef SDLK_GREATER
#undef SDLK_QUESTION
#undef SDLK_AT
#undef SDLK_LEFTBRACKET
#undef SDLK_BACKSLASH
#undef SDLK_RIGHTBRACKET
#undef SDLK_CARET
#undef SDLK_UNDERSCORE
#undef SDLK_BACKQUOTE
#undef SDLK_a
#undef SDLK_b
#undef SDLK_c
#undef SDLK_d
#undef SDLK_e
#undef SDLK_f
#undef SDLK_g
#undef SDLK_h
#undef SDLK_i
#undef SDLK_j
#undef SDLK_k
#undef SDLK_l
#undef SDLK_m
#undef SDLK_n
#undef SDLK_o
#undef SDLK_p
#undef SDLK_q
#undef SDLK_r
#undef SDLK_s
#undef SDLK_t
#undef SDLK_u
#undef SDLK_v
#undef SDLK_w
#undef SDLK_x
#undef SDLK_y
#undef SDLK_z
#undef SDLK_DELETE
#undef SDLK_UP
#undef SDLK_DOWN
#undef SDLK_RIGHT
#undef SDLK_LEFT
#undef SDLK_INSERT
#undef SDLK_HOME
#undef SDLK_END
#undef SDLK_PAGEUP
#undef SDLK_PAGEDOWN
#undef SDLK_F1
#undef SDLK_F2
#undef SDLK_F3
#undef SDLK_F4
#undef SDLK_F5
#undef SDLK_F6
#undef SDLK_F7
#undef SDLK_F8
#undef SDLK_F9
#undef SDLK_F10
#undef SDLK_F11
#undef SDLK_F12
#undef SDLK_F13
#undef SDLK_F14
#undef SDLK_F15
#undef SDLK_CAPSLOCK
#undef SDLK_RSHIFT
#undef SDLK_LSHIFT
#undef SDLK_RCTRL
#undef SDLK_LCTRL
#undef SDLK_RALT
#undef SDLK_LALT
#undef SDLK_MODE

#define SDLK_BACKSPACE SDL_SCANCODE_BACKSPACE
#define SDLK_TAB SDL_SCANCODE_TAB
#define SDLK_CLEAR SDL_SCANCODE_DELETE
#define SDLK_RETURN SDL_SCANCODE_RETURN
#define SDLK_PAUSE SDL_SCANCODE_PAUSE
#define SDLK_ESCAPE SDL_SCANCODE_ESCAPE
#define SDLK_SPACE SDL_SCANCODE_SPACE
#define SDLK_EXCLAIM SDL_SCANCODE_1
#define SDLK_QUOTEDBL SDL_SCANCODE_APOSTROPHE
#define SDLK_HASH SDL_SCANCODE_3
#define SDLK_DOLLAR SDL_SCANCODE_4
#define SDLK_AMPERSAND SDL_SCANCODE_7
#define SDLK_QUOTE SDL_SCANCODE_APOSTROPHE
#define SDLK_LEFTPAREN SDL_SCANCODE_9
#define SDLK_RIGHTPAREN SDL_SCANCODE_0
#define SDLK_ASTERISK SDL_SCANCODE_8
#define SDLK_PLUS SDL_SCANCODE_EQUALS
#define SDLK_COMMA SDL_SCANCODE_COMMA
#define SDLK_MINUS SDL_SCANCODE_MINUS
#define SDLK_PERIOD SDL_SCANCODE_PERIOD
#define SDLK_SLASH SDL_SCANCODE_SLASH
#define SDLK_0 SDL_SCANCODE_0
#define SDLK_1 SDL_SCANCODE_1
#define SDLK_2 SDL_SCANCODE_2
#define SDLK_3 SDL_SCANCODE_3
#define SDLK_4 SDL_SCANCODE_4
#define SDLK_5 SDL_SCANCODE_5
#define SDLK_6 SDL_SCANCODE_6
#define SDLK_7 SDL_SCANCODE_7
#define SDLK_8 SDL_SCANCODE_8
#define SDLK_9 SDL_SCANCODE_9
#define SDLK_COLON SDL_SCANCODE_SEMICOLON
#define SDLK_SEMICOLON SDL_SCANCODE_SEMICOLON
#define SDLK_LESS SDL_SCANCODE_COMMA
#define SDLK_EQUALS SDL_SCANCODE_EQUALS
#define SDLK_GREATER SDL_SCANCODE_PERIOD
#define SDLK_QUESTION SDL_SCANCODE_SLASH
#define SDLK_AT SDL_SCANCODE_2
#define SDLK_LEFTBRACKET SDL_SCANCODE_LEFTBRACKET
#define SDLK_BACKSLASH SDL_SCANCODE_BACKSLASH
#define SDLK_RIGHTBRACKET SDL_SCANCODE_RIGHTBRACKET
#define SDLK_CARET SDL_SCANCODE_6
#define SDLK_UNDERSCORE SDL_SCANCODE_MINUS
#define SDLK_BACKQUOTE SDL_SCANCODE_GRAVE
#define SDLK_a SDL_SCANCODE_A
#define SDLK_b SDL_SCANCODE_B
#define SDLK_c SDL_SCANCODE_C
#define SDLK_d SDL_SCANCODE_D
#define SDLK_e SDL_SCANCODE_E
#define SDLK_f SDL_SCANCODE_F
#define SDLK_g SDL_SCANCODE_G
#define SDLK_h SDL_SCANCODE_H
#define SDLK_i SDL_SCANCODE_I
#define SDLK_j SDL_SCANCODE_J
#define SDLK_k SDL_SCANCODE_K
#define SDLK_l SDL_SCANCODE_L
#define SDLK_m SDL_SCANCODE_M
#define SDLK_n SDL_SCANCODE_N
#define SDLK_o SDL_SCANCODE_O
#define SDLK_p SDL_SCANCODE_P
#define SDLK_q SDL_SCANCODE_Q
#define SDLK_r SDL_SCANCODE_R
#define SDLK_s SDL_SCANCODE_S
#define SDLK_t SDL_SCANCODE_T
#define SDLK_u SDL_SCANCODE_U
#define SDLK_v SDL_SCANCODE_V
#define SDLK_w SDL_SCANCODE_W
#define SDLK_x SDL_SCANCODE_X
#define SDLK_y SDL_SCANCODE_Y
#define SDLK_z SDL_SCANCODE_Z
#define SDLK_DELETE SDL_SCANCODE_DELETE
#define SDLK_UP SDL_SCANCODE_UP
#define SDLK_DOWN SDL_SCANCODE_DOWN
#define SDLK_RIGHT SDL_SCANCODE_RIGHT
#define SDLK_LEFT SDL_SCANCODE_LEFT
#define SDLK_INSERT SDL_SCANCODE_INSERT
#define SDLK_HOME SDL_SCANCODE_HOME
#define SDLK_END SDL_SCANCODE_END
#define SDLK_PAGEUP SDL_SCANCODE_PAGEUP
#define SDLK_PAGEDOWN SDL_SCANCODE_PAGEDOWN
#define SDLK_F1 SDL_SCANCODE_F1
#define SDLK_F2 SDL_SCANCODE_F2
#define SDLK_F3 SDL_SCANCODE_F3
#define SDLK_F4 SDL_SCANCODE_F4
#define SDLK_F5 SDL_SCANCODE_F5
#define SDLK_F6 SDL_SCANCODE_F6
#define SDLK_F7 SDL_SCANCODE_F7
#define SDLK_F8 SDL_SCANCODE_F8
#define SDLK_F9 SDL_SCANCODE_F9
#define SDLK_F10 SDL_SCANCODE_F10
#define SDLK_F11 SDL_SCANCODE_F11
#define SDLK_F12 SDL_SCANCODE_F12
#define SDLK_F13 SDL_SCANCODE_F13
#define SDLK_F14 SDL_SCANCODE_F14
#define SDLK_F15 SDL_SCANCODE_F15
#define SDLK_CAPSLOCK SDL_SCANCODE_CAPSLOCK
#define SDLK_RSHIFT SDL_SCANCODE_RSHIFT
#define SDLK_LSHIFT SDL_SCANCODE_LSHIFT
#define SDLK_RCTRL SDL_SCANCODE_RCTRL
#define SDLK_LCTRL SDL_SCANCODE_LCTRL
#define SDLK_RALT SDL_SCANCODE_RALT
#define SDLK_LALT SDL_SCANCODE_LALT
#define SDLK_MODE SDL_SCANCODE_MODE

static inline const char *sdl_joystick_name(int index)
{
	return SDL_JoystickNameForIndex(index);
}

static inline void sdl_fix_event_key(SDL_Event *event)
{
	if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP)
		event->key.keysym.sym = event->key.keysym.scancode;
}

static inline void sdl_event_range_from_mask(Uint32 mask, Uint32 *min_type, Uint32 *max_type)
{
	if ((mask & (SDL_KEYDOWNMASK | SDL_KEYUPMASK)) == mask) {
		*min_type = SDL_KEYDOWN;
		*max_type = SDL_KEYUP;
	} else if ((mask & JOY_EVENTS) == mask) {
		*min_type = SDL_JOYAXISMOTION;
		*max_type = SDL_JOYBUTTONUP;
	} else {
		*min_type = SDL_FIRSTEVENT;
		*max_type = SDL_LASTEVENT;
	}
}

static inline int sdl_event_matches_mask(Uint32 mask, Uint32 type)
{
	switch (type) {
	case SDL_KEYDOWN:
		return !!(mask & SDL_KEYDOWNMASK);
	case SDL_KEYUP:
		return !!(mask & SDL_KEYUPMASK);
	case SDL_JOYAXISMOTION:
		return !!(mask & SDL_JOYAXISMOTIONMASK);
	case SDL_JOYBALLMOTION:
		return !!(mask & SDL_JOYBALLMOTIONMASK);
	case SDL_JOYHATMOTION:
		return !!(mask & SDL_JOYHATMOTIONMASK);
	case SDL_JOYBUTTONDOWN:
		return !!(mask & SDL_JOYBUTTONDOWNMASK);
	case SDL_JOYBUTTONUP:
		return !!(mask & SDL_JOYBUTTONUPMASK);
	default:
		return !!(mask & ~(SDL_KEYDOWNMASK | SDL_KEYUPMASK | JOY_EVENTS));
	}
}

static inline int sdl_peep_events_compat(SDL_Event *events, int numevents, SDL_eventaction action, Uint32 mask)
{
	Uint32 min_type = SDL_FIRSTEVENT;
	Uint32 max_type = SDL_LASTEVENT;
	int count, i;

	sdl_event_range_from_mask(mask, &min_type, &max_type);
	count = SDL_PeepEvents(events, numevents, action, min_type, max_type);

	if (events != NULL && count > 0) {
		for (i = 0; i < count; i++) {
			if (action == SDL_GETEVENT &&
			    !sdl_event_matches_mask(mask, events[i].type)) {
				SDL_PushEvent(&events[i]);
				if (i + 1 < count)
					memmove(&events[i], &events[i + 1],
						(count - i - 1) * sizeof(events[0]));
				count--;
				i--;
				continue;
			}
			sdl_fix_event_key(&events[i]);
		}
	}

	return count;
}
#define SDL_JoystickName(i) sdl_joystick_name(i)
#define SDL_PeepEvents(events, numevents, action, mask) \
	sdl_peep_events_compat((events), (numevents), (action), (mask))
#endif

#define IN_SDL_PREFIX "sdl:"
/* should be machine word for best performace */
typedef unsigned long keybits_t;
#define KEYBITS_WORD_BITS (sizeof(keybits_t) * 8)

struct in_sdl_state {
	const in_drv_t *drv;
	SDL_Joystick *joy;
	int joy_id;
#ifdef USE_SDL2
	int joy_index;
	uint8_t joy_buttons[IN_SDL_JOY_BUTTON_COUNT];
	int joy_axes[2];
#endif
	int axis_keydown[2];
	keybits_t keystate[IN_SDL_KEY_COUNT / KEYBITS_WORD_BITS + 1];
	// emulator keys should always be processed immediately lest one is lost
	keybits_t emu_keys[IN_SDL_KEY_COUNT / KEYBITS_WORD_BITS + 1];
};

static void (*ext_event_handler)(void *event);

#ifdef USE_SDL2
static int in_sdl_debug_input(void)
{
	static int enabled = -1;

	if (enabled < 0)
		enabled = getenv("PICOARCH_SDL_INPUT_DEBUG") != NULL;
	return enabled;
}
#endif

static const char * const in_sdl_keys[IN_SDL_KEY_COUNT] = {
	[SDLK_BACKSPACE] = "backspace",
	[SDLK_TAB] = "tab",
#ifndef USE_SDL2
	[SDLK_CLEAR] = "clear",
#endif
	[SDLK_RETURN] = "return",
	[SDLK_PAUSE] = "pause",
	[SDLK_ESCAPE] = "escape",
	[SDLK_SPACE] = "space",
#ifndef USE_SDL2
	[SDLK_EXCLAIM]  = "!",
	[SDLK_QUOTEDBL]  = "\"",
	[SDLK_HASH]  = "#",
	[SDLK_DOLLAR]  = "$",
	[SDLK_AMPERSAND]  = "&",
#endif
	[SDLK_QUOTE] = "'",
#ifndef USE_SDL2
	[SDLK_LEFTPAREN] = "(",
	[SDLK_RIGHTPAREN] = ")",
	[SDLK_ASTERISK] = "*",
	[SDLK_PLUS] = "+",
#endif
	[SDLK_COMMA] = ",",
	[SDLK_MINUS] = "-",
	[SDLK_PERIOD] = ".",
	[SDLK_SLASH] = "/",
	[SDLK_0] = "0",
	[SDLK_1] = "1",
	[SDLK_2] = "2",
	[SDLK_3] = "3",
	[SDLK_4] = "4",
	[SDLK_5] = "5",
	[SDLK_6] = "6",
	[SDLK_7] = "7",
	[SDLK_8] = "8",
	[SDLK_9] = "9",
#ifndef USE_SDL2
	[SDLK_COLON] = ":",
#endif
	[SDLK_SEMICOLON] = ";",
#ifndef USE_SDL2
	[SDLK_LESS] = "<",
#endif
	[SDLK_EQUALS] = "=",
#ifndef USE_SDL2
	[SDLK_GREATER] = ">",
	[SDLK_QUESTION] = "?",
	[SDLK_AT] = "@",
#endif
	[SDLK_LEFTBRACKET] = "[",
	[SDLK_BACKSLASH] = "\\",
	[SDLK_RIGHTBRACKET] = "]",
#ifndef USE_SDL2
	[SDLK_CARET] = "^",
	[SDLK_UNDERSCORE] = "_",
#endif
	[SDLK_BACKQUOTE] = "`",
	[SDLK_a] = "a",
	[SDLK_b] = "b",
	[SDLK_c] = "c",
	[SDLK_d] = "d",
	[SDLK_e] = "e",
	[SDLK_f] = "f",
	[SDLK_g] = "g",
	[SDLK_h] = "h",
	[SDLK_i] = "i",
	[SDLK_j] = "j",
	[SDLK_k] = "k",
	[SDLK_l] = "l",
	[SDLK_m] = "m",
	[SDLK_n] = "n",
	[SDLK_o] = "o",
	[SDLK_p] = "p",
	[SDLK_q] = "q",
	[SDLK_r] = "r",
	[SDLK_s] = "s",
	[SDLK_t] = "t",
	[SDLK_u] = "u",
	[SDLK_v] = "v",
	[SDLK_w] = "w",
	[SDLK_x] = "x",
	[SDLK_y] = "y",
	[SDLK_z] = "z",
	[SDLK_DELETE] = "delete",

	[SDLK_KP0] = "[0]",
	[SDLK_KP1] = "[1]",
	[SDLK_KP2] = "[2]",
	[SDLK_KP3] = "[3]",
	[SDLK_KP4] = "[4]",
	[SDLK_KP5] = "[5]",
	[SDLK_KP6] = "[6]",
	[SDLK_KP7] = "[7]",
	[SDLK_KP8] = "[8]",
	[SDLK_KP9] = "[9]",
	[SDLK_KP_PERIOD] = "[.]",
	[SDLK_KP_DIVIDE] = "[/]",
	[SDLK_KP_MULTIPLY] = "[*]",
	[SDLK_KP_MINUS] = "[-]",
	[SDLK_KP_PLUS] = "[+]",
	[SDLK_KP_ENTER] = "enter",
	[SDLK_KP_EQUALS] = "equals",

	[SDLK_UP] = "up",
	[SDLK_DOWN] = "down",
	[SDLK_RIGHT] = "right",
	[SDLK_LEFT] = "left",
	[SDLK_INSERT] = "insert",
	[SDLK_HOME] = "home",
	[SDLK_END] = "end",
	[SDLK_PAGEUP] = "page up",
	[SDLK_PAGEDOWN] = "page down",

	[SDLK_F1] = "f1",
	[SDLK_F2] = "f2",
	[SDLK_F3] = "f3",
	[SDLK_F4] = "f4",
	[SDLK_F5] = "f5",
	[SDLK_F6] = "f6",
	[SDLK_F7] = "f7",
	[SDLK_F8] = "f8",
	[SDLK_F9] = "f9",
	[SDLK_F10] = "f10",
	[SDLK_F11] = "f11",
	[SDLK_F12] = "f12",
	[SDLK_F13] = "f13",
	[SDLK_F14] = "f14",
	[SDLK_F15] = "f15",

	[SDLK_NUMLOCK] = "numlock",
	[SDLK_CAPSLOCK] = "caps lock",
	[SDLK_SCROLLOCK] = "scroll lock",
	[SDLK_RSHIFT] = "right shift",
	[SDLK_LSHIFT] = "left shift",
	[SDLK_RCTRL] = "right ctrl",
	[SDLK_LCTRL] = "left ctrl",
	[SDLK_RALT] = "right alt",
	[SDLK_LALT] = "left alt",
	[SDLK_RMETA] = "right meta",
	[SDLK_LMETA] = "left meta",
	[SDLK_LSUPER] = "left super",	/* "Windows" keys */
	[SDLK_RSUPER] = "right super",	
	[SDLK_MODE] = "alt gr",
	[SDLK_COMPOSE] = "compose",

	[SDL_JOY_BUTTON(0)] = "joy 0",
	[SDL_JOY_BUTTON(1)] = "joy 1",
	[SDL_JOY_BUTTON(2)] = "joy 2",
	[SDL_JOY_BUTTON(3)] = "joy 3",
	[SDL_JOY_BUTTON(4)] = "joy 4",
	[SDL_JOY_BUTTON(5)] = "joy 5",
	[SDL_JOY_BUTTON(6)] = "joy 6",
	[SDL_JOY_BUTTON(7)] = "joy 7",
	[SDL_JOY_BUTTON(8)] = "joy 8",
	[SDL_JOY_BUTTON(9)] = "joy 9",
	[SDL_JOY_BUTTON(10)] = "joy 10",
	[SDL_JOY_BUTTON(11)] = "joy 11",
	[SDL_JOY_BUTTON(12)] = "joy 12",
	[SDL_JOY_BUTTON(13)] = "joy 13",
	[SDL_JOY_BUTTON(14)] = "joy 14",
	[SDL_JOY_BUTTON(15)] = "joy 15",
};

static void in_sdl_probe(const in_drv_t *drv)
{
	const struct in_pdata *pdata = drv->pdata;
	const char * const * key_names = in_sdl_keys;
	struct in_sdl_state *state;
	SDL_Joystick *joy;
	int i, joycount;
	char name[256];

	if (pdata->key_names)
		key_names = pdata->key_names;

	state = calloc(1, sizeof(*state));
	if (state == NULL) {
		fprintf(stderr, "in_sdl: OOM\n");
		return;
	}

	state->drv = drv;
	in_register(IN_SDL_PREFIX "keys", -1, state, IN_SDL_KEY_COUNT,
		key_names, 0);

	/* joysticks go here too */
	if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) != 0) {
		fprintf(stderr, "in_sdl: joystick init failed: %s\n", SDL_GetError());
		return;
	}

	joycount = SDL_NumJoysticks();
#ifdef USE_SDL2
	if (in_sdl_debug_input())
		fprintf(stderr, "in_sdl: joystick count=%d\n", joycount);
#endif
	for (i = 0; i < joycount; i++) {
		joy = SDL_JoystickOpen(i);
		if (joy == NULL) {
#ifdef USE_SDL2
			if (in_sdl_debug_input())
				fprintf(stderr, "in_sdl: open joystick %d failed: %s\n",
					i, SDL_GetError());
#endif
			continue;
		}

		state = calloc(1, sizeof(*state));
		if (state == NULL) {
			fprintf(stderr, "in_sdl: OOM\n");
			break;
		}
		state->joy = joy;
#ifdef USE_SDL2
		state->joy_id = SDL_JoystickInstanceID(joy);
		state->joy_index = i;
		if (in_sdl_debug_input())
			fprintf(stderr,
				"in_sdl: opened joystick index=%d instance=%d name=%s axes=%d buttons=%d\n",
				i, state->joy_id, SDL_JoystickNameForIndex(i),
				SDL_JoystickNumAxes(joy), SDL_JoystickNumButtons(joy));
#else
		state->joy_id = i;
#endif
		state->drv = drv;

		snprintf(name, sizeof(name), IN_SDL_PREFIX "%s", SDL_JoystickName(i));
		in_register(name, -1, state, IN_SDL_KEY_COUNT, key_names, 0);
	}

	if (joycount > 0)
		SDL_JoystickEventState(SDL_ENABLE);
}

static void in_sdl_free(void *drv_data)
{
	struct in_sdl_state *state = drv_data;

	if (state != NULL) {
		if (state->joy != NULL)
			SDL_JoystickClose(state->joy);
		free(state);
	}
}

static const char * const *
in_sdl_get_key_names(const in_drv_t *drv, int *count)
{
	const struct in_pdata *pdata = drv->pdata;
	*count = IN_SDL_KEY_COUNT;

	if (pdata->key_names)
		return pdata->key_names;
	return in_sdl_keys;
}

/* could use SDL_GetKeyState, but this gives better packing */
static void update_keystate(keybits_t *keystate, int sym, int is_down)
{
	keybits_t *ks_word, mask;

	mask = 1;
	mask <<= sym & (KEYBITS_WORD_BITS - 1);
	ks_word = keystate + sym / KEYBITS_WORD_BITS;
	if (is_down)
		*ks_word |= mask;
	else
		*ks_word &= ~mask;
}

static int get_keystate(keybits_t *keystate, int sym)
{
	keybits_t *ks_word, mask;

	mask = 1;
	mask <<= sym & (KEYBITS_WORD_BITS - 1);
	ks_word = keystate + sym / KEYBITS_WORD_BITS;
	return !!(*ks_word & mask);
}

static int handle_event(struct in_sdl_state *state, SDL_Event *event,
	int *kc_out, int *down_out, int *emu_out)
{
	int emu;

	if (event->type != SDL_KEYDOWN && event->type != SDL_KEYUP)
		return -1;

	emu = get_keystate(state->emu_keys, event->key.keysym.sym);
	update_keystate(state->keystate, event->key.keysym.sym,
		event->type == SDL_KEYDOWN);
	if (kc_out != NULL)
		*kc_out = event->key.keysym.sym;
	if (down_out != NULL)
		*down_out = event->type == SDL_KEYDOWN;
	if (emu_out != 0)
		*emu_out = emu;

	return 1;
}

static int handle_joy_event(struct in_sdl_state *state, SDL_Event *event,
	int *kc_out, int *down_out, int *emu_out)
{
	int kc = -1, down = 0, emu = 0, ret = 0;

	/* TODO: remaining axis */
	switch (event->type) {
	case SDL_JOYAXISMOTION:
#ifdef USE_SDL2
		if (in_sdl_debug_input())
			fprintf(stderr, "in_sdl: joy axis which=%d axis=%d value=%d state_id=%d state_index=%d\n",
				event->jaxis.which, event->jaxis.axis, event->jaxis.value,
				state->joy_id, state->joy_index);
		if (event->jaxis.which != state->joy_id &&
		    event->jaxis.which != state->joy_index)
			return -2;
#else
		if (event->jaxis.which != state->joy_id)
			return -2;
#endif
		if (event->jaxis.axis > 1)
			break;
		if (-16384 <= event->jaxis.value && event->jaxis.value <= 16384) {
			kc = state->axis_keydown[event->jaxis.axis];
			state->axis_keydown[event->jaxis.axis] = 0;
			ret = 1;
		}
		else if (event->jaxis.value < -16384) {
			kc = state->axis_keydown[event->jaxis.axis];
			if (kc) {
				emu |= get_keystate(state->emu_keys, kc);
				update_keystate(state->keystate, kc, 0);
			}
			kc = event->jaxis.axis ? SDLK_UP : SDLK_LEFT;
			state->axis_keydown[event->jaxis.axis] = kc;
			down = 1;
			ret = 1;
		}
		else if (event->jaxis.value > 16384) {
			kc = state->axis_keydown[event->jaxis.axis];
			if (kc) {
				emu |= get_keystate(state->emu_keys, kc);
				update_keystate(state->keystate, kc, 0);
			}
			kc = event->jaxis.axis ? SDLK_DOWN : SDLK_RIGHT;
			state->axis_keydown[event->jaxis.axis] = kc;
			down = 1;
			ret = 1;
		}
		break;

	case SDL_JOYBUTTONDOWN:
	case SDL_JOYBUTTONUP:
#ifdef USE_SDL2
		if (in_sdl_debug_input())
			fprintf(stderr, "in_sdl: joy button which=%d button=%d state=%d state_id=%d state_index=%d\n",
				event->jbutton.which, event->jbutton.button, event->jbutton.state,
				state->joy_id, state->joy_index);
		if (event->jbutton.which != state->joy_id &&
		    event->jbutton.which != state->joy_index)
			return -2;
#else
		if (event->jbutton.which != state->joy_id)
			return -2;
#endif
		if (event->jbutton.button >= IN_SDL_JOY_BUTTON_COUNT) {
#ifdef USE_SDL2
			if (in_sdl_debug_input())
				fprintf(stderr, "in_sdl: ignored joystick button %d, max supported=%d\n",
					event->jbutton.button, IN_SDL_JOY_BUTTON_COUNT - 1);
#endif
			break;
		}
		kc = SDL_JOY_BUTTON(event->jbutton.button);
		down = event->jbutton.state == SDL_PRESSED;
		ret = 1;
		break;
	default:
		return -1;
	}

	if (ret) {
		emu |= get_keystate(state->emu_keys, kc);
		update_keystate(state->keystate, kc, down);
	}
	if (kc_out != NULL)
		*kc_out = kc;
	if (down_out != NULL)
		*down_out = down;
	if (emu_out != 0)
		*emu_out = emu;

	return ret;
}

#ifndef JOY_EVENTS
#define JOY_EVENTS (SDL_JOYAXISMOTIONMASK | SDL_JOYBALLMOTIONMASK | SDL_JOYHATMOTIONMASK \
		    | SDL_JOYBUTTONDOWNMASK | SDL_JOYBUTTONUPMASK)
#endif

#ifdef USE_SDL2
static int update_joy_key(struct in_sdl_state *state, int kc, int down,
	int *one_kc, int *one_down)
{
	update_keystate(state->keystate, kc, down);
	if (one_kc != NULL) {
		*one_kc = kc;
		if (one_down != NULL)
			*one_down = down;
		return 1;
	}

	return 0;
}

static int poll_joy_state(struct in_sdl_state *state, int *one_kc, int *one_down)
{
	int i, axes, buttons, ret = 0;

	if (!state->joy)
		return 0;

	SDL_JoystickUpdate();

	axes = SDL_JoystickNumAxes(state->joy);
	if (axes > 2)
		axes = 2;

	for (i = 0; i < axes; i++) {
		int value = SDL_JoystickGetAxis(state->joy, i);
		int dir = 0;
		int kc;

		if (value < -16384)
			dir = -1;
		else if (value > 16384)
			dir = 1;

		if (dir == state->joy_axes[i])
			continue;

		if (state->joy_axes[i] != 0) {
			kc = i ? (state->joy_axes[i] < 0 ? SDLK_UP : SDLK_DOWN)
			       : (state->joy_axes[i] < 0 ? SDLK_LEFT : SDLK_RIGHT);
			if (update_joy_key(state, kc, 0, one_kc, one_down))
				return 1;
			ret = 1;
		}

		state->joy_axes[i] = dir;
		if (dir != 0) {
			kc = i ? (dir < 0 ? SDLK_UP : SDLK_DOWN)
			       : (dir < 0 ? SDLK_LEFT : SDLK_RIGHT);
			if (update_joy_key(state, kc, 1, one_kc, one_down))
				return 1;
			ret = 1;
		}
	}

	buttons = SDL_JoystickNumButtons(state->joy);
	if (buttons > IN_SDL_JOY_BUTTON_COUNT)
		buttons = IN_SDL_JOY_BUTTON_COUNT;

	for (i = 0; i < buttons; i++) {
		uint8_t down = SDL_JoystickGetButton(state->joy, i) ? 1 : 0;
		int kc;

		if (down == state->joy_buttons[i])
			continue;

		state->joy_buttons[i] = down;
		kc = SDL_JOY_BUTTON(i);
		if (in_sdl_debug_input())
			fprintf(stderr, "in_sdl: polled joy button button=%d state=%d\n",
				i, down);
		if (update_joy_key(state, kc, down, one_kc, one_down))
			return 1;
		ret = 1;
	}

	return ret;
}
#endif

static int collect_events(struct in_sdl_state *state, int *one_kc, int *one_down)
{
	SDL_Event events[4];
	Uint32 mask = state->joy ? JOY_EVENTS : (SDL_ALLEVENTS & ~JOY_EVENTS);
	int count, maxcount, is_emukey;
	int i, ret, retval = 0;
	SDL_Event *event;

	maxcount = (one_kc != NULL) ? 1 : sizeof(events) / sizeof(events[0]);

	SDL_PumpEvents();

	for (;;) {
		count = SDL_PeepEvents(events, maxcount, SDL_GETEVENT, mask);
		if (count <= 0)
			break;
		for (i = 0; i < count; i++) {
			event = &events[i];
			if (state->joy) {
				ret = handle_joy_event(state,
					event, one_kc, one_down, &is_emukey);
			} else {
				ret = handle_event(state,
					event, one_kc, one_down, &is_emukey);
			}
			if (ret < 0) {
				switch (ret) {
					case -2:
						SDL_PushEvent(event);
						break;
					default:
						if (ext_event_handler != NULL)
							ext_event_handler(event);
						break;
				}
				continue;
			}

			retval |= ret;
			if ((is_emukey || one_kc != NULL) && ret)
			{
				// don't lose events other devices might want to handle
				if (++i < count)
					SDL_PeepEvents(events+i, count-i, SDL_ADDEVENT, mask);
				goto out;
			}
		}
	}

out:
#ifdef USE_SDL2
	if (state->joy && (retval == 0 || one_kc == NULL))
		retval |= poll_joy_state(state, one_kc, one_down);
#endif
	return retval;
}

static int in_sdl_update(void *drv_data, const int *binds, int *result)
{
	struct in_sdl_state *state = drv_data;
	keybits_t mask;
	int i, sym, bit, b;

	collect_events(state, NULL, NULL);

	for (i = 0; i < IN_SDL_KEY_COUNT / KEYBITS_WORD_BITS + 1; i++) {
		mask = state->keystate[i];
		if (mask == 0)
			continue;
		for (bit = 0; mask != 0; bit++, mask >>= 1) {
			if ((mask & 1) == 0)
				continue;
			sym = i * KEYBITS_WORD_BITS + bit;

			for (b = 0; b < IN_BINDTYPE_COUNT; b++)
				result[b] |= binds[IN_BIND_OFFS(sym, b)];
		}
	}

	return 0;
}

static int in_sdl_update_keycode(void *drv_data, int *is_down)
{
	struct in_sdl_state *state = drv_data;
	int ret_kc = -1, ret_down = 0;

	collect_events(state, &ret_kc, &ret_down);

	if (is_down != NULL)
		*is_down = ret_down;

	return ret_kc;
}

static int in_sdl_menu_translate(void *drv_data, int keycode, char *charcode)
{
	struct in_sdl_state *state = drv_data;
	const struct in_pdata *pdata = state->drv->pdata;
	const char * const * key_names = in_sdl_keys;
	const struct menu_keymap *map;
	int map_len;
	int ret = 0;
	int i;

	if (pdata->key_names)
		key_names = pdata->key_names;

	if (state->joy) {
		map = pdata->joy_map;
		map_len = pdata->jmap_size;
	} else {
		map = pdata->key_map;
		map_len = pdata->kmap_size;
	}

	if (keycode < 0)
	{
		/* menu -> kc */
		keycode = -keycode;
		for (i = 0; i < map_len; i++)
			if (map[i].pbtn == keycode)
				return map[i].key;
	}
	else
	{
		for (i = 0; i < map_len; i++) {
			if (map[i].key == keycode) {
				ret = map[i].pbtn;
				break;
			}
		}

		if (charcode != NULL && (unsigned int)keycode < IN_SDL_KEY_COUNT &&
		    key_names[keycode] != NULL && key_names[keycode][1] == 0)
		{
			ret |= PBTN_CHAR;
			*charcode = key_names[keycode][0];
		}
	}

	return ret;
}

static int in_sdl_clean_binds(void *drv_data, int *binds, int *def_finds)
{
	struct in_sdl_state *state = drv_data;
	int i, t, cnt = 0;

	memset(state->emu_keys, 0, sizeof(state->emu_keys));
	for (t = 0; t < IN_BINDTYPE_COUNT; t++)
		for (i = 0; i < IN_SDL_KEY_COUNT; i++)
			if (binds[IN_BIND_OFFS(i, t)]) {
				if (t == IN_BINDTYPE_EMU)
					update_keystate(state->emu_keys, i, 1);
				cnt ++;
			}

	return cnt;
}

static const in_drv_t in_sdl_drv = {
	.prefix         = IN_SDL_PREFIX,
	.probe          = in_sdl_probe,
	.free           = in_sdl_free,
	.get_key_names  = in_sdl_get_key_names,
	.update         = in_sdl_update,
	.update_keycode = in_sdl_update_keycode,
	.menu_translate = in_sdl_menu_translate,
	.clean_binds    = in_sdl_clean_binds,
};

int in_sdl_init(const struct in_pdata *pdata, void (*handler)(void *event))
{
	if (!pdata) {
		fprintf(stderr, "in_sdl: Missing input platform data\n");
		return -1;
	}

	in_register_driver(&in_sdl_drv, pdata->defbinds, pdata);
	ext_event_handler = handler;
	return 0;
}
