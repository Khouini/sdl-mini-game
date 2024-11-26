#include "personne.h"
#include "background.h"
#include "minimap.h"

int main(int argc, char *argv[]) {
    // Initialize SDL subsystems
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_Surface *screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Mini Jeu", NULL);

    // Initialize game components
    Personne perso;
    Background back;
    MiniMap map;

    initPerso(&perso);
    initBack(&back);
    initMap(&map);

    int running = 1;
    SDL_Event event;
    
    // Physics and movement variables
    const int GRAVITY = 1;
    const int JUMP_STRENGTH = 15;
    int isJumping = 0;
    int groundLevel = 300; // Adjust based on your background

    while (running) {
        // Event handling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            
            // Keyboard input handling
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        perso.accelX = -5;
                        break;
                    case SDLK_RIGHT:
                        perso.accelX = 5;
                        break;
                    case SDLK_SPACE:
                        if (!isJumping) {
                            perso.vitesseY = -JUMP_STRENGTH;
                            isJumping = 1;
                        }
                        break;
                }
            }
            
            // Stop horizontal movement when key is released
            if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                    case SDLK_RIGHT:
                        perso.accelX = 0;
                        break;
                }
            }
        }
        
        // Apply gravity
        perso.vitesseY += GRAVITY;
        
        // Move character
        movePerso(&perso);
        
        // Ground collision and jumping
        if (perso.position.y >= groundLevel) {
            perso.position.y = groundLevel;
            perso.vitesseY = 0;
            isJumping = 0;
        }
        
        // Smooth horizontal friction
        perso.vitesseX *= 0.8;
        
        // Scroll background based on character movement
        if (perso.vitesseX != 0) {
            scrolling(&back, perso.vitesseX > 0 ? 1 : 0, abs(perso.vitesseX));
        }
        
        // Animation
        animerPerso(&perso);
        animerMiniMap(&map);

        // Render
        afficherBack(back, screen);
        afficherPerso(perso, screen);
        afficherMiniMap(map, screen);

        SDL_Flip(screen);
        SDL_Delay(16); // ~60 FPS
    }

    // Cleanup
    SDL_Quit();
    return 0;
}