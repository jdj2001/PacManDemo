#include <GL/glew.h>
#include <GL/glut.h>
#include "Fantasma.h"
#include "Mapa.h"
#include "Pacman.h"
#include <cstdlib>
#include <SDL.h>

float tiempoSalida[3] = { 10.0f, 15.0f, 20.0f };  
bool fantasmaSalio[3] = { false, false, false };  
float tiempoTranscurrido[3] = { 0.0f, 0.0f, 0.0f }; 
//float salidaX = 104.0f * escalaMapa + centroX;
//float salidaY = (mapaOriginalAlto - (99 + 6)) * escalaMapa + centroY;

//enum Direccion { DERECHA, IZQUIERDA, ARRIBA, ABAJO };
enum Direccion { DERECHA, IZQUIERDA, ARRIBA, ABAJO, DERECHA_F, IZQUIERDA_F, ARRIBA_F, ABAJO_F };

Fantasma::Fantasma(float x, float y, const float color[3], bool enJaula, Uint32 tiempoSalida)
    : posX(x), posY(y), direccionActual(ARRIBA), enJaula(enJaula), tiempoSalida(tiempoSalida) {
    this->color[0] = color[0];
    this->color[1] = color[1];
    this->color[2] = color[2];
    initAnimaciones();
}

void Fantasma::setEnJaula(bool enJaula) {
    this->enJaula = enJaula;
}

void Fantasma::initAnimaciones() {
    
    if (color[0] == 1.0f && color[1] == 0.0f && color[2] == 0.0f) { // Rojo
        animaciones[DERECHA] = { 3.0f / 226.0f, (3.0f + 14.0f) / 226.0f, 65.0f / 248.0f, (65.0f + 14.0f) / 248.0f };
        animaciones[IZQUIERDA] = { (3.0f + 14.0f) / 226.0f, 3.0f / 226.0f, 65.0f / 248.0f, (65.0f + 14.0f) / 248.0f };
        animaciones[ARRIBA] = { 67.0f / 226.0f, (67.0f + 14.0f) / 226.0f, 65.0f / 248.0f, (65.0f + 14.0f) / 248.0f };
        animaciones[ABAJO] = { 99.0f / 226.0f, (99.0f + 14.0f) / 226.0f, 65.0f / 248.0f, (65.0f + 14.0f) / 248.0f };
    }
    else if (color[0] == 255.0f / 255.0f && color[1] == 183.0f / 255.0f && color[2] == 255.0f / 255.0f) { // Rosa
        animaciones[DERECHA] = { 3.0f / 226.0f, (3.0f + 14.0f) / 226.0f, 81.0f / 248.0f, (81.0f + 14.0f) / 248.0f };
        animaciones[IZQUIERDA] = { (3.0f + 14.0f) / 226.0f, 3.0f / 226.0f, 81.0f / 248.0f, (81.0f + 14.0f) / 248.0f };
        animaciones[ARRIBA] = { 67.0f / 226.0f, (67.0f + 14.0f) / 226.0f, 81.0f / 248.0f, (81.0f + 14.0f) / 248.0f };
        animaciones[ABAJO] = { 99.0f / 226.0f, (99.0f + 14.0f) / 226.0f, 81.0f / 248.0f, (81.0f + 14.0f) / 248.0f };
    }
    else if (color[0] == 0.0f && color[1] == 255.0f / 255.0f && color[2] == 255.0f / 255.0f) { // Azul claro
        animaciones[DERECHA] = { 3.0f / 226.0f, (3.0f + 14.0f) / 226.0f, 97.0f / 248.0f, (97.0f + 14.0f) / 248.0f };
        animaciones[IZQUIERDA] = { (3.0f + 14.0f) / 226.0f, 3.0f / 226.0f, 97.0f / 248.0f, (97.0f + 14.0f) / 248.0f };
        animaciones[ARRIBA] = { 67.0f / 226.0f, (67.0f + 14.0f) / 226.0f, 97.0f / 248.0f, (97.0f + 14.0f) / 248.0f };
        animaciones[ABAJO] = { 99.0f / 226.0f, (99.0f + 14.0f) / 226.0f, 97.0f / 248.0f, (97.0f + 14.0f) / 248.0f };
    }
    else if (color[0] == 254.0f / 255.0f && color[1] == 182.0f / 255.0f && color[2] == 81.0f / 255.0f) { // Naranja
        animaciones[DERECHA] = { 3.0f / 226.0f, (3.0f + 14.0f) / 226.0f, 113.0f / 248.0f, (113.0f + 14.0f) / 248.0f };
        animaciones[IZQUIERDA] = { (3.0f + 14.0f) / 226.0f, 3.0f / 226.0f, 113.0f / 248.0f, (113.0f + 14.0f) / 248.0f };
        animaciones[ARRIBA] = { 67.0f / 226.0f, (67.0f + 14.0f) / 226.0f, 113.0f / 248.0f, (113.0f + 14.0f) / 248.0f };
        animaciones[ABAJO] = { 99.0f / 226.0f, (99.0f + 14.0f) / 226.0f, 113.0f / 248.0f, (113.0f + 14.0f) / 248.0f };
    }
}

