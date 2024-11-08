#include <Windows.h>
#include <GL/glew.h> 
#include <GL/glut.h>  
#include "Game.h"
#include "Menu.h"
#include <iostream>
#include "Mapa.h"
#include "Fantasma.h"

void display() {
    //renderScene();  
    if (gameStarted) {
        renderScene(); 
        
    }
    else {
        renderMenu();   
    }
}

void update(int value) {
    if (gameStarted) {
        updateGame();  
    }
    glutPostRedisplay();  
    glutTimerFunc(16, update, 0);  
}

void keyboard(unsigned char key, int x, int y) {
    if (gameStarted) {
        handleInput(key); 
    }
}

void mouseClick(int button, int state, int x, int y) {
    if (gameStarted) {
        mouseCallback(button, state, x, y);
    }
    else {
        handleMenuMouse(button, state, x, y); 
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1720, 880);
    glutCreateWindow("Pac-Man Demo");

    glViewport(0, 0, 1720, 880);   
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1720.0, 0.0, 880.0); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLenum err = glewInit(); 
    if (GLEW_OK != err) {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
        return -1;
    }

    initGame();  
    // Definir el array de tiempos de salida
    //Uint32 tiemposSalida[3] = { 1000, 2000, 3000 };  // Ejemplo de tiempos de salida

    // Crear un objeto de la clase Fantasma con esos tiempos de salida
    //Fantasma fantasma(10.0f, 20.0f, { 1.0f, 0.0f, 0.0f }, true, tiemposSalida);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, update, 0);
    glutMouseFunc(mouseClick);
    //glutMouseFunc(mouseCallback);

    glutMainLoop();  

    cleanupGame();

    return 0;
}
