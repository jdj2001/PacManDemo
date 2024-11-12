#include <GL/glew.h>
#include <GL/glut.h>
#include "Menu.h"
#include "Game.h"
#include "Mapa.h"
#include <iostream>

bool gameStarted = false; 
bool instructionsVisible = false;

void initMenu() {
    gameStarted; 
}

void drawCenteredText(float x, float y, const char* string, void* font) {
    float textWidth = 0;
    for (const char* c = string; *c != '\0'; c++) {
        textWidth += glutBitmapWidth(font, *c);
    }
    float centeredX = x - (textWidth / 2.0f);
    float centeredY = y - 10.0f;  

    glRasterPos2f(centeredX, centeredY);
    for (const char* c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void drawButton(float x, float y, float width, float height, const char* label) {
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y - height);
    glVertex2f(x, y - height);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    drawCenteredText(x + width / 2.0f, y - height / 2.0f, label, GLUT_BITMAP_HELVETICA_18);
}

void renderMenu() {
    glPushAttrib(GL_CURRENT_BIT);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 0.0);
    drawCenteredText(860.0f, 700.0f, "PAC-MAN", GLUT_BITMAP_TIMES_ROMAN_24);

    drawButton(760.0f, 500.0f, 200.0f, 50.0f, "Iniciar Juego");     
    drawButton(760.0f, 400.0f, 200.0f, 50.0f, "Instrucciones");    
    drawButton(760.0f, 300.0f, 200.0f, 50.0f, "Salir");            

    glPopAttrib();
    glFlush();
    glutSwapBuffers();
}

void renderInstructions() {
    glPushAttrib(GL_CURRENT_BIT);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 0.0);
    drawCenteredText(860.0f, 750.0f, "INSTRUCCIONES", GLUT_BITMAP_TIMES_ROMAN_24);

    drawCenteredText(860.0f, 650.0f, "Objetivo: Come todos los pellets sin ser atrapado por los fantasmas.", GLUT_BITMAP_HELVETICA_18);
    drawCenteredText(860.0f, 600.0f, "Controles: Usa la teclas w, s, a y d del teclado para mover a Pac-Man.", GLUT_BITMAP_HELVETICA_18);
    drawCenteredText(860.0f, 550.0f, "Pellets grandes: Vuelven vulnerables a los fantasmas temporalmente.", GLUT_BITMAP_HELVETICA_18);
    drawCenteredText(860.0f, 500.0f, "Vidas: Tienes 3 vidas. Pierdes una si un fantasma te atrapa.", GLUT_BITMAP_HELVETICA_18);

    drawButton(760.0f, 200.0f, 200.0f, 50.0f, "Regresar");

    glPopAttrib();
    glFlush();
    glutSwapBuffers();
}


void handleMenuMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float oglX = static_cast<float>(x);
        float oglY = 880.0f - static_cast<float>(y);

        if (!instructionsVisible) {
            // INICIAR JUEGO
            if (oglX >= 760 && oglX <= 960 && oglY >= 500 && oglY <= 550) {
                gameStarted = true;
                puntaje = 0;
                initGame();
            }
            // INSTRUCCIONES
            else if (oglX >= 760 && oglX <= 960 && oglY >= 400 && oglY <= 450) {
                instructionsVisible = true;
                glutPostRedisplay();
            }
            // SALIR DEL JUEGO
            else if (oglX >= 760 && oglX <= 960 && oglY >= 300 && oglY <= 350) {
                exit(0);
            }
        }
        else {
            if (oglX >= 760 && oglX <= 960 && oglY >= 200 && oglY <= 250) {
                instructionsVisible = false;
                glutPostRedisplay();
            }
        }
    }
}

