# 2D Platform Game 

## Prerequisites

### System Requirements
- Linux Operating System (Ubuntu/Debian recommended)
- GCC Compiler
- SDL Libraries

### Install Dependencies
```bash
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev libpulse-dev libxt-dev
```

## Compilation
```bash
gcc -o jeu main.c personne.c background.c minimap.c -lSDL -lSDL_image -lSDL_mixer -lm
```

## Running the Game
```bash
./jeu
```

## Game Controls
- **Left Arrow**: Move Left
- **Right Arrow**: Move Right
- **Space**: Jump
- **A Key**: Accelerate Movement
- **ESC**: Exit Game

## Project Structure
- `main.c`: Game main loop and core logic
- `personne.c`: Character management and physics
- `background.c`: Background and scrolling mechanics
- `minimap.c`: Minimap rendering
- `assets/`: Directory for game resources


## Asset Requirements
Prepare the following assets in the `assets/` directory:
- `background.jpeg`: Background image
- `background_music.mp3`: Background music
- `perso1.png`, `perso2.png`, `perso3.png`, `perso4.png`: Character animation frames
- `minimap.jpg`: Minimap background

## Development Notes
- Game runs at approximately 60 FPS
- Uses SDL 1.2 library
- Simple 2D platformer mechanics
# Comprendre la Boucle de Jeu

## Qu'est-ce qu'une Boucle de Jeu ?

La boucle de jeu est le cœur battant de tout jeu vidéo. C'est un cycle continu qui tourne environ 60 fois par seconde pour créer l'expérience interactive d'un jeu. Imaginez-la comme une liste de tâches sans fin que le jeu parcourt à chaque instant :

1. **Écouter les Entrées du Joueur**
2. **Mettre à Jour la Logique du Jeu**
3. **Afficher (Dessiner) l'Écran**

## Décomposition Détaillée de Notre Boucle de Jeu

```c
while (game.running) {
    // 1. Gérer les Événements (Écouter le Joueur)
    handleEvents(&game);

    // 2. Mettre à Jour la Logique du Jeu (Calculer les Changements)
    updateGameLogic(&game);

    // 3. Affichage (Dessiner Tout)
    render(&game);

    // 4. Contrôler la Vitesse du Jeu
    SDL_Delay(16);
}
```

### 1. Gestion des Événements (`handleEvents()`)
- Vérifie ce que le joueur fait
- Capture les entrées du clavier
- Décide des actions comme :
  - Se déplacer à gauche/droite
  - Sauter
  - Quitter le jeu

### 2. Mise à Jour de la Logique du Jeu (`updateGameLogic()`)
- Calcule les nouvelles positions
- Applique la physique (gravité, mouvement)
- Met à jour les animations du personnage
- Gère les changements d'état du jeu

### 3. Affichage (`render()`)
- Dessine tout à l'écran
- Met à jour l'arrière-plan
- Place le personnage
- Actualise la mini-carte
- Montre l'état actuel du jeu

### 4. Contrôle de Vitesse (`SDL_Delay(16)`)
- Assure que le jeu tourne à une vitesse constante
- Limite à environ 60 images par seconde
- Empêche le jeu de tourner trop vite

## Pourquoi C'est Important

Imaginez la boucle de jeu comme un cycle très rapide :
- Écouter → Calculer → Dessiner
- Écouter → Calculer → Dessiner
- Écouter → Calculer → Dessiner

Ceci se produit 60 fois par seconde, créant l'illusion d'un mouvement fluide et interactif !

## Concepts Clés

- **Cycle Continu** : La boucle ne s'arrête jamais pendant que le jeu tourne
- **Mises à Jour en Temps Réel** : Réponse constante aux entrées du joueur
- **Animation Fluide** : Des mises à jour rapides créent un mouvement doux

### Conseil de Performance
- Chaque étape doit être rapide
- Évitez les calculs complexes dans la boucle de jeu
- Gardez le jeu réactif et fluide
Je vais expliquer le fichier `personne.c` de manière détaillée et accessible :

# Explication du Fichier `personne.c`

## Vue d'Ensemble
Ce fichier gère toute la logique liée au personnage dans un jeu de plateforme 2D. Il contrôle :
- L'initialisation du personnage
- Les animations 
- Les mouvements
- Les sauts

## Fonctions Principales

### 1. `initPerso(Personne *p)`
🎬 **Initialisation du Personnage**
- Charge les images (sprites) du personnage
- Position initiale à l'écran (x=100, y=300)
- Initialise tous les attributs :
  - Vitesse à zéro
  - Direction vers la droite
  - État immobile
  - Vie et score
  - Préparation pour les animations et sauts

### 2. `afficherPerso(Personne p, SDL_Surface *screen)`
🖼️ **Affichage du Personnage**
- Choisit le bon sprite selon :
  - Direction (gauche/droite)
  - État (en mouvement/immobile)
- Dessine le personnage à l'écran

### 3. `animerPerso(Personne *p)`
🏃 **Gestion des Animations**
- Change l'image du personnage 
- Crée l'illusion de mouvement
- Différentes animations pour :
  - État immobile
  - Déplacement
- Change l'image toutes les 10 frames quand le personnage bouge

