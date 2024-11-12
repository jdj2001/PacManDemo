#ifndef PACMAN_H
#define PACMAN_H

#include <GL/glew.h>
#include <GL/glut.h>

extern float pacmanAlto;
extern float pacmanAncho;
extern float pacmanX;
extern float pacmanY;
extern const float TUNNEL_LEFT;  
extern const float TUNNEL_RIGHT; 
extern bool isDying;

extern int vidas; 

void renderizarVidas();
void initPacman(float centroX, float centroY, float escalaMapa, bool inicializarVidas);

void updatePacman();

void drawPacman(GLuint textureID);
void drawDeathAnim(GLuint textureID);

void loseLife();

void processPacmanInput(unsigned char key);

#endif 