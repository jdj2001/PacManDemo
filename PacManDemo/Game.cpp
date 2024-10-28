#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "Pacman.h"
#include "Mapa.h"
#include "TextureLoader.h"
#include <iostream>

unsigned int pacmanTexture;  
unsigned int mapaTexture;


float escalaMapa;  // Factor de escala global
float centroX;     // Desplazamiento en X para centrar el mapa
float centroY;     // Desplazamiento en Y para centrar el mapa

void initGame() {
    pacmanTexture = loadTexture("C:/sprite_personajes.png");
    mapaTexture = loadTexture("C:/mapa1.png");

    initMapa();  // Inicializar el mapa y sus objetos

    float ventanaAncho = 1720.0f;
    float ventanaAlto = 880.0f;
    float escalaX = ventanaAncho / 227.0f;
    float escalaY = ventanaAlto / 248.0f;
    escalaMapa = std::min(escalaX, escalaY);

    centroX = (ventanaAncho - 227.0f * escalaMapa) / 2.0f;
    centroY = (ventanaAlto - 248.0f * escalaMapa) / 2.0f;

    initPacman(centroX, centroY, escalaMapa);  // Inicializar la posición de Pacman
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawMapa();  // Dibujar el mapa
    drawPacman(pacmanTexture);  // Dibujar a Pacman
    glutSwapBuffers();
}


void updateGame() {
    updatePacman();
}

void handleInput(unsigned char key) {
    processPacmanInput(key);
}
