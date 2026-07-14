#ifndef LIBPICOFE_IN_SDL_H
#define LIBPICOFE_IN_SDL_H

#ifndef IN_SDL_JOY_BUTTON_COUNT
#define IN_SDL_JOY_BUTTON_COUNT 32
#endif

#define SDL_JOY_BUTTON(button) (SDLK_LAST + (button))
#define IN_SDL_KEY_COUNT SDL_JOY_BUTTON(IN_SDL_JOY_BUTTON_COUNT)

int in_sdl_init(const struct in_pdata *pdata, void (*handler)(void *event));

#endif
