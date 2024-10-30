#include <GL/glew.h>
#include <GL/glut.h>
#include "Mapa.h"
#include "Game.h"
#include "Pacman.h"
#include <vector>
#include "stb_image.h"
#include "TextureLoader.h"
#include <iostream>

float mapaX = 0.0f;
float mapaY = 0.0f;

struct Objeto {
    float x, y, ancho, alto;  
};

struct Pasillo {
    float x, y, ancho, alto;  // Estructura para representar los pasillos
};

std::vector<Objeto> objetos;  // Vector que contendrá los objetos (paredes y obstáculos)
std::vector<Pasillo> pasillos;  // Vector para los pasillos

extern float escalaMapa;  
extern float centroX;     
extern float centroY;     

float mapaOriginalAlto = 248.0f;
float mapaOriginalAncho = 227.0f;

void initMapa() {
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

    /*glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(centroX, centroY);               // Esquina inferior izquierda
    glTexCoord2f(1.0f, 1.0f); glVertex2f(centroX + mapaOriginalAncho, centroY);    // Esquina inferior derecha
    glTexCoord2f(1.0f, 0.0f); glVertex2f(centroX + mapaOriginalAncho, centroY + mapaOriginalAlto);  // Esquina superior derecha
    glTexCoord2f(0.0f, 0.0f); glVertex2f(centroX, centroY + mapaOriginalAlto);     // Esquina superior izquierda
    glEnd();*/
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
            return true;  // Colisión detectada
        }
    }
    return false;  // No hay colisión
}

