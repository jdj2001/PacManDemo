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

void initPacman(float centroX, float centroY, float escalaMapa);

void updatePacman();

void drawPacman(GLuint textureID);

void processPacmanInput(unsigned char key);

#endif 