void Fantasma::draw(GLuint textureID) {
    glPushAttrib(GL_CURRENT_BIT);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    Animacion currentAnim = animaciones[direccionActual];

    glBegin(GL_QUADS);
    glTexCoord2f(currentAnim.texCoordLeft, currentAnim.texCoordBottom); glVertex2f(posX, posY + fantasmaAlto);
    glTexCoord2f(currentAnim.texCoordRight, currentAnim.texCoordBottom); glVertex2f(posX + fantasmaAncho, posY + fantasmaAlto);
    glTexCoord2f(currentAnim.texCoordRight, currentAnim.texCoordTop); glVertex2f(posX + fantasmaAncho, posY);
    glTexCoord2f(currentAnim.texCoordLeft, currentAnim.texCoordTop); glVertex2f(posX, posY);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glPopAttrib();
}
//#########
/*void Fantasma::update() {
    float nextX = posX;
    float nextY = posY;

    switch (direccionActual) {
    case DERECHA: nextX += speed; break;
    case IZQUIERDA: nextX -= speed; break;
    case ARRIBA: nextY += speed; break;
    case ABAJO: nextY -= speed; break;
    }

    if (!checkCollision(nextX, nextY, fantasmaAncho, fantasmaAlto)) {
        posX = nextX;
        posY = nextY;
    }
    else {
        direccionActual = rand() % 4;
    }
}*/
//##########
void Fantasma::update() {
    Uint32 tiempoActual = SDL_GetTicks();
    
    //Mix_PlayMusic(movimientoFatasmas, 0);
    
    float limiteSuperiorJaula = (mapaOriginalAlto - 117) * escalaMapa + centroY;
    float limiteInferiorJaula = (mapaOriginalAlto - 128) * escalaMapa + centroY;
    float puertaJaulaY = (mapaOriginalAlto - 99) * escalaMapa + centroY;
    float salidaX = 106.0f * escalaMapa + centroX;

    if (enJaula) {
        float nextX = posX;
        float nextY = posY;

        if (tiempoActual >= tiempoSalida) {
            if (posX != salidaX) {
                if (posX < salidaX) {
                    posX = salidaX;

                }
                else if (posX > salidaX) {
                    //direccionActual = IZQUIERDA;
                    //nextX -= speed;
                    posX = salidaX;

                }
                /*if (posY < puertaJaulaY) {
                    direccionActual = ARRIBA;
                    nextY += speed;
                }*/
                if (posY < puertaJaulaY && posX == salidaX) {
                    direccionActual = ARRIBA;
                    nextY += speed;
                    int randomValue = rand() % 2; // Genera 0, 1 o 2

                    if (randomValue == 0) {
                        direccionActual = DERECHA;
                    }
                    else if (randomValue == 1) {
                        direccionActual = IZQUIERDA;
                    }
                }
            }
            else {
                enJaula = false;

            }
        }
        else {
            if (direccionActual == ARRIBA) {
                nextY += speed;
                if (nextY >= limiteSuperiorJaula) {
                    direccionActual = ABAJO;
                }
            }
            else if (direccionActual == ABAJO) {
                nextY -= speed;
                if (nextY <= limiteInferiorJaula) {
                    direccionActual = ARRIBA;
                }
            }
        }
        posY = nextY;
    }
    else if (!enJaula) {
        float nextX = posX;
        float nextY = posY;
        switch (direccionActual) {
        case DERECHA: nextX += speed; break;
        case IZQUIERDA: nextX -= speed; break;
        case ARRIBA: nextY += speed; break;
        case ABAJO: nextY -= speed; break;
        }

        if (!checkCollision(nextX, nextY, fantasmaAncho, fantasmaAlto)) {
            posX = nextX;
            posY = nextY;
        }
        else {
            direccionActual = rand() % 4;
        }
    }


}


void Fantasma::checkSalida(Uint32 tiempoActual) {
    if (enJaula && tiempoActual >= tiempoSalida) {
        direccionActual = ARRIBA;  
    }
}


