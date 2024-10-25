#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "Pacman.h"
#include "Mapa.h"
#include "TextureLoader.h"
#include <iostream>

unsigned int pacmanTexture;  
unsigned int mapaTexture;

void initGame() {
    pacmanTexture = loadTexture("C:/sprite_personajes.png");
    mapaTexture = loadTexture("C:/mapa1.png");

    initMapa(); 

    float ventanaAncho = 1720.0f;
    float ventanaAlto = 880.0f;
    float escalaMapa = std::min(ventanaAncho / 227.0f, ventanaAlto / 248.0f);
    float centroX = (ventanaAncho - 227.0f * escalaMapa) / 2.0f;
    float centroY = (ventanaAlto - 248.0f * escalaMapa) / 2.0f;

    initPacman(centroX, centroY, escalaMapa); 
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}


void updateGame() {
    updatePacman();
}

void handleInput(unsigned char key) {
    switch (key) {
    case 'w':
        break;
    case 's':
        break;
    case 'a':
        break;
    case 'd':
        break;
    }
}
