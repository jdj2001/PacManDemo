#ifndef FANTASMA_H
#define FANTASMA_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>

struct Animacion {
    float texCoordLeft;
    float texCoordRight;
    float texCoordBottom;
    float texCoordTop;
};

class Fantasma {
public:
    Fantasma(float x, float y, const float color[3]);
    void initAnimaciones();
    void draw(GLuint textureID);
    void update();

    float posX, posY;
    int direccionActual;
    float color[3];
    static const int fantasmaAncho = 46;
    static const int fantasmaAlto = 46;

private:
    Animacion animaciones[4];  
    float speed = 2.0f;        
};

#endif