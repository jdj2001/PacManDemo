#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
#include "Fantasma.h"
#ifndef GAME_H
#define GAME_H

extern unsigned int pacmanTexture;
extern unsigned int fantasmasTexture;
extern unsigned int fantasmasVulnerablesTexture;
extern unsigned int mapaTexture;
extern unsigned int mapaTexturePellets;
extern bool showEndLevelDialog; 
extern bool showGameOverDialog;
extern Mix_Chunk* eatDotSound;
extern Mix_Chunk* muertePacman;
extern bool isGamePaused;
extern bool isLevelStarting;
extern Mix_Music* intermissionMusic;
//extern Mix_Chunk* movimientoFatasmas;
extern Uint32 levelStartTime;
extern bool isMusicPlaying;

void resetGame();  
void goToMainMenu();  
void reiniciarPosiciones();

void handleInput(unsigned char);
void initGame(void);
void renderScene(void);
void updateGame(void);
void mostrarVentanaFinDeNivel();
void mostrarVentanaDerrota();
void mouseCallback(int button, int state, int x, int y);
void cleanupGame();

extern std::vector<Fantasma> fantasmas;

#endif 