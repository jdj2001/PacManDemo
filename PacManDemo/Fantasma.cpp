#include <GL/glew.h>
#include <GL/glut.h>
#include "Fantasma.h"
#include "Mapa.h"
#include "Pacman.h"
#include <cstdlib>
#include <SDL.h>
#include "Game.h"
#include "TextureLoader.h"

float tiempoSalida[3] = { 10.0f, 15.0f, 20.0f };
bool fantasmaSalio[3] = { false, false, false };
//float tiempoTranscurrido[3] = { 0.0f, 0.0f, 0.0f };

Animacion animacionVulnerable;
enum Direccion { DERECHA, IZQUIERDA, ARRIBA, ABAJO};

Fantasma::Fantasma(float x, float y, const float color[3], bool enJaula, Uint32 tiempoSalida)
    : posX(x), posY(y), direccionActual(ARRIBA), enJaula(enJaula), tiempoSalida(tiempoSalida),
    vulnerable(false), duracionVulnerable(5000) {
    this->color[0] = color[0];
    this->color[1] = color[1];
    this->color[2] = color[2];
    initAnimaciones();

    texturaNormal = fantasmasTexture; 
    texturaVulnerable = fantasmasVulnerablesTexture; 
    texturaActual = texturaNormal; 
}

void Fantasma::setVulnerable(bool vulnerable, Uint32 tiempoActual) {
    esVulnerable = vulnerable;
    tiempoVulnerable = tiempoActual;
    texturaActual = esVulnerable ? texturaVulnerable : texturaNormal;
}


bool Fantasma::isVulnerable() const {
    return esVulnerable;
}

/*void Fantasma::setEnJaula(bool enJaula) {
    this->enJaula = enJaula;
}*/
void Fantasma::setEnJaula(bool enJaula, Uint32 tiempoActual) {
    this->enJaula = enJaula;
    if (enJaula) {
        tiempoSalida = tiempoActual + 5000;  
        posX = 106.0f * escalaMapa + centroX;  
        posY = (mapaOriginalAlto - 122.0f) * escalaMapa + centroY;
        direccionActual = ARRIBA; 
        esVulnerable = false;  
        texturaActual = texturaNormal;  
    }
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

    animacionVulnerable = { 131.0f / 226.0f, (131.0f + 14.0f) / 226.0f, 65.0f / 248.0f, (65.0f + 14.0f) / 248.0f };
}

void Fantasma::draw() {
    //glPushAttrib(GL_CURRENT_BIT);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaActual);

    //glColor3f(1.0f, 0.0f, 0.0f);

    Animacion currentAnim = esVulnerable ? animacionVulnerable : animaciones[direccionActual];

    glBegin(GL_QUADS);
    glTexCoord2f(currentAnim.texCoordLeft, currentAnim.texCoordBottom); glVertex2f(posX, posY + fantasmaAlto);
    glTexCoord2f(currentAnim.texCoordRight, currentAnim.texCoordBottom); glVertex2f(posX + fantasmaAncho, posY + fantasmaAlto);
    glTexCoord2f(currentAnim.texCoordRight, currentAnim.texCoordTop); glVertex2f(posX + fantasmaAncho, posY);
    glTexCoord2f(currentAnim.texCoordLeft, currentAnim.texCoordTop); glVertex2f(posX, posY);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    //glColor3f(1.0f, 1.0f, 1.0f);

    //glPopAttrib();
    //glColor3f(1.0f, 1.0f, 1.0f);
}

/*void Fantasma::update() {
    Uint32 tiempoActual = SDL_GetTicks();

    //Mix_PlayMusic(movimientoFatasmas, 0);

    float limiteSuperiorJaula = (mapaOriginalAlto - 117) * escalaMapa + centroY;
    float limiteInferiorJaula = (mapaOriginalAlto - 126) * escalaMapa + centroY;
    float puertaJaulaY = (mapaOriginalAlto - 99) * escalaMapa + centroY;
    float salidaX = 106.0f * escalaMapa + centroX;

    if (esVulnerable && (tiempoActual - tiempoVulnerable > duracionVulnerable)) {
        setVulnerable(false, tiempoActual);  
    }

    if (enJaula) {
        float nextX = posX;
        float nextY = posY;

        if (tiempoActual >= tiempoSalida) {
            if (posX != salidaX) {
                posX = salidaX;
                /*if (posX < salidaX) {
                    posX = salidaX;

                }
                else if (posX > salidaX) {
                    //direccionActual = IZQUIERDA;
                    //nextX -= speed;
                    posX = salidaX;

                }*/
                /*if (posY < puertaJaulaY) {
                    direccionActual = ARRIBA;
                    nextY += speed;
                }
                direccionActual = ARRIBA;
                nextY += speed;
                //nextY += speed;
                //int randomValue = rand() % 2;

                
                
            }
            /*if (posY < puertaJaulaY && posX == salidaX) {
                direccionActual = ARRIBA;
                nextY += speed;
                int randomValue = rand() % 2;

                if (randomValue == 0) {
                    direccionActual = DERECHA;
                }
                else if (randomValue == 1) {
                    direccionActual = IZQUIERDA;
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
            posY = nextY;
        }
        
        //posY = nextY;

        if (posY >= puertaJaulaY) {
            direccionActual = (rand() % 2 == 0) ? DERECHA : IZQUIERDA;
            if (direccionActual == DERECHA)
            {
                nextX += speed;
            }
            else if (direccionActual == IZQUIERDA)
            {
                nextX += speed;
            }
        }
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
}*/
void Fantasma::update() {
    Uint32 tiempoActual = SDL_GetTicks();

    float limiteSuperiorJaula = (mapaOriginalAlto - 117) * escalaMapa + centroY;
    float limiteInferiorJaula = (mapaOriginalAlto - 126) * escalaMapa + centroY;
    float puertaJaulaY = (mapaOriginalAlto - 99) * escalaMapa + centroY;
    float salidaX = 106.0f * escalaMapa + centroX;

    if (esVulnerable && (tiempoActual - tiempoVulnerable > duracionVulnerable)) {
        setVulnerable(false, tiempoActual);
    }

    if (enJaula) {
        float nextX = posX;
        float nextY = posY;

        if (tiempoActual >= tiempoSalida) {
            if (posX != salidaX) {
                posX = salidaX; 
                direccionActual = ARRIBA;
            }
            else if (posY < puertaJaulaY) {
                nextY += speed;
                posY = nextY;
            }
            else if (posY >= puertaJaulaY) {
                direccionActual = (rand() % 2 == 0) ? DERECHA : IZQUIERDA;
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
            posY = nextY;
        }
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

