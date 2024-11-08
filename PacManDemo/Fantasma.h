#ifndef FANTASMA_H
#define FANTASMA_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>

struct Animacion {
    float texCoordLeft;
    float texCoordRight;
    float texCoordBottom;
    float texCoordTop;
};

class Fantasma {
public:
    Fantasma(float x, float y, const float color[3], bool enJaula, Uint32 tiempoSalida = 0);
    //Fantasma(float x, float y, const float color[3]);
    void initAnimaciones();
    void draw(GLuint textureID);
    void update();
    //void chooseDirection(float pacmanX, float pacmanY);  // Nueva función de persecución
    bool checkCollisionWithPacman(float pacmanX, float pacmanY, float pacmanAncho, float pacmanAlto);  
    void setEnJaula(bool enJaula); 
    void checkSalida(Uint32 tiempoActual);  
    //void changeDirection();

    //void colisiones();

    float posX, posY;
    float nextX = posX;
    float nextY = posY;
    int direccionActual;
    float color[3];
    bool enJaula;
    bool alcanzoSalida = false;  
    Uint32 tiempoSalida; 
    //Uint32 timeToExit = SDL_GetTicks();
    static const int fantasmaAncho = 44;
    static const int fantasmaAlto = 44;
    //bool isMovingToExit = false;
    

private:
    Animacion animaciones[4];  
    float speed = 2.0f;  
    Uint32 tiempoUltimoCambio = 0;
    bool enModoPersecucion = false;  
};

#endif