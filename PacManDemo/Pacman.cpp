#include "Pacman.h"
#include "Game.h"
#include "Mapa.h"

float pacmanX = 0.0f;
float pacmanY = 0.0f;
float pacmanSpeed = 4.0f;  // Velocidad de Pacman
float pacmanAncho = 46.2f;
float pacmanAlto = 46.2f;

enum Direccion { DERECHA, IZQUIERDA, ARRIBA, ABAJO };
Direccion direccionActual = DERECHA;
bool enMovimiento = false;  // Si Pacman est� en movimiento

// �ndice para la animaci�n del ciclo
int animacionIndex = 0;
int animacionDelay = 40;  // Tiempo en milisegundos entre animaciones
float lastAnimacionTime = 0;  // �ltimo tiempo en el que se cambi� la animaci�n

// Posiciones de las animaciones dentro del sprite
struct Animacion {
    float texCoordLeft;
    float texCoordRight;
    float texCoordBottom;
    float texCoordTop;
};

Animacion pacmanAnimaciones[3][4];  // 3 animaciones, 4 direcciones

void initAnimaciones() {
    // Configuraci�n para la animaci�n de cada direcci�n:
    // Boca cerrada (primera animaci�n)
    pacmanAnimaciones[0][DERECHA] = { 35.0f / 226.0f, (35.0f + 13.0f) / 226.0f, (1.0f + 13.0f) / 248.0f, 1.0f / 248.0f };
    pacmanAnimaciones[0][IZQUIERDA] = pacmanAnimaciones[0][DERECHA];  // Mirror para izquierda
    pacmanAnimaciones[0][ARRIBA] = pacmanAnimaciones[0][DERECHA];     // Tambi�n reutilizamos boca cerrada para arriba
    pacmanAnimaciones[0][ABAJO] = pacmanAnimaciones[0][DERECHA];      // Y para abajo

    // Boca abierta normal (segunda animaci�n)
    pacmanAnimaciones[1][DERECHA] = { 19.0f / 226.0f, (19.0f + 12.0f) / 226.0f, (1.0f + 13.0f) / 248.0f, 1.0f / 248.0f };
    pacmanAnimaciones[1][IZQUIERDA] = { (19.0f + 12.0f) / 226.0f, 19.0f / 226.0f, (1.0f + 13.0f) / 248.0f, 1.0f / 248.0f };  // Mirror
    pacmanAnimaciones[1][ARRIBA] = { 19.0f / 226.0f, (19.0f + 13.0f) / 226.0f, (34.0f + 12.0f) / 248.0f, 34.0f / 248.0f };
    pacmanAnimaciones[1][ABAJO] = { 19.0f / 226.0f, (19.0f + 13.0f) / 226.0f, 34.0f / 248.0f, (34.0f + 12.0f) / 248.0f };   // Mirror

    // Boca muy abierta (tercera animaci�n)
    pacmanAnimaciones[2][DERECHA] = { 3.0f / 226.0f, (3.0f + 9.0f) / 226.0f, (1.0f + 13.0f) / 248.0f, 1.0f / 248.0f };
    pacmanAnimaciones[2][IZQUIERDA] = { (3.0f + 9.0f) / 226.0f, 3.0f / 226.0f, (1.0f + 13.0f) / 248.0f, 1.0f / 248.0f };  // Mirror
    pacmanAnimaciones[2][ARRIBA] = { 3.0f / 226.0f, (3.0f + 13.0f) / 226.0f, (37.0f + 9.0f) / 248.0f, 37.0f / 248.0f };
    pacmanAnimaciones[2][ABAJO] = { 3.0f / 226.0f, (3.0f + 13.0f) / 226.0f, 37.0f / 248.0f, (37.0f + 9.0f) / 248.0f };     // Mirror
}

void initPacman(float centroX, float centroY, float escalaMapa) {
    pacmanX = centroX + 106.0f * escalaMapa;
    pacmanY = centroY + 101.5f * escalaMapa;

    // Inicializar animaciones
    initAnimaciones();
}

void drawPacman(GLuint textureID) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Obtener la animaci�n actual seg�n la direcci�n y el �ndice de animaci�n
    Animacion currentAnim = pacmanAnimaciones[animacionIndex][direccionActual];

    glBegin(GL_QUADS);
    glTexCoord2f(currentAnim.texCoordLeft, currentAnim.texCoordBottom); glVertex2f(pacmanX, pacmanY);
    glTexCoord2f(currentAnim.texCoordRight, currentAnim.texCoordBottom); glVertex2f(pacmanX + pacmanAncho, pacmanY);
    glTexCoord2f(currentAnim.texCoordRight, currentAnim.texCoordTop); glVertex2f(pacmanX + pacmanAncho, pacmanY + pacmanAlto);
    glTexCoord2f(currentAnim.texCoordLeft, currentAnim.texCoordTop); glVertex2f(pacmanX, pacmanY + pacmanAlto);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

// Actualizar la animaci�n del Pacman
void updatePacmanAnimacion() {
    float currentTime = glutGet(GLUT_ELAPSED_TIME);
    if (currentTime - lastAnimacionTime > animacionDelay) {
        // Cambiar el estado de la animaci�n c�clicamente
        animacionIndex = (animacionIndex + 1) % 3;  // 0 = cerrado, 1 = abierto normal, 2 = muy abierto
        lastAnimacionTime = currentTime;
    }
}

// Actualizar la posici�n de Pacman y la animaci�n
void updatePacman() {
    if (enMovimiento) {
        updatePacmanAnimacion();
        float nextX = pacmanX;
        float nextY = pacmanY;

        // Movimiento seg�n la direcci�n
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

        // Verificar colisiones antes de actualizar la posici�n
        if (!checkCollision(nextX, nextY, pacmanAncho, pacmanAlto)) {
            pacmanX = nextX;
            pacmanY = nextY;
        }
        else {
            enMovimiento = false;  // Si colisiona, detener el movimiento
        }
    }
}

void processPacmanInput(unsigned char key) {
    // Antes de cambiar la direcci�n, verificamos si hay colisiones en esa direcci�n
    float nextX = pacmanX;
    float nextY = pacmanY;

    switch (key) {
    case 'd':  // Derecha
        nextX += pacmanSpeed;
        if (!checkCollision(nextX, pacmanY, pacmanAncho, pacmanAlto)) {
            direccionActual = DERECHA;
            enMovimiento = true;
        }
        break;
    case 'a':  // Izquierda
        nextX -= pacmanSpeed;
        if (!checkCollision(nextX, pacmanY, pacmanAncho, pacmanAlto)) {
            direccionActual = IZQUIERDA;
            enMovimiento = true;
        }
        break;
    case 'w':  // Arriba
        nextY += pacmanSpeed;
        if (!checkCollision(pacmanX, nextY, pacmanAncho, pacmanAlto)) {
            direccionActual = ARRIBA;
            enMovimiento = true;
        }
        break;
    case 's':  // Abajo
        nextY -= pacmanSpeed;
        if (!checkCollision(pacmanX, nextY, pacmanAncho, pacmanAlto)) {
            direccionActual = ABAJO;
            enMovimiento = true;
        }
        break;
    }
}