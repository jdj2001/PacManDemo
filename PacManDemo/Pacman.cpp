#include <GL/glew.h>
#include <GL/glut.h>
#include "Pacman.h"
#include "Game.h"
#include "Mapa.h"
#include <cmath>
#include <vector>
#include "Fantasma.h"

float pacmanX = 0.0f;
float pacmanY = 0.0f;
float pacmanSpeed = 3.0f;
float pacmanAncho = 46.0f;
float pacmanAlto = 46.0f;

int vidas = 3;  
bool isDying = false; 

int deathAnimIndex = 0;
float deathAnimDelay = 100;
float lastDeathAnimTime = 0;

enum Direccion { DERECHA, IZQUIERDA, ARRIBA, ABAJO };
Direccion direccionActual = DERECHA;
bool enMovimiento = false;

int animacionIndex = 0;
int animacionDelay = 40;
float lastAnimacionTime = 0;

/*struct Animacion {
    float texCoordLeft;
    float texCoordRight;
    float texCoordBottom;
    float texCoordTop;
};*/

Animacion pacmanAnimaciones[3][4];

extern const Animacion vidaIcono = { 133.0f / 226.0f, (133.0f + 10.0f) / 226.0f, 18.0f / 248.0f, (18.0f + 11.0f) / 248.0f };

std::vector<Animacion> deathAnimaciones = {
    {51.0f / 226.0f, (51.0f + 13.0f) / 226.0f, 3.0f / 248.0f, (3.0f + 9.0f) / 248.0f},
    {66.0f / 226.0f, (66.0f + 15.0f) / 226.0f, 4.0f / 248.0f, (4.0f + 8.0f) / 248.0f},
    {82.0f / 226.0f, (82.0f + 15.0f) / 226.0f, 6.0f / 248.0f, (6.0f + 6.0f) / 248.0f},
    {98.0f / 226.0f, (98.0f + 15.0f) / 226.0f, 7.0f / 248.0f, (7.0f + 5.0f) / 248.0f},
    {114.0f / 226.0f, (114.0f + 15.0f) / 226.0f, 8.0f / 248.0f, (8.0f + 5.0f) / 248.0f},
    {130.0f / 226.0f, (130.0f + 15.0f) / 226.0f, 8.0f / 248.0f, (8.0f + 6.0f) / 248.0f},
    {147.0f / 226.0f, (147.0f + 15.0f) / 226.0f, 8.0f / 248.0f, (8.0f + 7.0f) / 248.0f},
    {165.0f / 226.0f, (165.0f + 15.0f) / 226.0f, 8.0f / 248.0f, (8.0f + 7.0f) / 248.0f},
    {183.0f / 226.0f, (183.0f + 5.0f) / 226.0f, 8.0f / 248.0f, (8.0f + 7.0f) / 248.0f},
    {201.0f / 226.0f, (201.0f + 15.0f) / 226.0f, 8.0f / 248.0f, (8.0f + 6.0f) / 248.0f},
    {212.0f / 226.0f, (212.0f + 15.0f) / 226.0f, 6.0f / 248.0f, (6.0f + 10.0f) / 248.0f},
    //FALTAN ANIMACIONES
};

void initAnimaciones() {
    pacmanAnimaciones[0][DERECHA] = { 35.0f / 226.0f, (35.0f + 13.0f) / 226.0f, (1.0f + 13.0f) / 248.0f, 1.0f / 248.0f };
    pacmanAnimaciones[0][IZQUIERDA] = pacmanAnimaciones[0][DERECHA];
    pacmanAnimaciones[0][ARRIBA] = pacmanAnimaciones[0][DERECHA];
    pacmanAnimaciones[0][ABAJO] = pacmanAnimaciones[0][DERECHA];

    pacmanAnimaciones[1][DERECHA] = { 19.0f / 226.0f, (19.0f + 12.0f) / 226.0f, (1.0f + 13.0f) / 248.0f, 1.0f / 248.0f };
    pacmanAnimaciones[1][IZQUIERDA] = { (19.0f + 12.0f) / 226.0f, 19.0f / 226.0f, (1.0f + 13.0f) / 248.0f, 1.0f / 248.0f };  // mirrow
    pacmanAnimaciones[1][ARRIBA] = { 19.0f / 226.0f, (19.0f + 13.0f) / 226.0f, (34.0f + 12.0f) / 248.0f, 34.0f / 248.0f };
    pacmanAnimaciones[1][ABAJO] = { 19.0f / 226.0f, (19.0f + 13.0f) / 226.0f, 34.0f / 248.0f, (34.0f + 12.0f) / 248.0f };   //mirrow

    pacmanAnimaciones[2][DERECHA] = { 3.0f / 226.0f, (3.0f + 9.0f) / 226.0f, (1.0f + 13.0f) / 248.0f, 1.0f / 248.0f };
    pacmanAnimaciones[2][IZQUIERDA] = { (3.0f + 9.0f) / 226.0f, 3.0f / 226.0f, (1.0f + 13.0f) / 248.0f, 1.0f / 248.0f };
    pacmanAnimaciones[2][ARRIBA] = { 3.0f / 226.0f, (3.0f + 13.0f) / 226.0f, (37.0f + 9.0f) / 248.0f, 37.0f / 248.0f };
    pacmanAnimaciones[2][ABAJO] = { 3.0f / 226.0f, (3.0f + 13.0f) / 226.0f, 37.0f / 248.0f, (37.0f + 9.0f) / 248.0f };
}

