#ifndef PERSONNE_H
#define PERSONNE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <math.h>

#define SPRITE_WIDTH 130
#define SPRITE_HEIGHT 130
#define SPRITE_COLUMNS 4

typedef struct {
    SDL_Surface *spriteSheet;  // Single sprite sheet
    SDL_Rect position;
    SDL_Rect currentClip;      // Current sprite clip
    int vitesseX, vitesseY;
    int accelX, accelY;
    int direction;
    int score;
    int vies;
    
    // Animation variables
    int currentFrame;
    int frameCounter;
    
    // Jumping-specific attributes
    int isJumping;
    float jumpStartY;
    float jumpTime;
} Personne;

void initPerso(Personne *p);
void afficherPerso(Personne p, SDL_Surface *screen);
void movePerso(Personne *p);
void animerPerso(Personne *p);
void saut(Personne *p, int sinusoidal);
void startJump(Personne *p);

#endif