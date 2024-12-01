#include "personne.h"
#include <math.h>

// Jumping constants
#define JUMP_HEIGHT 100  // Maximum jump height
#define JUMP_DURATION 0.5  // Jump duration in seconds
#define GRAVITY 9.8  // Standard gravity
#define SPRITE_WIDTH 130
#define SPRITE_HEIGHT 130
#define SPRITE_COLUMNS 4
#define IDLE_SPRITE_COLUMNS 1  // Changed to 1 frame for idle state

void initPerso(Personne *p) {
    // Load sprite sheets
    p->spriteSheetRight = IMG_Load("assets/spritesheet.png");
    p->spriteSheetLeft = IMG_Load("assets/spritesheet_flip.png");
    p->idleSpriteSheetRight = IMG_Load("assets/idle_spritesheet.png");
    p->idleSpriteSheetLeft = IMG_Load("assets/idle_spritesheet_flip.png");
    
    if (!p->spriteSheetRight || !p->spriteSheetLeft || 
        !p->idleSpriteSheetRight || !p->idleSpriteSheetLeft) {
        printf("Failed to load character sprite sheets: %s\n", IMG_GetError());
        exit(1);
    }

    // Initial position
    p->position.x = 100;
    p->position.y = 300;
    p->position.w = SPRITE_WIDTH;
    p->position.h = SPRITE_HEIGHT;

    // Set up initial sprite clip (first frame of first row)
    p->currentClip.x = 0;
    p->currentClip.y = 0;
    p->currentClip.w = SPRITE_WIDTH;
    p->currentClip.h = SPRITE_HEIGHT;

    // Initialize other attributes
    p->vitesseX = 0;
    p->vitesseY = 0;
    p->accelX = 0;
    p->accelY = 0;
    p->direction = 1;  // Start facing right
    p->score = 0;
    p->vies = 3;
    
    // Animation initialization
    p->currentFrame = 0;
    p->frameCounter = 0;
    p->isMoving = 0;  // Start in idle state
    
    // Jump initialization
    p->isJumping = 0;
    p->jumpStartY = p->position.y;
    p->jumpTime = 0;
}

void afficherPerso(Personne p, SDL_Surface *screen) {
    SDL_Surface *currentSpriteSheet;
    int currentColumns;
    
    // Select sprite sheet based on movement and direction
    if (p.isMoving) {
        // Moving sprite sheet
        currentSpriteSheet = (p.direction > 0) ? 
            p.spriteSheetRight : p.spriteSheetLeft;
        currentColumns = SPRITE_COLUMNS;
    } else {
        // Idle sprite sheet
        currentSpriteSheet = (p.direction > 0) ? 
            p.idleSpriteSheetRight : p.idleSpriteSheetLeft;
        currentColumns = IDLE_SPRITE_COLUMNS;
    }
    
    SDL_BlitSurface(currentSpriteSheet, &p.currentClip, screen, &p.position);
}

void animerPerso(Personne *p) {
    // Increment frame counter
    p->frameCounter++;

    // Determine frame change interval based on movement state
    int frameInterval = p->isMoving ? 10 : 0;  // No animation for idle state
    int maxColumns = p->isMoving ? SPRITE_COLUMNS : IDLE_SPRITE_COLUMNS;

    // Change sprite every set number of frames
    if (p->frameCounter >= frameInterval) {
        // Reset counter
        p->frameCounter = 0;

        // Move to next frame
        p->currentFrame = (p->currentFrame + 1) % maxColumns;

        // Update clip rectangle
        p->currentClip.x = p->currentFrame * SPRITE_WIDTH;
        p->currentClip.y = 0;  // Assuming first row of sprite sheet
        p->currentClip.w = SPRITE_WIDTH;
        p->currentClip.h = SPRITE_HEIGHT;
    }
}

void movePerso(Personne *p) {
    // Update position based on velocity
    p->position.x += p->vitesseX;
    p->position.y += p->vitesseY;
    
    // Handle jumping physics
    if (p->isJumping) {
        // Parabolic jump trajectory
        p->jumpTime += 0.016;  // Assuming ~60 FPS
        
        // Use sinusoidal jump for more natural movement
        saut(p, 1);
        
        // Check if jump is complete
        if (p->jumpTime >= JUMP_DURATION) {
            p->isJumping = 0;
            p->jumpTime = 0;
            p->position.y = p->jumpStartY;
            p->vitesseY = 0;
        }
    }
}

void saut(Personne *p, int sinusoidal) {
    if (sinusoidal) {
        // Sinusoidal jump for more natural arc
        float t = p->jumpTime;
        float jumpHeight = JUMP_HEIGHT;
        
        // Parabolic jump calculation
        p->position.y = p->jumpStartY - 
            (jumpHeight * 4 * t * (JUMP_DURATION - t)) / 
            (JUMP_DURATION * JUMP_DURATION);
    } else {
        // Simple vertical jump
        p->position.y -= 20;
    }
}

void startJump(Personne *p) {
    // Only allow jump if not already jumping
    if (!p->isJumping) {
        p->isJumping = 1;
        p->jumpStartY = p->position.y;
        p->jumpTime = 0;
        p->vitesseY = -10;  // Initial upward velocity
    }
}