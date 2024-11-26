#include "personne.h"
#include "background.h"
#include "minimap.h"

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_Surface *screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Mini Jeu", NULL);

    Personne perso;
    Background back;
    MiniMap map;

    initPerso(&perso);
    initBack(&back);
    initMap(&map);

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        movePerso(&perso);
        animerPerso(&perso);
        animerMiniMap(&map);

        afficherBack(back, screen);
        afficherPerso(perso, screen);
        afficherMiniMap(map, screen);

        SDL_Flip(screen);
        SDL_Delay(16);
    }

    SDL_Quit();
    return 0;
}
