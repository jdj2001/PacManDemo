#include <GL/glew.h>
#include <GL/glut.h>
#include "Mapa.h"
#include "Game.h"
#include "Pacman.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include "stb_image.h"
#include "TextureLoader.h"
#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "Menu.h"

int puntaje = 0; 

float mapaX = 0.0f;
float mapaY = 0.0f;

float pelletPequeX = 0.0f;
float pelletPequeY = 0.0f;

float pelletGrandeX = 0.0f;
float pelletGrandeY = 0.0f;

struct Objeto {
    float x, y, ancho, alto;
};

struct Pasillo {
    float x, y, ancho, alto;
};

struct Pellet {
    float x, y;
    bool isBig;
    bool isEaten = false;
};

std::vector<Pellet> pellets;
std::vector<Objeto> objetos;
std::vector<Pasillo> pasillos;

extern unsigned int mapaTexturePellets; 
extern float escalaMapa;
extern float centroX;
extern float centroY;
extern float pacmanX, pacmanY, pacmanAncho, pacmanAlto;

float mapaOriginalAlto = 248.0f;
float mapaOriginalAncho = 227.0f;

void initMapa() {
    //objetos.push_back({ 11, mapaOriginalAlto - (19 + 2), 2, 2 });
    // Segmento superior
    objetos.push_back({ 0, mapaOriginalAlto - (0 + 5), 224, 5 });
    objetos.push_back({ 107, mapaOriginalAlto - (4 + 33), 10, 33 });
    objetos.push_back({ 19, mapaOriginalAlto - (19 + 18), 26, 18 });
    objetos.push_back({ 19, mapaOriginalAlto - (51 + 10), 26, 10 });
    objetos.push_back({ 59, mapaOriginalAlto - (19 + 18), 34, 18 });
    objetos.push_back({ 59, mapaOriginalAlto - (51 + 58), 10, 58 });
    objetos.push_back({ 68, mapaOriginalAlto - (75 + 10), 25, 10 });
    objetos.push_back({ 83, mapaOriginalAlto - (51 + 10), 58, 10 });
    objetos.push_back({ 107, mapaOriginalAlto - (60 + 25), 10, 25 });
    objetos.push_back({ 131, mapaOriginalAlto - (19 + 18), 34, 18 });
    objetos.push_back({ 179, mapaOriginalAlto - (19 + 18), 26, 18 });
    objetos.push_back({ 179, mapaOriginalAlto - (51 + 10), 26, 10 });
    objetos.push_back({ 155, mapaOriginalAlto - (51 + 58), 10, 58 });
    objetos.push_back({ 131, mapaOriginalAlto - (75 + 10), 25, 10 });

    //({ 0, mapaOriginalAlto - (109 + 14), 1, 14 });
    //({ 223, mapaOriginalAlto - (109 + 14), 1, 14 });

    // Paredes laterales
    objetos.push_back({ 0, mapaOriginalAlto - (0 + 76), 5, 76 });
    objetos.push_back({ 219, mapaOriginalAlto - (0 + 80), 5, 80 });

    // Obstáculos inferiores (izquierda y derecha)
    objetos.push_back({ 0, mapaOriginalAlto - (75 + 34), 45, 34 });//OBJETO SUPERIOR (TUNEL IZQUIERDO)
    objetos.push_back({ 179, mapaOriginalAlto - (75 + 34), 45, 34 });//OBJETO SUPERIOR (TUNEL DERECHO)

    // Segmento medio (jaula de los fantasmas)
    objetos.push_back({ 83, mapaOriginalAlto - (99 + 1), 58, 1 }); //-  
    objetos.push_back({ 83, mapaOriginalAlto - (99 + 34), 1, 34 }); //*  
    objetos.push_back({ 83, mapaOriginalAlto - (132 + 1), 58, 1 });
    objetos.push_back({ 140, mapaOriginalAlto - (99 + 34), 1, 34 }); //*
    objetos.push_back({ 88, mapaOriginalAlto - (104 + 24), 1, 24 });
    objetos.push_back({ 88, mapaOriginalAlto - (104 + 1), 48, 1 });
    objetos.push_back({ 88, mapaOriginalAlto - (127 + 1), 48, 1 });
    objetos.push_back({ 135, mapaOriginalAlto - (104 + 24), 1, 24 }); // Pared derecha interior
    objetos.push_back({ 104, mapaOriginalAlto - (99 + 6), 16, 6 });   // Parte por donde saldrán los fantasmas
    objetos.push_back({ 89, mapaOriginalAlto - (105 + 22), 46, 22 }); // Área donde estarán los fantasmas

    // Segmento inferior
    objetos.push_back({ 0, mapaOriginalAlto - (243 + 5), 224, 5 });   // Pared inferior
    objetos.push_back({ 59, mapaOriginalAlto - (123 + 34), 10, 34 });
    objetos.push_back({ 19, mapaOriginalAlto - (171 + 10), 26, 10 });
    objetos.push_back({ 35, mapaOriginalAlto - (181 + 24), 10, 24 });
    objetos.push_back({ 19, mapaOriginalAlto - (219 + 10), 74, 10 });
    objetos.push_back({ 59, mapaOriginalAlto - (195 + 25), 10, 25 });
    objetos.push_back({ 59, mapaOriginalAlto - (171 + 10), 34, 10 });
    objetos.push_back({ 83, mapaOriginalAlto - (147 + 10), 58, 10 });
    objetos.push_back({ 107, mapaOriginalAlto - (156 + 25), 10, 25 });
    objetos.push_back({ 83, mapaOriginalAlto - (195 + 10), 58, 10 });
    objetos.push_back({ 107, mapaOriginalAlto - (204 + 25), 10, 25 });
    objetos.push_back({ 131, mapaOriginalAlto - (171 + 10), 34, 10 });
    objetos.push_back({ 155, mapaOriginalAlto - (123 + 34), 10, 34 }); //AQUÍ EN X +1, EN ANCHO -1
    objetos.push_back({ 155, mapaOriginalAlto - (195 + 25), 10, 25 });
    objetos.push_back({ 131, mapaOriginalAlto - (219 + 10), 74, 10 });
    objetos.push_back({ 179, mapaOriginalAlto - (171 + 10), 26, 10 });
    objetos.push_back({ 179, mapaOriginalAlto - (181 + 24), 10, 24 });
    objetos.push_back({ 179, mapaOriginalAlto - (123 + 34), 45, 34 });//OBJETO INFERIOR (TUNEL DERECHO)

    // Paredes laterales inferiores
    objetos.push_back({ 0, mapaOriginalAlto - (156 + 92), 5, 92 });   // Pared izquierda inferior
    objetos.push_back({ 219, mapaOriginalAlto - (156 + 92), 5, 92 }); // Pared derecha inferior

    // Obstáculos adicionales
    objetos.push_back({ 4, mapaOriginalAlto - (195 + 10), 17, 10 });
    objetos.push_back({ 0, mapaOriginalAlto - (123 + 34), 45, 34 });//OBJETO INFERIOR TUNEL IZQUIERDO
    objetos.push_back({ 203, mapaOriginalAlto - (195 + 10), 17, 10 });
    objetos.push_back({ 179, mapaOriginalAlto - (123 + 34), 45, 34 });
}



