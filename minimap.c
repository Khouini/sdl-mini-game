#include "minimap.h"

void initMap(MiniMap *m) {
    m->image = IMG_Load("assets/minimap.jpg");
    if (!m->image) {
        printf("Erreur de chargement de l'image : %s\n", IMG_GetError());
        exit(1);
    }
    m->position.x = 10;
    m->position.y = 10;
    m->persoPosition.x = 10;
    m->persoPosition.y = 10;
}

void afficherMiniMap(MiniMap m, SDL_Surface *screen) {
    SDL_BlitSurface(m.image, NULL, screen, &m.position);
    SDL_Rect persoRect = {m.persoPosition.x, m.persoPosition.y, 5, 5};
    SDL_FillRect(screen, &persoRect, SDL_MapRGB(screen->format, 255, 0, 0));
}

void animerMiniMap(MiniMap *m) {
    m->persoPosition.x += 1;
}
