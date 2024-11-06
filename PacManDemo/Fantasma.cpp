#include <GL/glew.h>
#include <GL/glut.h>
#include "Fantasma.h"
#include "Mapa.h"
#include <cstdlib>

enum Direccion { DERECHA, IZQUIERDA, ARRIBA, ABAJO };

Fantasma::Fantasma(float x, float y, const float color[3])
    : posX(x), posY(y), direccionActual(DERECHA) {
    this->color[0] = color[0];
    this->color[1] = color[1];
    this->color[2] = color[2];
    initAnimaciones();
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

void Fantasma::update() {
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

