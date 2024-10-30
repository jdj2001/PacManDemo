#ifndef PACMAN_H
#define PACMAN_H

#include <GL/glew.h>
#include <GL/glut.h>

extern float pacmanAncho;
extern const float TUNNEL_LEFT;  // Coordenadas fuera del l�mite izquierdo
extern const float TUNNEL_RIGHT; // Coordenadas fuera del l�mite derecho

void initPacman(float centroX, float centroY, float escalaMapa);

void updatePacman();

void drawPacman(GLuint textureID);

void processPacmanInput(unsigned char key);

#endif 