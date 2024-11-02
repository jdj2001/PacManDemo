#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "Pacman.h"
#include "Mapa.h"
#include "TextureLoader.h"
#include <iostream>
#include "HUD.h"

SoundManager soundManager;

unsigned int pacmanTexture;  
unsigned int mapaTexture;
unsigned int mapaTexturePellets;

float escalaMapa;  // Factor de escala global
float centroX;    
float centroY;   

void initGame() {
    pacmanTexture = loadTexture("C:/sprite_personajes.png");
    mapaTexture = loadTexture("C:/mapa2.png");
    mapaTexturePellets = loadTexture("C:/mapa1.png");
    soundManager.loadSound("smallPellet", "path/to/small_pellet.wav");
    soundManager.loadSound("bigPellet", "path/to/big_pellet.wav");

    initMapa();  
    initPellets();

    float ventanaAncho = 1720.0f;
    float ventanaAlto = 880.0f;
    float escalaX = ventanaAncho / 227.0f;
    float escalaY = ventanaAlto / 248.0f;
    escalaMapa = std::min(escalaX, escalaY);

    centroX = (ventanaAncho - mapaOriginalAncho * escalaMapa) / 2.0f;
    centroY = (ventanaAlto - mapaOriginalAlto * escalaMapa) / 2.0f;

    initPacman(centroX, centroY, escalaMapa);  
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawMapa();  
    drawPellets();
    drawPacman(pacmanTexture);  
    renderizarPuntaje();
    glutSwapBuffers();
}


void updateGame() {
    updatePacman();
    checkPelletCollision();
}

void handleInput(unsigned char key) {
    processPacmanInput(key);
}
