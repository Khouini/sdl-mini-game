#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

typedef struct {
    SDL_Surface *image;
    SDL_Rect position;
    Mix_Music *musique;
} Background;

void initBack(Background *b);
void afficherBack(Background b, SDL_Surface *screen);
void scrolling(Background *b, int direction, int pas);

#endif
