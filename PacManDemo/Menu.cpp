/*#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include "menu.h"
#include "Game.h"
#include "Mapa.h"

bool gameStarted = false;

void initMenu() {
    gameStarted = false;
}

// Función para mostrar texto centrado en el botón
void drawCenteredText(float x, float y, const char* string, void* font) {
    float textWidth = 0;
    for (const char* c = string; *c != '\0'; c++) {
        textWidth += glutBitmapWidth(font, *c);
    }
    float centeredX = x - (textWidth / 500.0f);
    float centeredY = y - 0.03f;

    glRasterPos2f(centeredX, centeredY);
    for (const char* c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

// Función para dibujar un botón
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
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 0.0);
    renderizarTexto(860.0f, 700.0f, "PAC-MAN");
    drawButton(800.0f, 500.0f, 200.0f, 50.0f, "Start Game");
    drawButton(800.0f, 400.0f, 200.0f, 50.0f, "Instructions");
    drawButton(800.0f, 300.0f, 200.0f, 50.0f, "Exit");

    //glFlush();
    glutSwapBuffers();
}

// Función para dibujar la figura de Pac-Man
void drawPacMan(float x, float y, float radius) {
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int angle = 30; angle <= 330; angle += 10) {
        float theta = angle * 3.14159 / 180.0;
        glVertex2f(x + radius * cos(theta), y + radius * sin(theta));
    }
    glEnd();
}

// Dibuja el menú en pantalla
/*void renderMenu() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 0.0);
    drawCenteredText(-0.0f, 0.5f, "PAC-MAN", GLUT_BITMAP_TIMES_ROMAN_24);

    drawPacMan(0.0f, 0.2f, 0.15f);

    drawButton(-0.3f, -0.1f, 0.6f, 0.2f, "Start Game");
    drawButton(-0.3f, -0.35f, 0.6f, 0.2f, "Instructions");
    drawButton(-0.3f, -0.6f, 0.6f, 0.2f, "Exit");

    glFlush();
}

// Maneja las opciones seleccionadas
void selectOption(int option) {
    switch (option) {
    case 1:
        gameStarted = true;  // Cambiar al estado de juego
        initGame();
        break;
    case 2:
        std::cout << "Instructions selected" << std::endl;
        break;
    case 3:
        exit(0);  // Salir del programa
        break;
    }
    glutPostRedisplay();
}

void handleMenuMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float oglX = (float(x) / 1720.0f) * 2 - 1.0f;  // Convertir las coordenadas
        float oglY = 1.0f - (float(y) / 880.0f) * 2;

        // Detecta en qué botón se hizo clic
        if (oglY < 0.05f && oglY > -0.1f && oglX < 0.5f && oglX > -0.5f) {
            gameStarted = true;  // Cambiar al estado de juego
            initGame();          // Iniciar el juego
        }
        else if (oglY < -0.1f && oglY > -0.2f) {
            std::cout << "Instructions selected" << std::endl;
        }
        else if (oglY < -0.3f && oglY > -0.4f) {
            exit(0);
        }
    }
}
// Maneja clics del mouse en el menú
void handleMenuMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float oglX = (float(x) / 250.0f) - 1.0f;
        float oglY = 1.0f - (float(y) / 250.0f);

        if (oglY > -0.05f && oglY < 0.1f && oglX > -0.2f && oglX < 0.2f) {
            selectOption(1);
        }
        else if (oglY > -0.25f && oglY < -0.1f && oglX > -0.2f && oglX < 0.2f) {
            selectOption(2);
        }
        else if (oglY > -0.45f && oglY < -0.3f && oglX > -0.2f && oglX < 0.2f) {
            selectOption(3);
        }
    }
}

void displayGameIfStarted() {
    if (gameStarted) {
        renderScene();
    }
    else {
        renderMenu();
    }
}*/
