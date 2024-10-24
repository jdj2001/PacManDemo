#include "Pacman.h"
#include "Game.h"

float pacmanX = 0.0f;  
float pacmanY = 0.0f;  
float pacmanSpeed = 10.0f;  

void initPacman(float centroX, float centroY, float escalaMapa) {
    pacmanX = centroX + 111.0f * escalaMapa;
    pacmanY = centroY + 133.0f * escalaMapa;
}

void drawPacman(GLuint textureID) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    float texCoordLeft = 19.0f / 226.0f;
    float texCoordRight = (30.0f + 1.0f) / 226.0f;
    float texCoordBottom = (13.0f + 1.0f) / 248.0f;
    float texCoordTop = 1.0f / 248.0f;

    float pacmanAncho = 42.0f;
    float pacmanAlto = 42.0f;

    glBegin(GL_QUADS);
    glTexCoord2f(texCoordLeft, texCoordBottom); glVertex2f(pacmanX, pacmanY);
    glTexCoord2f(texCoordRight, texCoordBottom); glVertex2f(pacmanX + pacmanAncho, pacmanY);
    glTexCoord2f(texCoordRight, texCoordTop); glVertex2f(pacmanX + pacmanAncho, pacmanY + pacmanAlto);
    glTexCoord2f(texCoordLeft, texCoordTop); glVertex2f(pacmanX, pacmanY + pacmanAlto);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void updatePacman() {
    
}

void processPacmanInput(unsigned char key) {
    float nextX = pacmanX;
    float nextY = pacmanY;

    if (key == 'w') nextY += pacmanSpeed;
    if (key == 's') nextY -= pacmanSpeed;
    if (key == 'a') nextX -= pacmanSpeed;
    if (key == 'd') nextX += pacmanSpeed;

    pacmanX = nextX;
    pacmanY = nextY;
}


