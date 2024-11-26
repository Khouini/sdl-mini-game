#include "personne.h"
#include <math.h>

// Jumping constants
#define JUMP_HEIGHT 100  // Maximum jump height
#define JUMP_DURATION 0.5  // Jump duration in seconds
#define GRAVITY 9.8  // Standard gravity

void initPerso(Personne *p) {
    p->image[0] = IMG_Load("assets/perso1.png");
    p->image[1] = IMG_Load("assets/perso2.png");
    p->image[2] = IMG_Load("assets/perso3.png");
    p->image[3] = IMG_Load("assets/perso4.png");
    p->position.x = 100;
    p->position.y = 300;
    p->vitesseX = 0;
    p->vitesseY = 0;
    p->accelX = 0;
    p->accelY = 0;
    p->direction = 1;
    p->score = 0;
    p->vies = 3;
    
    // Initialize jump-specific attributes
    p->isJumping = 0;
    p->jumpStartY = p->position.y;
    p->jumpTime = 0;
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

void afficherPerso(Personne p, SDL_Surface *screen) {
    SDL_BlitSurface(p.image[p.direction], NULL, screen, &p.position);
}

void animerPerso(Personne *p) {
    static int frame = 0;
    frame = (frame + 1) % 4;
    p->direction = frame;
}