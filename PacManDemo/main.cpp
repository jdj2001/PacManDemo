#include <Windows.h>
#include <GL/glew.h> 
#include <GL/glut.h>  
#include "Game.h"
#include <iostream>

void display() {
    renderScene();  
}

void update(int value) {
    updateGame();   
    glutPostRedisplay();  
    glutTimerFunc(16, update, 0);  
}

void keyboard(unsigned char key, int x, int y) {
    handleInput(key);  
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1720, 880);
    glutCreateWindow("Pac-Man Demo");

    glutInitWindowSize(1720, 880); 
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

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, update, 0);

    glutMainLoop();  

    return 0;
}