bool Fantasma::checkCollisionWithPacman(float pacmanX, float pacmanY, float pacmanAncho, float pacmanAlto) {
    return (posX < pacmanX + pacmanAncho &&
        posX + fantasmaAncho > pacmanX &&
        posY < pacmanY + pacmanAlto &&
        posY + fantasmaAlto > pacmanY);
}
//nueva parte
/*void Fantasma::changeDirection() {
    float nextX = posX;
    float nextY = posY;

    switch (direccionActual) {
    case DERECHA: nextX += speed; break;
    case IZQUIERDA: nextX -= speed; break;
    case ARRIBA: nextY += speed; break;
    case ABAJO: nextY -= speed; break;
    }
    if (!checkCollision(nextX, nextY, fantasmaAncho, fantasmaAlto)) {
        posX = nextX;
        posY = nextY;
    }
    else {
        if (direccionActual == DERECHA && checkCollision(nextX, nextY, fantasmaAncho, fantasmaAlto) ||
            direccionActual == ARRIBA && checkCollision(nextX, nextY, fantasmaAncho, fantasmaAlto) ||
            direccionActual == ABAJO && checkCollision(nextX, nextY, fantasmaAncho, fantasmaAlto)) {
            direccionActual = IZQUIERDA;
            posX = nextX;
            posY = nextY;
        }
        else if (direccionActual == IZQUIERDA && checkCollision(nextX, nextY, fantasmaAncho, fantasmaAlto) ||
            direccionActual == ARRIBA && checkCollision(nextX, nextY, fantasmaAncho, fantasmaAlto) ||
            direccionActual == ABAJO && checkCollision(nextX, nextY, fantasmaAncho, fantasmaAlto)) {
            direccionActual = DERECHA;
            posX = nextX;
            posY = nextY;
        }
        else if (direccionActual == DERECHA && checkCollision(nextX, nextY, fantasmaAncho, fantasmaAlto) ||
            direccionActual == ARRIBA && checkCollision(nextX, nextY, fantasmaAncho, fantasmaAlto) ||
            direccionActual == IZQUIERDA && checkCollision(nextX, nextY, fantasmaAncho, fantasmaAlto)) {
            direccionActual = ABAJO;
            posX = nextX;
            posY = nextY;
        }
        else if (direccionActual == DERECHA && checkCollision(nextX, nextY, fantasmaAncho, fantasmaAlto) ||
            direccionActual == IZQUIERDA && checkCollision(nextX, nextY, fantasmaAncho, fantasmaAlto) ||
            direccionActual == ABAJO && checkCollision(nextX, nextY, fantasmaAncho, fantasmaAlto)) {
            direccionActual = ARRIBA;
            posX = nextX;
            posY = nextY;
        }
    }
}
/*void Fantasma::changeDirection() {
    switch (direccionActual) {
    case DERECHA: direccionActual = IZQUIERDA; break;
    case IZQUIERDA: direccionActual = DERECHA; break;
    case ARRIBA: direccionActual = ABAJO; break;
    case ABAJO: direccionActual = ARRIBA; break;
    }
}

void Fantasma::colisiones() {
    

    if (!checkCollision(nextX, nextY, fantasmaAncho, fantasmaAlto)) {
        posX = nextX;
        posY = nextY;
    }
    else {
        changeDirection();
    }
}

void Fantasma::chooseDirection(float pacmanX, float pacmanY) {
    if (std::abs(pacmanX - posX) > std::abs(pacmanY - posY)) {
        direccionActual = (pacmanX > posX) ? DERECHA : IZQUIERDA;
    }
    else {
        direccionActual = (pacmanY > posY) ? ARRIBA : ABAJO;
    } 
}

bool Fantasma::checkCollisionWithPacman(float pacmanX, float pacmanY, float pacmanAncho, float pacmanAlto) {
    return (posX < pacmanX + pacmanAncho &&
        posX + fantasmaAncho > pacmanX &&
        posY < pacmanY + pacmanAlto &&
        posY + fantasmaAlto > pacmanY);
}

void Fantasma::update() {
    Uint32 tiempoActual = SDL_GetTicks();
    float nextX = posX;
    float nextY = posY;

    if (enModoPersecucion && enJaula == false) {
        // Modo persecución: Actualizar dirección hacia Pac-Man
        //chooseDirection(pacmanX, pacmanY);
        changeDirection();
    }
    else if (!enModoPersecucion && enJaula == false) {
        if (!checkCollision(nextX, nextY, fantasmaAncho, fantasmaAlto)) {
            posX = nextX;
            posY = nextY;
        }
        else {
            direccionActual = rand() % 4;  // Cambia a una nueva dirección
        }
    }

    // Actualizar posición según la dirección actual
    /*switch (direccionActual) {
    case DERECHA: nextX += speed; break;
    case IZQUIERDA: nextX -= speed; break;
    case ARRIBA: nextY += speed; break;
    case ABAJO: nextY -= speed; break;
    }

    // Verificar colisiones
    if (!checkCollision(nextX, nextY, fantasmaAncho, fantasmaAlto)) {
        posX = nextX;
        posY = nextY;
    }
    else {
        //changeDirection();  // Cambiar dirección si hay colisión
    }

    // Alterna entre modo persecución y modo aleatorio cada 5 segundos
    if (tiempoActual - tiempoUltimoCambio > 5000) {
        enModoPersecucion = !enModoPersecucion;
        tiempoUltimoCambio = tiempoActual;
    }
}*/

