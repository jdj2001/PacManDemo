#ifndef MAPA_H
#define MAPA_H

#include <GL/glew.h>
#include <GL/glut.h>
#include "Pacman.h"
#include <vector>

void initMapa();   
void initPellets();
void drawMapa();   
void drawPellets();
//bool checkCollisionPellet(float nextX, float nextY, float pacmanAncho, float pacmanAlto);
bool checkCollision(float nextX, float nextY, float pacmanAncho, float pacmanAlto);  // Funci�n para detectar colisiones
//void calcularPasillos();

extern float escalaMapa;  // Factor de escala global
extern float centroX;     // Desplazamiento del mapa en X
extern float centroY;     // Desplazamiento del mapa en Y
extern float mapaOriginalAlto;
extern float mapaOriginalAncho;

#endif 
