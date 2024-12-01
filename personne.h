// Updated personne.h
#ifndef PERSONNE_H
#define PERSONNE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <math.h>

#define SPRITE_WIDTH 130
#define SPRITE_HEIGHT 130
#define SPRITE_COLUMNS 4

typedef enum {
    IDLE,
    MOVING
} AnimationState;

typedef struct {
    SDL_Surface *spriteSheetRight;  // Sprite sheet for right-facing movement
    SDL_Surface *spriteSheetLeft;   // Sprite sheet for left-facing movement
    SDL_Surface *idleSpriteSheetRight;  // New idle sprite sheet for right
    SDL_Surface *idleSpriteSheetLeft;   // New idle sprite sheet for left
    SDL_Rect position;
    SDL_Rect currentClip;      // Current sprite clip
    int vitesseX, vitesseY;
    int accelX, accelY;
    int direction;             // 1 for right, -1 for left
    int score;
    int vies;
    
    // Animation variables
    int currentFrame;
    int frameCounter;
    
    // Jumping-specific attributes
    int isJumping;
    float jumpStartY;
    float jumpTime;

    int isMoving;  // Flag to track movement state
    AnimationState animationState;
} Personne;

void initPerso(Personne *p);
void afficherPerso(Personne p, SDL_Surface *screen);
void movePerso(Personne *p);
void animerPerso(Personne *p);
void saut(Personne *p, int sinusoidal);
void startJump(Personne *p);

#endif