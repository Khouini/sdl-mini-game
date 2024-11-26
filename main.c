#include "personne.h"
#include "background.h"
#include "minimap.h"

// Movement constants
#define MOVE_SPEED 2
#define SCROLL_SPEED 1
#define MAX_VELOCITY 3
#define FRICTION 0.6
#define GRAVITY 0.5
#define JUMP_STRENGTH 8
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 600

// Game state structure
typedef struct {
    Personne perso;
    Background back;
    MiniMap map;
    SDL_Surface *screen;
    int running;
    int isJumping;
    int groundLevel;
} GameState;

// Function prototypes
int initSDL(GameState *game);
void handleEvents(GameState *game);
void updateGameLogic(GameState *game);
void render(GameState *game);
void cleanupSDL(GameState *game);

int initSDL(GameState *game) {
    // Initialize SDL subsystems
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return 0;
    }

    // Create screen surface
    game->screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, 
                                    SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!game->screen) {
        fprintf(stderr, "Screen creation failed: %s\n", SDL_GetError());
        return 0;
    }

    SDL_WM_SetCaption("Mini Jeu", NULL);

    // Initialize game components
    initPerso(&game->perso);
    initBack(&game->back);
    initMap(&game->map);

    // Set initial game state
    game->running = 1;
    game->isJumping = 0;
    game->groundLevel = 300;

    return 1;
}

void handleEvents(GameState *game) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game->running = 0;
        }
        
        // Keyboard input handling
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    game->perso.accelX = -MOVE_SPEED;
                    break;
                case SDLK_RIGHT:
                    game->perso.accelX = MOVE_SPEED;
                    break;
                case SDLK_SPACE:
                    if (!game->isJumping) {
                        game->perso.vitesseY = -JUMP_STRENGTH;
                        game->isJumping = 1;
                    }
                    break;
                case SDLK_ESCAPE:
                    game->running = 0;
                    break;
            }
        }
        
        // Stop horizontal movement when key is released
        if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                case SDLK_RIGHT:
                    game->perso.accelX = 0;
                    break;
            }
        }
    }
}

void updateGameLogic(GameState *game) {
    // Apply horizontal acceleration with max velocity
    game->perso.vitesseX += game->perso.accelX;
    
    // Clamp horizontal velocity
    if (game->perso.vitesseX > MAX_VELOCITY) 
        game->perso.vitesseX = MAX_VELOCITY;
    if (game->perso.vitesseX < -MAX_VELOCITY) 
        game->perso.vitesseX = -MAX_VELOCITY;
    
    // Apply friction
    game->perso.vitesseX *= FRICTION;
    
    // Apply gravity
    game->perso.vitesseY += GRAVITY;
    
    // Move character
    movePerso(&game->perso);
    
    // Ground collision and jumping
    if (game->perso.position.y >= game->groundLevel) {
        game->perso.position.y = game->groundLevel;
        game->perso.vitesseY = 0;
        game->isJumping = 0;
    }
    
    // Controlled background scrolling
    if (game->perso.vitesseX != 0) {
        int scrollAmount = 0;
        
        // Determine scroll direction and amount
        if (game->perso.vitesseX > 0) {
            scrollAmount = SCROLL_SPEED;
        } else if (game->perso.vitesseX < 0) {
            scrollAmount = -SCROLL_SPEED;
        }
        
        // Scroll background
        scrolling(&game->back, scrollAmount > 0 ? 1 : 0, SCROLL_SPEED);
    }
    
    // Animation
    animerPerso(&game->perso);
    animerMiniMap(&game->map);
}

void render(GameState *game) {
    // Clear screen
    afficherBack(game->back, game->screen);
    afficherPerso(game->perso, game->screen);
    afficherMiniMap(game->map, game->screen);

    // Update display
    SDL_Flip(game->screen);
}

void cleanupSDL(GameState *game) {
    // Free surfaces and resources
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    GameState game;

    // Initialize game
    if (!initSDL(&game)) {
        return 1;
    }

    // Game loop
    while (game.running) {
        // Handle events
        handleEvents(&game);

        // Update game logic
        updateGameLogic(&game);

        // Render
        render(&game);

        // Cap to ~60 FPS
        SDL_Delay(16);
    }

    // Cleanup
    cleanupSDL(&game);

    return 0;
}