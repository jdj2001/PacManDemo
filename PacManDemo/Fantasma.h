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
    void initAnimaciones();
    void draw();
    void update();
    bool checkCollisionWithPacman(float pacmanX, float pacmanY, float pacmanAncho, float pacmanAlto);

    void setVulnerable(bool vulnerable, Uint32 tiempoActual);
    bool isVulnerable() const;  

    void setEnJaula(bool enJaula, Uint32 tiempoActual);
    void checkSalida(Uint32 tiempoActual);

    float posX, posY;
    float nextX = posX;
    float nextY = posY;
    int direccionActual;
    float color[3];
    bool enJaula;
    bool alcanzoSalida = false;
    Uint32 tiempoSalida;
    static const int fantasmaAncho = 44;
    static const int fantasmaAlto = 44;
private:
    Animacion animaciones[4];
    float speed = 2.0f;
    Uint32 tiempoUltimoCambio = 0;
    bool enModoPersecucion = false;

    bool esVulnerable = false;  
    Uint32 tiempoVulnerable = 0;  

    bool vulnerable;
    Uint32 duracionVulnerable;

    GLuint texturaNormal;  
    GLuint texturaVulnerable;  
    GLuint texturaActual;
};

#endif