// Dibujar el mapa
void drawMapa() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mapaTexture);

    float mapaOriginalAncho = 227.0f;
    float mapaOriginalAlto = 248.0f;

    float ventanaAncho = 1720.0f;
    float ventanaAlto = 880.0f;

    float escalaX = ventanaAncho / mapaOriginalAncho;
    float escalaY = ventanaAlto / mapaOriginalAlto;

    escalaMapa = std::min(escalaX, escalaY);

    float mapaAncho = mapaOriginalAncho * escalaMapa;
    float mapaAlto = mapaOriginalAlto * escalaMapa;

    centroX = (ventanaAncho - mapaAncho) / 2.0f;
    centroY = (ventanaAlto - mapaAlto) / 2.0f;

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(centroX, centroY);               // Esquina inferior izquierda
    glTexCoord2f(1.0f, 1.0f); glVertex2f(centroX + mapaAncho, centroY);    // Esquina inferior derecha
    glTexCoord2f(1.0f, 0.0f); glVertex2f(centroX + mapaAncho, centroY + mapaAlto);  // Esquina superior derecha
    glTexCoord2f(0.0f, 0.0f); glVertex2f(centroX, centroY + mapaAlto);     // Esquina superior izquierda
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

bool checkCollision(float nextX, float nextY, float pacmanAncho, float pacmanAlto) {
    for (const auto& objeto : objetos) {
        float objetoX = objeto.x * escalaMapa + centroX;
        float objetoY = objeto.y * escalaMapa + centroY;
        float objetoAncho = objeto.ancho * escalaMapa;
        float objetoAlto = objeto.alto * escalaMapa;

        if (nextX < objetoX + objetoAncho &&
            nextX + pacmanAncho > objetoX &&
            nextY < objetoY + objetoAlto &&
            nextY + pacmanAlto > objetoY) {
            return true;
        }
    }
    return false;
}