void initPacman(float centroX, float centroY, float escalaMapa, bool inicializarVidas = true) {
    pacmanX = centroX + 106.0f * escalaMapa;
    pacmanY = centroY + 101.5f * escalaMapa;

    initAnimaciones();

    if (inicializarVidas) {
        vidas = 3;  
    }

    isDying = false;
}

void renderizarVidas() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, pacmanTexture);

    for (int i = 0; i < vidas; ++i) {
        float x = 1500.0f + i * 30.0f;
        float y = 850.0f;

        glBegin(GL_QUADS);
        glTexCoord2f(vidaIcono.texCoordLeft, vidaIcono.texCoordBottom); glVertex2f(x, y);
        glTexCoord2f(vidaIcono.texCoordRight, vidaIcono.texCoordBottom); glVertex2f(x + 20.0f, y);
        glTexCoord2f(vidaIcono.texCoordRight, vidaIcono.texCoordTop); glVertex2f(x + 20.0f, y + 20.0f);
        glTexCoord2f(vidaIcono.texCoordLeft, vidaIcono.texCoordTop); glVertex2f(x, y + 20.0f);
        glEnd();
    }

    glDisable(GL_TEXTURE_2D);
}

void drawDeathAnim(GLuint textureID) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    Animacion deathFrame = deathAnimaciones[deathAnimIndex];
    glBegin(GL_QUADS);
    glTexCoord2f(deathFrame.texCoordLeft, deathFrame.texCoordBottom); glVertex2f(pacmanX, pacmanY);
    glTexCoord2f(deathFrame.texCoordRight, deathFrame.texCoordBottom); glVertex2f(pacmanX + pacmanAncho, pacmanY);
    glTexCoord2f(deathFrame.texCoordRight, deathFrame.texCoordTop); glVertex2f(pacmanX + pacmanAncho, pacmanY + pacmanAlto);
    glTexCoord2f(deathFrame.texCoordLeft, deathFrame.texCoordTop); glVertex2f(pacmanX, pacmanY + pacmanAlto);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void loseLife() {
    if (!isDying && vidas > 0) {
        vidas--;
        isDying = true;
        deathAnimIndex = 0;  // Reiniciar animación de muerte
        if (vidas == 0) {
            mostrarVentanaDerrota();  // Mostrar ventana de derrota si no hay más vidas
        }
    }
}

void updateDeathAnim() {
    if (isDying) {
        float currentTime = glutGet(GLUT_ELAPSED_TIME);
        if (currentTime - lastDeathAnimTime > deathAnimDelay) {
            if (deathAnimIndex < deathAnimaciones.size() - 1) {
                deathAnimIndex++;
                lastDeathAnimTime = currentTime;
            }
            else {
                isDying = false;  // Terminar la animación
                if (vidas > 0) {
                    reiniciarPosiciones();  // Reiniciar posiciones si aún tiene vidas
                    isGamePaused = false;
                }
                else {
                    mostrarVentanaDerrota();  // Mostrar derrota si no tiene más vidas
                }
            }
        }
    }
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

    if (isDying) {
        drawDeathAnim(textureID);
    }
    else {
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
}

void updatePacmanAnimacion() {
    float currentTime = glutGet(GLUT_ELAPSED_TIME);
    if (currentTime - lastAnimacionTime > animacionDelay) {
        animacionIndex = (animacionIndex + 1) % 3;
        lastAnimacionTime = currentTime;
    }
}

void updatePacman() {

    if (isDying) {
        updateDeathAnim();
    }
    else if (enMovimiento) {
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
        //16 × 1 @ (104, 99)
        //88, mapaOriginalAlto - (104 + 24), 1, 24
        float puertaJaulaY = (mapaOriginalAlto - 99) * escalaMapa + centroY;
        float puertaJaulaXMin = (104 * escalaMapa) + centroX;
        float puertaJaulaXMax = (119 * escalaMapa) + centroX;

        if (nextX < tunelIzquierdoX && (pacmanY > tunelYMin && pacmanY < tunelYMax)) {
            nextX = tunelDerechoX - pacmanAncho;
        }
        else if (nextX > tunelDerechoX && (pacmanY > tunelYMin && pacmanY < tunelYMax)) {
            nextX = tunelIzquierdoX;
        }
        // Si Pac-Man intenta entrar a la jaula desde ARRIBA o ABAJO, detén su movimiento
        if (nextY < puertaJaulaY && nextY > (puertaJaulaY - 1) && direccionActual == ABAJO && pacmanX + pacmanAncho > puertaJaulaXMin && pacmanX < puertaJaulaXMax) {
            // Verificar si está dentro del rango de X de la puerta de la jaula
            //if (pacmanX + pacmanAncho > puertaJaulaXMin && pacmanX < puertaJaulaXMax) {
                // Ajustar posición o detener movimiento
                enMovimiento = false;
                return; // Salir de la función para evitar que Pac-Man avance
            
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