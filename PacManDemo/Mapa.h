#ifndef MAPA_H
#define MAPA_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>

void initMapa();   
void drawMapa();   
bool checkCollision(float nextX, float nextY, float pacmanAncho, float pacmanAlto);  // Función para detectar colisiones
void calcularPasillos();

extern float escalaMapa;  // Factor de escala global
extern float centroX;     // Desplazamiento del mapa en X
extern float centroY;     // Desplazamiento del mapa en Y

#endif 
