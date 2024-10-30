#ifndef GAME_H
#define GAME_H

extern unsigned int pacmanTexture;  
extern unsigned int mapaTexture;
extern unsigned int mapaTexturePellets;

void handleInput(unsigned char);
void initGame(void);
void renderScene(void);
void updateGame(void);

#endif 
