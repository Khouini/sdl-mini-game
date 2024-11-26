#ifndef PERSONNE_H
#define PERSONNE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <math.h>

typedef struct {
    SDL_Surface *image[4];
    SDL_Rect position;
    int vitesseX, vitesseY;
    int accelX, accelY;
    int direction;
    int score;
    int vies;
} Personne;

void initPerso(Personne *p);
void afficherPerso(Personne p, SDL_Surface *screen);
void movePerso(Personne *p);
void animerPerso(Personne *p);
void saut(Personne *p, int sinusoidal);

#endif