### 4. `movePerso(Personne *p)`
↔️ **Déplacement du Personnage**
- Met à jour la position 
- Gère la physique des sauts
- Calcule la trajectoire du saut
- Vérifie la durée du saut

### 5. `saut(Personne *p, int sinusoidal)`
🦘 **Système de Saut**
- Deux types de sauts :
  1. Parabolique (plus naturel)
  2. Vertical simple
- Calcule la trajectoire du saut
- Crée un mouvement plus réaliste

### 6. `startJump(Personne *p)`
🚀 **Déclenchement du Saut**
- Vérifie si le personnage peut sauter
- Initialise les paramètres du saut
- Donne une vitesse initiale vers le haut

## Concepts Clés

### Sprites et Animations
- Utilise plusieurs images pour simuler le mouvement
- Change d'image rapidement pour créer l'animation

### Physique de Saut
- Calcul mathématique pour un saut naturel
- Gestion de la hauteur et de la durée du saut

### États du Personnage
- Immobile ou en mouvement
- Direction gauche/droite
- En train de sauter ou non

## Constantes Importantes
```c
#define JUMP_HEIGHT 100     // Hauteur maximale du saut
#define JUMP_DURATION 0.5   // Durée du saut
#define GRAVITY 9.8         // Gravité standard
```

## Points Techniques
- Utilisation de pointeurs pour modifier directement l'objet
- Gestion précise des états et des transitions
- Calculs mathématiques pour les mouvements

# Documentation du Module d'Arrière-plan

## Aperçu
Ce module fournit des fonctionnalités pour gérer les images d'arrière-plan et la musique dans une application SDL, avec un support pour le défilement de l'arrière-plan.


## Structures
### `Background`
Une structure qui encapsule les éléments liés à l'arrière-plan :
- `SDL_Surface *image` : Stocke l'image d'arrière-plan
- `SDL_Rect position` : Définit la position et les dimensions de l'arrière-plan
- `Mix_Music *musique` : Gère la musique d'arrière-plan

## Fonctions

### `initBack(Background *b)`
Initialise l'arrière-plan en effectuant les étapes suivantes :
- Charge une image d'arrière-plan depuis "assets/background.jpeg"
- Définit la position initiale à (0,0)
- Définit la largeur et la hauteur pour correspondre aux dimensions de l'image
- Charge la musique d'arrière-plan depuis "assets/background_music.mp3"
- Lance la lecture de la musique en boucle infinie

#### Gestion des Erreurs
- Quitte le programme si le chargement de l'image ou de la musique échoue
- Affiche des messages d'erreur en utilisant `IMG_GetError()` ou `Mix_GetError()`

### `afficherBack(Background b, SDL_Surface *screen)`
Affiche l'arrière-plan sur l'écran en utilisant `SDL_BlitSurface()`

### `scrolling(Background *b, int direction, int pas)`
Déplace l'arrière-plan en fonction de la direction spécifiée :
- `0` : Déplacer vers la Gauche
- `1` : Déplacer vers la Droite
- `2` : Déplacer vers le Haut
- `3` : Déplacer vers le Bas

#### Paramètres
- `direction` : Direction du défilement (0-3)
- `pas` : Nombre de pixels à déplacer

## Exemple d'Utilisation
```c
Background background;
initBack(&background);
afficherBack(background, screen);
scrolling(&background, 0, 5); // Défilement vers la gauche de 5 pixels
```

# Documentation du Module de Mini-carte

## Aperçu
Ce module gère la création et l'affichage d'une mini-carte dans une application SDL, permettant de suivre la position du personnage sur une carte réduite.

## Dépendances
- SDL2
- SDL2_image

## Structures
### `MiniMap`
Une structure qui contient les informations de la mini-carte :
- `SDL_Surface *image` : Image de la mini-carte
- `SDL_Rect position` : Position de la mini-carte sur l'écran
- `SDL_Point persoPosition` : Position du personnage sur la mini-carte

## Fonctions

### `initMap(MiniMap *m)`
Initialise la mini-carte :
- Charge l'image de la mini-carte depuis "assets/minimap.jpg"
- Définit la position initiale de la mini-carte à (10, 10)
- Configure la position initiale du personnage à (10, 10)

#### Gestion des Erreurs
- Quitte le programme si le chargement de l'image échoue
- Affiche un message d'erreur en utilisant `IMG_GetError()`

### `afficherMiniMap(MiniMap m, SDL_Surface *screen)`
Affiche la mini-carte sur l'écran :
- Utilise `SDL_BlitSurface()` pour dessiner l'image de la mini-carte
- Dessine un rectangle rouge représentant la position du personnage

### `animerMiniMap(MiniMap *m, Personne *perso)`
Met à jour la position du personnage sur la mini-carte :
- Utilise des facteurs de mise à l'échelle pour adapter la position du personnage
- Calcule la nouvelle position sur la mini-carte en fonction de la position réelle du personnage

## Exemple d'Utilisation
```c
MiniMap minimap;
Personne personnage;

initMap(&minimap);
// Après avoir mis à jour la position du personnage
animerMiniMap(&minimap, &personnage);
afficherMiniMap(minimap, screen);
```