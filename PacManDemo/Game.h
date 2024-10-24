#ifndef GAME_H
#define GAME_H

extern unsigned int pacmanTexture;  
extern unsigned int mapaTexture;

void handleInput(unsigned char);
void initGame(void);
void renderScene(void);
void updateGame(void);

#endif 
