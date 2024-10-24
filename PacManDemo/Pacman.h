#ifndef PACMAN_H
#define PACMAN_H

#include <GL/glew.h>
#include <GL/glut.h>

void initPacman(float centroX, float centroY, float escalaMapa);

void updatePacman();

void drawPacman(GLuint textureID);

void processPacmanInput(unsigned char key);

#endif 