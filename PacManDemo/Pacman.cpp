#include "Pacman.h"
#include "Game.h"
#include "Mapa.h"

float pacmanX = 0.0f;
float pacmanY = 0.0f;
float pacmanSpeed = 3.0f; 
float pacmanAncho = 46.0f;
float pacmanAlto = 46.0f;

enum Direccion { DERECHA, IZQUIERDA, ARRIBA, ABAJO };
Direccion direccionActual = DERECHA;
bool enMovimiento = false; 

int animacionIndex = 0;
int animacionDelay = 40;  
float lastAnimacionTime = 0;  

struct Animacion {
    float texCoordLeft;
    float texCoordRight;
    float texCoordBottom;
    float texCoordTop;
};

Animacion pacmanAnimaciones[3][4];  

void initAnimaciones() {
    pacmanAnimaciones[0][DERECHA] = { 35.0f / 226.0f, (35.0f + 13.0f) / 226.0f, (1.0f + 13.0f) / 248.0f, 1.0f / 248.0f };
    pacmanAnimaciones[0][IZQUIERDA] = pacmanAnimaciones[0][DERECHA];  
    pacmanAnimaciones[0][ARRIBA] = pacmanAnimaciones[0][DERECHA];     
    pacmanAnimaciones[0][ABAJO] = pacmanAnimaciones[0][DERECHA];      

    pacmanAnimaciones[1][DERECHA] = { 19.0f / 226.0f, (19.0f + 12.0f) / 226.0f, (1.0f + 13.0f) / 248.0f, 1.0f / 248.0f };
    pacmanAnimaciones[1][IZQUIERDA] = { (19.0f + 12.0f) / 226.0f, 19.0f / 226.0f, (1.0f + 13.0f) / 248.0f, 1.0f / 248.0f };  
    pacmanAnimaciones[1][ARRIBA] = { 19.0f / 226.0f, (19.0f + 13.0f) / 226.0f, (34.0f + 12.0f) / 248.0f, 34.0f / 248.0f };
    pacmanAnimaciones[1][ABAJO] = { 19.0f / 226.0f, (19.0f + 13.0f) / 226.0f, 34.0f / 248.0f, (34.0f + 12.0f) / 248.0f };   

    pacmanAnimaciones[2][DERECHA] = { 3.0f / 226.0f, (3.0f + 9.0f) / 226.0f, (1.0f + 13.0f) / 248.0f, 1.0f / 248.0f };
    pacmanAnimaciones[2][IZQUIERDA] = { (3.0f + 9.0f) / 226.0f, 3.0f / 226.0f, (1.0f + 13.0f) / 248.0f, 1.0f / 248.0f };  
    pacmanAnimaciones[2][ARRIBA] = { 3.0f / 226.0f, (3.0f + 13.0f) / 226.0f, (37.0f + 9.0f) / 248.0f, 37.0f / 248.0f };
    pacmanAnimaciones[2][ABAJO] = { 3.0f / 226.0f, (3.0f + 13.0f) / 226.0f, 37.0f / 248.0f, (37.0f + 9.0f) / 248.0f };    
}

void initPacman(float centroX, float centroY, float escalaMapa) {
    pacmanX = centroX + 106.0f * escalaMapa;
    pacmanY = centroY + 101.5f * escalaMapa;

    initAnimaciones();
}

void drawPacman(GLuint textureID) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    Animacion currentAnim = pacmanAnimaciones[animacionIndex][direccionActual];

    glBegin(GL_QUADS);
    glTexCoord2f(currentAnim.texCoordLeft, currentAnim.texCoordBottom); glVertex2f(pacmanX, pacmanY);
    glTexCoord2f(currentAnim.texCoordRight, currentAnim.texCoordBottom); glVertex2f(pacmanX + pacmanAncho, pacmanY);
    glTexCoord2f(currentAnim.texCoordRight, currentAnim.texCoordTop); glVertex2f(pacmanX + pacmanAncho, pacmanY + pacmanAlto);
    glTexCoord2f(currentAnim.texCoordLeft, currentAnim.texCoordTop); glVertex2f(pacmanX, pacmanY + pacmanAlto);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void updatePacmanAnimacion() {
    float currentTime = glutGet(GLUT_ELAPSED_TIME);
    if (currentTime - lastAnimacionTime > animacionDelay) {
        animacionIndex = (animacionIndex + 1) % 3;  
        lastAnimacionTime = currentTime;
    }
}

void updatePacman() {
    if (enMovimiento) {
        updatePacmanAnimacion();
        float nextX = pacmanX;
        float nextY = pacmanY;

        switch (direccionActual) {
        case DERECHA:
            nextX += pacmanSpeed;
            break;
        case IZQUIERDA:
            nextX -= pacmanSpeed;
            break;
        case ARRIBA:
            nextY += pacmanSpeed;
            break;
        case ABAJO:
            nextY -= pacmanSpeed;
            break;
        }

        float tunelIzquierdoX = centroX;
        float tunelDerechoX = (223 * escalaMapa) + centroX;
        float tunelYMin = (mapaOriginalAlto - 123) * escalaMapa + centroY;
        float tunelYMax = (mapaOriginalAlto - 109) * escalaMapa + centroY;

        //({ 0, mapaOriginalAlto - (109 + 14), 1, 14 });
        //({ 223, mapaOriginalAlto - (109 + 14), 1, 14 });

        if (nextX < tunelIzquierdoX && (pacmanY > tunelYMin && pacmanY < tunelYMax)) {
            nextX = tunelDerechoX - pacmanAncho;  
        }
        else if (nextX > tunelDerechoX && (pacmanY > tunelYMin && pacmanY < tunelYMax)) {
            nextX = tunelIzquierdoX;  
        }

        if (!checkCollision(nextX, nextY, pacmanAncho, pacmanAlto)) {
            pacmanX = nextX;
            pacmanY = nextY;
        }
        else {
            enMovimiento = false;
        }
    }
}


void processPacmanInput(unsigned char key) {
    float nextX = pacmanX;
    float nextY = pacmanY;

    switch (key) {
    case 'd':  
        nextX += pacmanSpeed;
        if (!checkCollision(nextX, pacmanY, pacmanAncho, pacmanAlto)) {
            direccionActual = DERECHA;
            enMovimiento = true;
        }
        break;
    case 'a': 
        nextX -= pacmanSpeed;
        if (!checkCollision(nextX, pacmanY, pacmanAncho, pacmanAlto)) {
            direccionActual = IZQUIERDA;
            enMovimiento = true;
        }
        break;
    case 'w': 
        nextY += pacmanSpeed;
        if (!checkCollision(pacmanX, nextY, pacmanAncho, pacmanAlto)) {
            direccionActual = ARRIBA;
            enMovimiento = true;
        }
        break;
    case 's':
        nextY -= pacmanSpeed;
        if (!checkCollision(pacmanX, nextY, pacmanAncho, pacmanAlto)) {
            direccionActual = ABAJO;
            enMovimiento = true;
        }
        break;
    }
}