void initPellets() {
    pellets.clear();
    int pelletSmallSize = 2;
    int pelletBigSize = 8;

    // Pellets grandes

    // SELECTION 8 × 8 @ (8, 24)
    pellets.push_back({8, 31, true});

    // SELECTION 8 × 8 @ (208, 24)
    pellets.push_back({ 208, 31, true });

    // SELECTION 8 × 8 @ (208, 184)
    pellets.push_back({ 208, 191, true });

    // SELECTION 8 × 8 @ (8, 184)
    pellets.push_back({ 8, 191, true });


    // Segmento superior

    // SELECTION 90 × 2 @ (11, 11)
    //pellets.push_back({ 11, 11, false });
    for (int i = 0; i < 12; i++) {
        Pellet smallPellet = { 11 + i * (pelletSmallSize + 6), 11, false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 2 × 2 @ (11, 19)
    for (int i = 0; i < 1; i++) {
        Pellet smallPellet = { 11 + i * (pelletSmallSize + 2), 19, false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 2 × 34 @ (11, 35)
    for (int i = 0; i < 5; i++) {
        Pellet smallPellet = { 11, 35 + i * (pelletSmallSize + 6), false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 26 × 2 @ (19, 67)
    for (int i = 0; i < 4; i++) {
        Pellet smallPellet = { 19 + i * (pelletSmallSize + 6), 67, false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 26 × 2 @ (19, 43)
    for (int i = 0; i < 4; i++) {
        Pellet smallPellet = { 19 + i * (pelletSmallSize + 6), 43, false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 2 × 194 @ (51, 19)
    for (int i = 0; i < 25; i++) {
        Pellet smallPellet = { 51, 19 + i * (pelletSmallSize + 6), false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 106 × 2 @ (59, 43)
    for (int i = 0; i < 14; i++) {
        Pellet smallPellet = { 59 + i * (pelletSmallSize + 6), 43, false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 2 × 18 @ (99, 19)
    for (int i = 0; i < 3; i++) {
        Pellet smallPellet = { 99, 19 + i * (pelletSmallSize + 6), false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 2 × 18 @ (123, 19)
    for (int i = 0; i < 3; i++) {
        Pellet smallPellet = { 123, 19 + i * (pelletSmallSize + 6), false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 90 × 2 @ (123, 11)
    for (int i = 0; i < 12; i++) {
        Pellet smallPellet = { 123 + i * (pelletSmallSize + 6), 11, false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 2 × 194 @ (171, 19)
    for (int i = 0; i < 25; i++) {
        Pellet smallPellet = { 171, 19 + i * (pelletSmallSize + 6), false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 2 × 2 @ (211, 19)
    for (int i = 0; i < 1; i++) {
        Pellet smallPellet = { 211 + i * (pelletSmallSize + 2), 19, false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 2 × 34 @ (211, 35)
    for (int i = 0; i < 5; i++) {
        Pellet smallPellet = { 211, 35 + i * (pelletSmallSize + 6), false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 26 × 2 @ (179, 67)
    for (int i = 0; i < 4; i++) {
        Pellet smallPellet = { 179 + i * (pelletSmallSize + 6), 67, false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 26 × 2 @ (179, 43)
    for (int i = 0; i < 4; i++) {
        Pellet smallPellet = { 179 + i * (pelletSmallSize + 6), 43, false };
        pellets.push_back(smallPellet);
    }

    //
    // SELECTION 2 × 10 @ (75, 51)
    for (int i = 0; i < 2; i++) {
        Pellet smallPellet = { 75, 51 + i * (pelletSmallSize + 8), false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 26 × 2 @ (75, 67)
    for (int i = 0; i < 4; i++) {
        Pellet smallPellet = { 75 + i * (pelletSmallSize + 6), 67, false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 2 × 10 @ (147, 51)
    for (int i = 0; i < 2; i++) {
        Pellet smallPellet = { 147, 51 + i * (pelletSmallSize + 8), false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 26 × 2 @ (123, 67)
    for (int i = 0; i < 4; i++) {
        Pellet smallPellet = { 123 + i * (pelletSmallSize + 6), 67, false };
        pellets.push_back(smallPellet);
    }

    // Segmento inferior

    // SELECTION 2 × 18 @ (11, 163)
    for (int i = 0; i < 3; i++) {
        Pellet smallPellet = { 11, 163 + i * (pelletSmallSize + 6), false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 10 × 2 @ (19, 187)
    for (int i = 0; i < 2; i++) {
        Pellet smallPellet = { 19 + i * (pelletSmallSize + 6), 187, false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 2 × 10 @ (27, 195)
    for (int i = 0; i < 2; i++) {
        Pellet smallPellet = { 27, 195 + i * (pelletSmallSize + 6), false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 26 × 2 @ (19, 163)
    for (int i = 0; i < 4; i++) {
        Pellet smallPellet = { 19 + i * (pelletSmallSize + 6), 163, false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 34 × 2 @ (11, 211)
    for (int i = 0; i < 6; i++) {
        Pellet smallPellet = { 11 + i * (pelletSmallSize + 6), 211, false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 2 × 10 @ (11, 219)
    for (int i = 0; i < 2; i++) {
        Pellet smallPellet = { 11, 219 + i * (pelletSmallSize + 6), false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 42 × 2 @ (59, 163)
    for (int i = 0; i < 6; i++) {
        Pellet smallPellet = { 59 + i * (pelletSmallSize + 6), 163, false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 2 × 10 @ (99, 171)
    for (int i = 0; i < 2; i++) {
        Pellet smallPellet = { 99, 171 + i * (pelletSmallSize + 6), false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 42 × 2 @ (59, 187)
    for (int i = 0; i < 6; i++) {
        Pellet smallPellet = { 59 + i * (pelletSmallSize + 6), 187, false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 2 × 10 @ (75, 195)
    for (int i = 0; i < 2; i++) {
        Pellet smallPellet = { 75, 195 + i * (pelletSmallSize + 6), false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 26 × 2 @ (75, 211)
    for (int i = 0; i < 4; i++) {
        Pellet smallPellet = { 75 + i * (pelletSmallSize + 6), 211, false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 2 × 10 @ (99, 219)
    for (int i = 0; i < 2; i++) {
        Pellet smallPellet = { 99, 219 + i * (pelletSmallSize + 6), false };
        pellets.push_back(smallPellet);
    }
    // Segunda parte del segmento inferior

// SELECTION 202 × 2 @ (11, 235)
    for (int i = 0; i < 26; i++) {
        Pellet smallPellet = { 11 + i * (pelletSmallSize + 6), 235, false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 42 × 2 @ (123, 163)
    for (int i = 0; i < 6; i++) {
        Pellet smallPellet = { 123 + i * (pelletSmallSize + 6), 163, false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 2 × 10 @ (123, 171)
    for (int i = 0; i < 2; i++) {
        Pellet smallPellet = { 123, 171 + i * (pelletSmallSize + 6), false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 42 × 2 @ (123, 187)
    for (int i = 0; i < 6; i++) {
        Pellet smallPellet = { 123 + i * (pelletSmallSize + 6), 187, false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 2 × 10 @ (147, 195)
    for (int i = 0; i < 2; i++) {
        Pellet smallPellet = { 147, 195 + i * (pelletSmallSize + 6), false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 26 × 2 @ (123, 211)
    for (int i = 0; i < 4; i++) {
        Pellet smallPellet = { 123 + i * (pelletSmallSize + 6), 211, false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 2 × 10 @ (123, 219)
    for (int i = 0; i < 2; i++) {
        Pellet smallPellet = { 123, 219 + i * (pelletSmallSize + 6), false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 34 × 2 @ (179, 163)
    for (int i = 0; i < 5; i++) {
        Pellet smallPellet = { 179 + i * (pelletSmallSize + 6), 163, false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 2 × 10 @ (211, 171)
    for (int i = 0; i < 2; i++) {
        Pellet smallPellet = { 211, 171 + i * (pelletSmallSize + 6), false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 10 × 2 @ (195, 187)
    for (int i = 0; i < 2; i++) {
        Pellet smallPellet = { 195 + i * (pelletSmallSize + 6), 187, false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 2 × 10 @ (195, 195)
    for (int i = 0; i < 2; i++) {
        Pellet smallPellet = { 195, 195 + i * (pelletSmallSize + 6), false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 34 × 2 @ (179, 211)
    for (int i = 0; i < 5; i++) {
        Pellet smallPellet = { 179 + i * (pelletSmallSize + 6), 211, false };
        pellets.push_back(smallPellet);
    }

    // SELECTION 2 × 10 @ (211, 219)
    for (int i = 0; i < 2; i++) {
        Pellet smallPellet = { 211, 219 + i * (pelletSmallSize + 6), false };
        pellets.push_back(smallPellet);
    }


}

void checkPelletCollision() {
    bool allPelletsEaten = true;

    for (auto& pellet : pellets) {
        if (pellet.isEaten) continue;

        float pelletX = pellet.x * escalaMapa + centroX;
        float pelletY = (mapaOriginalAlto - pellet.y) * escalaMapa + centroY;
        float pelletAncho = pellet.isBig ? 14.0f : 8.0f;

        if (!pellet.isEaten &&
            pacmanX < pelletX + pelletAncho && pacmanX + pacmanAncho > pelletX &&
            pacmanY < pelletY + pelletAncho && pacmanY + pacmanAlto > pelletY) {

            puntaje += pellet.isBig ? 50 : 10;
            Mix_PlayChannel(-1, eatDotSound, 0);
            pellet.isEaten = true;  
        }

        if (!pellet.isEaten) {
            allPelletsEaten = false;
        }
    }

    /*if (allPelletsEaten) {
        mostrarVentanaFinDeNivel();
    }*/
    if (allPelletsEaten && gameStarted) { 
        mostrarVentanaFinDeNivel();
    }
}


void drawPellets() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mapaTexturePellets);

    for (const auto& pellet : pellets) {
        if (pellet.isEaten) continue; 

        glBegin(GL_QUADS);
        float size = pellet.isBig ? 32.0f : 8.0f;
        float texLeft = pellet.isBig ? 8.0f / 227.0f : 11.0f / 227.0f;
        float texRight = pellet.isBig ? (8.0f + 8.0f) / 227.0f : (11.0f + 2.0f) / 227.0f;
        float texBottom = pellet.isBig ? 24.0f / 248.0f : 19.0f / 248.0f;
        float texTop = pellet.isBig ? (24.0f + 8.0f) / 248.0f : (19.0f + 2.0f) / 248.0f;

        float drawX = (pellet.x * escalaMapa) + centroX;
        float drawY = ((mapaOriginalAlto - pellet.y) * escalaMapa) + centroY;

        glTexCoord2f(texLeft, texBottom); glVertex2f(drawX, drawY);
        glTexCoord2f(texRight, texBottom); glVertex2f(drawX + size, drawY);
        glTexCoord2f(texRight, texTop); glVertex2f(drawX + size, drawY + size);
        glTexCoord2f(texLeft, texTop); glVertex2f(drawX, drawY + size);

        glEnd();
    }

    glDisable(GL_TEXTURE_2D);
}


void renderizarTexto(float x, float y, const char* texto) {
    glRasterPos2f(x, y);  
    for (const char* c = texto; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);  
    }
}

void renderizarPuntaje() {
    std::string textoPuntaje = "Puntaje: " + std::to_string(puntaje); 

    glPushAttrib(GL_CURRENT_BIT);
    glColor3f(1.0f, 1.0f, 0.0f); 
    renderizarTexto(1300.0f, 850.0f, textoPuntaje.c_str());
    glPopAttrib();
}

/*void renderizarTexto(float x, float y, const char* texto) {
    glRasterPos2f(x, y);  // Posición de inicio del texto
    for (const char* c = texto; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);  // Fuente y caracteres
    }
}
// Función para mostrar el puntaje en pantalla
void renderizarPuntaje() {
    std::string textoPuntaje = "Puntaje: " + std::to_string(puntaje); // Convierte el puntaje a texto
    glColor3f(1.0f, 1.0f, 0.0f); // Color amarillo para el texto
    renderizarTexto(1300.0f, 850.0f, textoPuntaje.c_str()); // Posición fuera del mapa, ajustada según resolución
}*/