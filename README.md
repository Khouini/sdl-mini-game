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