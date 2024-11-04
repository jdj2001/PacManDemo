#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "Pacman.h"
#include "Mapa.h"
#include "Menu.h"
#include "TextureLoader.h"
#include <iostream>
#include "HUD.h"
#include <SDL.h>
#include <SDL_mixer.h>

unsigned int pacmanTexture;
unsigned int mapaTexture;
unsigned int mapaTexturePellets;
bool showEndLevelDialog = false;
bool isGamePaused = false;
bool isMusicPlaying = false;

float escalaMapa;
float centroX;
float centroY;

Mix_Music* intermissionMusic = nullptr;
Mix_Chunk* eatDotSound = nullptr;
bool isLevelStarting = true;
Uint32 levelStartTime = 0;

void initGame() {
    showEndLevelDialog = false;  
    isGamePaused = false;
    isLevelStarting = true;
    isMusicPlaying = false;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Error al inicializar SDL_mixer: " << Mix_GetError() << std::endl;
    }

    intermissionMusic = Mix_LoadMUS("D:/clases/Comp Grafica y Visual/II/PacManDemo/PacManDemo/PacManDemo/Arcade - Pac-Man - Sound Effects/intermission.wav");
    eatDotSound = Mix_LoadWAV("D:/clases/Comp Grafica y Visual/II/PacManDemo/PacManDemo/PacManDemo/Arcade - Pac-Man - Sound Effects/eat_dot_0.wav");

    levelStartTime = SDL_GetTicks();
    
    //Mix_PlayMusic(intermissionMusic, 0);
    

    pacmanTexture = loadTexture("C:/sprite_personajes.png");
    mapaTexture = loadTexture("C:/mapa2.png");
    mapaTexturePellets = loadTexture("C:/mapa1.png");

    initMapa();
    initPellets();

    float ventanaAncho = 1720.0f;
    float ventanaAlto = 880.0f;
    float escalaX = ventanaAncho / 227.0f;
    float escalaY = ventanaAlto / 248.0f;
    escalaMapa = std::min(escalaX, escalaY);

    centroX = (ventanaAncho - mapaOriginalAncho * escalaMapa) / 2.0f;
    centroY = (ventanaAlto - mapaOriginalAlto * escalaMapa) / 2.0f;

    initPacman(centroX, centroY, escalaMapa);

    //isLevelStarting = true;
}

void mostrarVentanaFinDeNivel() {
    showEndLevelDialog = true;
    glutPostRedisplay();
}

void cleanupGame() {
    Mix_FreeMusic(intermissionMusic);
    Mix_FreeChunk(eatDotSound);
    Mix_CloseAudio();
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawMapa();
    drawPellets();
    drawPacman(pacmanTexture);
    renderizarPuntaje();

    if (!isMusicPlaying) {
        Mix_PlayMusic(intermissionMusic, 0);
        isMusicPlaying = true;
    }
    //Mix_PlayMusic(intermissionMusic, 0);
    Uint32 currentTime = SDL_GetTicks();
    if (isLevelStarting && (currentTime - levelStartTime < 5000)) {
        glPushAttrib(GL_CURRENT_BIT);
        //Mix_PlayMusic(intermissionMusic, 0);
        glColor3f(1.0f, 1.0f, 0.0f);
        renderizarTexto(800.0f, 440.0f, "¿LISTO?");
        glPopAttrib();
        isGamePaused = true;
    }
    else {
        isLevelStarting = false;
        isGamePaused = false;
    }
    //isMusicPlaying = false;
    if (showEndLevelDialog) {
        isGamePaused = true;
        glPushAttrib(GL_CURRENT_BIT);

        // Fondo ventana emergente
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(620, 420);
        glVertex2f(1100, 420);
        glVertex2f(1100, 680);
        glVertex2f(620, 680);
        glEnd();

        // Borde de la ventana
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(620, 420);
        glVertex2f(1100, 420);
        glVertex2f(1100, 680);
        glVertex2f(620, 680);
        glEnd();

        // Mensaje de finalización
        glColor3f(1.0f, 1.0f, 0.0f);
        renderizarTexto(700.0f, 620.0f, "¡Felicidades! Has ganado el nivel.");

        // Botón "Volver a jugar"
        glColor3f(0.5f, 0.5f, 0.5f);
        glBegin(GL_QUADS);
        glVertex2f(650, 500);
        glVertex2f(850, 500);
        glVertex2f(850, 570);
        glVertex2f(650, 570);
        glEnd();
        glColor3f(1.0f, 1.0f, 1.0f);
        renderizarTexto(690.0f, 530.0f, "Volver a jugar");

        // Botón "Regresar al menú"
        glColor3f(0.5f, 0.5f, 0.5f);
        glBegin(GL_QUADS);
        glVertex2f(870, 500);
        glVertex2f(1070, 500);
        glVertex2f(1070, 570);
        glVertex2f(870, 570);
        glEnd();
        glColor3f(1.0f, 1.0f, 1.0f);
        renderizarTexto(890.0f, 530.0f, "Regresar al menu");

        glPopAttrib();
        
    }

    glutSwapBuffers();
}

void resetGame() {
    puntaje = 0;
    initMapa();
    initPellets();
    initPacman(centroX, centroY, escalaMapa);

    showEndLevelDialog = false;
    isGamePaused = false;
    isLevelStarting = true;
    //isMusicPlaying = false;

    levelStartTime = SDL_GetTicks();
    if (!isMusicPlaying) {
        Mix_PlayMusic(intermissionMusic, 0);
        isMusicPlaying = true;
    }
    glutPostRedisplay();
}


void goToMainMenu() {
    //initMenu();
    std::cout << "Regresando al menú principal..." << std::endl;

    showEndLevelDialog = false; 
    gameStarted = false;         
    
    //isMusicPlaying = true;
    if (isMusicPlaying) {
        Mix_HaltMusic(); 
        isMusicPlaying = false;
    }
    glutPostRedisplay();
}

void mouseCallback(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float gameX = x;
        float gameY = 880 - y;

        std::cout << "Clic en: (" << gameX << ", " << gameY << ")" << std::endl;

        //VOLVER A JUGAR
        if (gameX >= 650 && gameX <= 850 && gameY >= 500 && gameY <= 570) {
            Mix_HaltMusic();  
            isMusicPlaying = false;
            resetGame();
        }

        // MENU
        if (gameX >= 870 && gameX <= 1070 && gameY >= 500 && gameY <= 570) {
            Mix_PlayMusic(intermissionMusic, 0);
            isMusicPlaying = true;
            goToMainMenu();
        }
    }
}

void updateGame() {
    Uint32 currentTime = SDL_GetTicks();
    if (!isGamePaused && (!isLevelStarting || (currentTime - levelStartTime >= 5000))) {
        updatePacman();
        checkPelletCollision();
    }
}

void handleInput(unsigned char key) {
    if (!isGamePaused) {
        processPacmanInput(key);
    }
}