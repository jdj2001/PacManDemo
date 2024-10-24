#include <GL/glew.h>
#include <GL/glut.h>
#include "Mapa.h"
#include "Game.h"
#include "stb_image.h"
#include "TextureLoader.h"
#include <iostream>

float mapaX = 0.0f;
float mapaY = 0.0f;

void initMapa() {
    mapaX = 0.0f;
    mapaY = 0.0f;
}

void drawMapa() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mapaTexture);

    float mapaOriginalAncho = 227.0f;
    float mapaOriginalAlto = 248.0f;

    float ventanaAncho = 1720.0f;
    float ventanaAlto = 880.0f;

    float escalaX = ventanaAncho / mapaOriginalAncho;
    float escalaY = ventanaAlto / mapaOriginalAlto;

    float escalaMapa = std::min(escalaX, escalaY);

    float mapaAncho = mapaOriginalAncho * escalaMapa;
    float mapaAlto = mapaOriginalAlto * escalaMapa;

    float centroX = (ventanaAncho - mapaAncho) / 2.0f; 
    float centroY = (ventanaAlto - mapaAlto) / 2.0f;    

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(centroX, centroY);  
    glTexCoord2f(1.0f, 0.0f); glVertex2f(centroX + mapaAncho, centroY);  
    glTexCoord2f(1.0f, 1.0f); glVertex2f(centroX + mapaAncho, centroY + mapaAlto); 
    glTexCoord2f(0.0f, 1.0f); glVertex2f(centroX, centroY + mapaAlto); 
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

