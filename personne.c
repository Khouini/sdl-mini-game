#include "personne.h"

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
}

void afficherPerso(Personne p, SDL_Surface *screen) {
    SDL_BlitSurface(p.image[p.direction], NULL, screen, &p.position);
}

void movePerso(Personne *p) {
    p->vitesseX += p->accelX;
    p->vitesseY += p->accelY;
    p->position.x += p->vitesseX;
    p->position.y += p->vitesseY;
}

void animerPerso(Personne *p) {
    static int frame = 0;
    frame = (frame + 1) % 4;
    p->direction = frame;
}

void saut(Personne *p, int sinusoidal) {
    if (sinusoidal) {
        p->position.y -= 10 * sin(p->position.x / 10.0);
    } else {
        p->position.y -= 20;
    }
}
