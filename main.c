#include "personne.h"
#include "background.h"
#include "minimap.h"

// Movement constants
#define MOVE_SPEED 2
#define SCROLL_SPEED 1
#define MAX_VELOCITY 6  // Increased to allow for accelerated movement
#define FRICTION 0.6
#define GRAVITY 0.5
#define JUMP_STRENGTH 8
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 600
#define NORMAL_MOVE_SPEED 2
#define ACCELERATED_MOVE_SPEED 5
#define ACCELERATE_KEY SDLK_LSHIFT  // Use 'A' key for acceleration


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

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "SDL_mixer initialization failed: %s\n", Mix_GetError());
        SDL_Quit();
        return 0;
    }

    // Create screen surface
    game->screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, 
                                    SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!game->screen) {
        fprintf(stderr, "Screen creation failed: %s\n", SDL_GetError());
        Mix_CloseAudio();
        SDL_Quit();
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

// In the handleEvents function, modify the left/right key handling:
void handleEvents(GameState *game) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game->running = 0;
        }
        
        // Keyboard input handling
        if (event.type == SDL_KEYDOWN) {
            // Get the current state of all keys
            Uint8 *keystate = SDL_GetKeyState(NULL);
            
            // Determine move speed based on acceleration key
            int moveSpeed = keystate[ACCELERATE_KEY] ? 
                            ACCELERATED_MOVE_SPEED : NORMAL_MOVE_SPEED;

            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    game->perso.accelX = -moveSpeed;
                    game->perso.direction = -1;  // Face left
                    game->perso.isMoving = 1;    // Set moving flag
                    break;
                case SDLK_RIGHT:
                    game->perso.accelX = moveSpeed;
                    game->perso.direction = 1;   // Face right
                    game->perso.isMoving = 1;    // Set moving flag
                    break;
                case SDLK_SPACE:
                    startJump(&game->perso);
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
                    game->perso.isMoving = 0;    // Reset moving flag
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
    
    // Move character (includes jump physics)
    movePerso(&game->perso);
    
    // Ground collision
    if (game->perso.position.y >= game->groundLevel) {
        game->perso.position.y = game->groundLevel;
        game->perso.isJumping = 0;
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
    
    if (game->perso.vitesseX == 0) {
        game->perso.isMoving = 0;
    } else {
        game->perso.isMoving = 1;
    }
    
    // Animation
    animerPerso(&game->perso);
    animerMiniMap(&game->map, &game->perso);
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
    // Stop and free music
    Mix_HaltMusic();
    Mix_FreeMusic(game->back.musique);

    // Close audio
    Mix_CloseAudio();

    // Quit SDL
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