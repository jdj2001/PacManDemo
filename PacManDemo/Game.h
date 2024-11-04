#include <SDL.h>
#include <SDL_mixer.h>
#ifndef GAME_H
#define GAME_H

extern unsigned int pacmanTexture;
extern unsigned int mapaTexture;
extern unsigned int mapaTexturePellets;
extern bool showEndLevelDialog;  
extern Mix_Chunk* eatDotSound;
extern bool isGamePaused;
extern bool isLevelStarting;

void resetGame();  
void goToMainMenu();  


void handleInput(unsigned char);
void initGame(void);
void renderScene(void);
void updateGame(void);
void mostrarVentanaFinDeNivel();
void mouseCallback(int button, int state, int x, int y);
void cleanupGame();

#endif 