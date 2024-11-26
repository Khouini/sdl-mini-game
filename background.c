#include "background.h"

void initBack(Background *b) {
    b->image = IMG_Load("assets/background.jpeg");
    if (!b->image) {
        printf("Erreur de chargement de l'image : %s\n", IMG_GetError());
        exit(1);
    }
    b->position.x = 0;
    b->position.y = 0;
    b->position.w = b->image->w;
    b->position.h = b->image->h;
    b->musique = Mix_LoadMUS("assets/background_music.mp3");
    if (!b->musique) {
        printf("Erreur de chargement de la musique : %s\n", Mix_GetError());
        exit(1);
    }
    Mix_PlayMusic(b->musique, -1);
}

void afficherBack(Background b, SDL_Surface *screen) {
    SDL_BlitSurface(b.image, &b.position, screen, NULL);
}

void scrolling(Background *b, int direction, int pas) {
    switch (direction) {
        case 0: b->position.x -= pas; break; // Gauche
        case 1: b->position.x += pas; break; // Droite
        case 2: b->position.y -= pas; break; // Haut
        case 3: b->position.y += pas; break; // Bas
    }
}
