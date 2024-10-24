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
    drawMapa();  // Dibuja el mapa usando la textura del mapa
    drawPacman(pacmanTexture);  // Dibuja a Pac-Man usando la textura correcta
    glutSwapBuffers();
}


void updateGame() {
    // Aqu� puedes agregar l�gica de movimiento de Pac-Man y otros personajes
    updatePacman();
    // Otras actualizaciones del juego
}

void handleInput(unsigned char key) {
    processPacmanInput(key);  // Actualizar el input del teclado
    // L�gica de entrada del teclado
    switch (key) {
    case 'w':
        // Mover arriba
        break;
    case 's':
        // Mover abajo
        break;
    case 'a':
        // Mover izquierda
        break;
    case 'd':
        // Mover derecha
        break;
    }
}
