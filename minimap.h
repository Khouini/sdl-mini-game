#ifndef MINIMAP_H
#define MINIMAP_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

typedef struct {
    SDL_Surface *image;
    SDL_Rect position;
    SDL_Rect persoPosition;
} MiniMap;

void initMap(MiniMap *m);
void afficherMiniMap(MiniMap m, SDL_Surface *screen);
void animerMiniMap(MiniMap *m);

#endif
