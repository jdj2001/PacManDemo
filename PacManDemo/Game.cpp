#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "Pacman.h"
#include "Mapa.h"
#include "Menu.h"
#include "TextureLoader.h"
#include "Fantasma.h"
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

unsigned int pacmanTexture;
unsigned int fantasmasTexture;
unsigned int fantasmasVulnerablesTexture;
unsigned int mapaTexture;
unsigned int mapaTexturePellets;
bool showEndLevelDialog = false;
bool showGameOverDialog = false;
bool isGamePaused = false;
bool isMusicPlaying = false;

float escalaMapa;
float centroX;
float centroY;

Mix_Music* intermissionMusic = nullptr;
//Mix_Chunk* movimientoFatasmas = nullptr;
Mix_Chunk* eatDotSound = nullptr;
Mix_Chunk* muertePacman = nullptr;
bool isLevelStarting = true;
Uint32 levelStartTime = 0;

float colorRojo[3] = { 1.0f, 0.0f, 0.0f };
float colorRosa[3] = { 255.0f / 255.0f, 183.0f / 255.0f, 255.0f / 255.0f };
float colorCyan[3] = { 0.0f, 255.0f / 255.0f, 255.0f / 255.0f };
float colorNaranja[3] = { 254.0f / 255.0f, 182.0f / 255.0f, 81.0f / 255.0f };

std::vector<Fantasma> fantasmas;

int posicionJaulaIndex = 0;


void initGame() {
    Uint32 tiempoInicio = SDL_GetTicks();

    fantasmas.clear();
    fantasmasTexture = loadTexture("C:/sprite_personajes.png");

    fantasmas.emplace_back(83.0f * escalaMapa + centroX, (mapaOriginalAlto - 99.0f) * escalaMapa + centroY, colorRojo, false, 0);
    fantasmas.emplace_back(91.0f * escalaMapa + centroX, (mapaOriginalAlto - 122.0f) * escalaMapa + centroY, colorRosa, true, tiempoInicio + 15000);//rosa
    fantasmas.emplace_back(106.0f * escalaMapa + centroX, (mapaOriginalAlto - 122.0f) * escalaMapa + centroY, colorCyan, true, tiempoInicio + 10000);//azul
    fantasmas.emplace_back(121.0f * escalaMapa + centroX, (mapaOriginalAlto - 122.0f) * escalaMapa + centroY, colorNaranja, true, tiempoInicio + 20000);//naranja

    fantasmasVulnerablesTexture = loadTexture("C:/sprite_personajes.png");

    showEndLevelDialog = false;
    isGamePaused = false;
    isLevelStarting = true;
    isMusicPlaying = false;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Error al inicializar SDL_mixer: " << Mix_GetError() << std::endl;
    }

    intermissionMusic = Mix_LoadMUS("D:/clases/Comp Grafica y Visual/II/PacManDemo/PacManDemo/PacManDemo/Arcade - Pac-Man - Sound Effects/intermission.wav");
    //movimientoFatasmas = Mix_LoadWAV("D:/clases/Comp Grafica y Visual/II/PacManDemo/PacManDemo/PacManDemo/Arcade - Pac-Man - Sound Effects/siren0.wav");

    muertePacman = Mix_LoadWAV("D:/clases/Comp Grafica y Visual/II/PacManDemo/PacManDemo/PacManDemo/Arcade - Pac-Man - Sound Effects/death_0.wav");

    eatDotSound = Mix_LoadWAV("D:/clases/Comp Grafica y Visual/II/PacManDemo/PacManDemo/PacManDemo/Arcade - Pac-Man - Sound Effects/eat_dot_0.wav");

    levelStartTime = SDL_GetTicks();

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

    initPacman(centroX, centroY, escalaMapa, true);
}

void mostrarVentanaFinDeNivel() {
    showEndLevelDialog = true;
    glutPostRedisplay();
}

void cleanupGame() {
    Mix_FreeMusic(intermissionMusic);
    Mix_FreeChunk(eatDotSound);
    //Mix_FreeChunk(movimientoFatasmas);
    Mix_CloseAudio();
}

void mostrarVentanaDerrota() {
    showGameOverDialog = true;
    glutPostRedisplay();
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawMapa();
    drawPellets();
    //drawPacman(pacmanTexture);

    if (isDying) {
        drawDeathAnim(pacmanTexture);
    }
    else {
        drawPacman(pacmanTexture);
    }

    for (auto& fantasma : fantasmas) {
        fantasma.draw();
        //fantasma.draw(fantasmasTexture);
    }

    renderizarPuntaje();
    renderizarVidas();

    if (!isMusicPlaying) {
        Mix_PlayMusic(intermissionMusic, 0);
        //Mix_PlayMusic(movimientoFatasmas, 0);
        isMusicPlaying = true;
    }
    Uint32 currentTime = SDL_GetTicks();
    if (isLevelStarting && (currentTime - levelStartTime < 5000)) {
        glPushAttrib(GL_CURRENT_BIT);
        //Mix_PlayMusic(intermissionMusic, 0);
        glColor3f(1.0f, 1.0f, 0.0f);
        renderizarTexto(800.0f, 500.0f, "�LISTO?");
        glPopAttrib();
        isGamePaused = true;
    }
    else {
        isLevelStarting = false;
        isGamePaused = false;
    }

    if (showEndLevelDialog) {
        isGamePaused = true;
        glPushAttrib(GL_CURRENT_BIT);


        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(620, 420);
        glVertex2f(1100, 420);
        glVertex2f(1100, 680);
        glVertex2f(620, 680);
        glEnd();


        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(620, 420);
        glVertex2f(1100, 420);
        glVertex2f(1100, 680);
        glVertex2f(620, 680);
        glEnd();


        glColor3f(1.0f, 1.0f, 0.0f);
        renderizarTexto(700.0f, 620.0f, "�Felicidades! Has ganado el nivel.");


        glColor3f(0.5f, 0.5f, 0.5f);
        glBegin(GL_QUADS);
        glVertex2f(650, 500);
        glVertex2f(850, 500);
        glVertex2f(850, 570);
        glVertex2f(650, 570);
        glEnd();
        glColor3f(1.0f, 1.0f, 1.0f);
        renderizarTexto(690.0f, 530.0f, "Volver a jugar");


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
    else if (showGameOverDialog) {
        isGamePaused = true;
        glPushAttrib(GL_CURRENT_BIT);

        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(620, 420);
        glVertex2f(1100, 420);
        glVertex2f(1100, 680);
        glVertex2f(620, 680);
        glEnd();

        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(620, 420);
        glVertex2f(1100, 420);
        glVertex2f(1100, 680);
        glVertex2f(620, 680);
        glEnd();

        glColor3f(1.0f, 1.0f, 0.0f);
        renderizarTexto(700.0f, 620.0f, "�Perdiste! �Suerte a la pr�xima!");

        glColor3f(0.5f, 0.5f, 0.5f);
        glBegin(GL_QUADS);
        glVertex2f(650, 500);
        glVertex2f(850, 500);
        glVertex2f(850, 570);
        glVertex2f(650, 570);
        glEnd();
        glColor3f(1.0f, 1.0f, 1.0f);
        renderizarTexto(690.0f, 530.0f, "Volver a jugar");

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

void reiniciarPosiciones() {
    //initPacman(centroX, centroY, escalaMapa);  
    initPacman(centroX, centroY, escalaMapa, false);
    Uint32 tiempoInicio = SDL_GetTicks();

    fantasmas.clear();
    fantasmas.emplace_back(83.0f * escalaMapa + centroX, (mapaOriginalAlto - 99.0f) * escalaMapa + centroY, colorRojo, false);
    fantasmas.emplace_back(90.0f * escalaMapa + centroX, (mapaOriginalAlto - 122.0f) * escalaMapa + centroY, colorRosa, true, tiempoInicio + 15000);
    fantasmas.emplace_back(105.0f * escalaMapa + centroX, (mapaOriginalAlto - 122.0f) * escalaMapa + centroY, colorCyan, true, tiempoInicio + 10000);
    fantasmas.emplace_back(120.0f * escalaMapa + centroX, (mapaOriginalAlto - 122.0f) * escalaMapa + centroY, colorNaranja, true, tiempoInicio + 20000);

    isLevelStarting = true;
    levelStartTime = SDL_GetTicks();
}

void pausarJuegoParaMuerte() {
    isGamePaused = true;
    Mix_HaltMusic();
    drawDeathAnim(pacmanTexture);
    if (!isDying) {
        reiniciarPosiciones();
        isGamePaused = false;
    }
}


void resetGame() {
    puntaje = 0;
    initMapa();
    initPellets();
    fantasmas.clear();
    Uint32 tiempoInicio = SDL_GetTicks();
    fantasmas.emplace_back(83.0f * escalaMapa + centroX, (mapaOriginalAlto - 99.0f) * escalaMapa + centroY, colorRojo, false);
    fantasmas.emplace_back(90.0f * escalaMapa + centroX, (mapaOriginalAlto - 122.0f) * escalaMapa + centroY, colorRosa, true, tiempoInicio + 15000);
    fantasmas.emplace_back(106.0f * escalaMapa + centroX, (mapaOriginalAlto - 122.0f) * escalaMapa + centroY, colorCyan, true, tiempoInicio + 10000);
    fantasmas.emplace_back(120.0f * escalaMapa + centroX, (mapaOriginalAlto - 122.0f) * escalaMapa + centroY, colorNaranja, true, tiempoInicio + 20000);
    initPacman(centroX, centroY, escalaMapa, true);
    for (auto& fantasma : fantasmas) {
        fantasma.draw();
    }

    showGameOverDialog = false;
    showEndLevelDialog = false;
    isGamePaused = false;
    isLevelStarting = true;

    levelStartTime = SDL_GetTicks();
    if (!isMusicPlaying) {
        Mix_PlayMusic(intermissionMusic, 0);
        //Mix_PlayMusic(movimientoFatasmas, 0);
        isMusicPlaying = true;
    }
    glutPostRedisplay();
}

void goToMainMenu() {
    std::cout << "Regresando al men� principal..." << std::endl;

    showEndLevelDialog = false;
    showGameOverDialog = false;
    gameStarted = false;

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

        if (gameX >= 650 && gameX <= 850 && gameY >= 500 && gameY <= 570) {
            Mix_HaltMusic();
            isMusicPlaying = false;
            fantasmas.clear();
            resetGame();
        }

        if (gameX >= 870 && gameX <= 1070 && gameY >= 500 && gameY <= 570) {
            Mix_PlayMusic(intermissionMusic, 0);
            //Mix_PlayMusic(movimientoFatasmas, 0);
            isMusicPlaying = true;
            goToMainMenu();
        }
    }
}

/*void updateGame() {
    Uint32 currentTime = SDL_GetTicks();
    if (!isGamePaused && (!isLevelStarting || (currentTime - levelStartTime >= 5000))) {
        updatePacman();
        checkPelletCollision();

        if (!isDying) {
            for (auto& fantasma : fantasmas) {
                fantasma.update();
                fantasma.checkSalida(currentTime);

                if (fantasma.isVulnerable() && fantasma.checkCollisionWithPacman(pacmanX, pacmanY, pacmanAncho, pacmanAlto)) {
                    puntaje += 200;  
                    fantasma.setEnJaula(true); 
                    //currentTime = 0;
                    fantasma.setVulnerable(false, currentTime);  
                    fantasma.posX = 106.0f * escalaMapa + centroX;
                    fantasma.posY = (mapaOriginalAlto - 122.0f) * escalaMapa + centroY;
                    continue;  

                }else if (!fantasma.isVulnerable() && fantasma.checkCollisionWithPacman(pacmanX, pacmanY, pacmanAncho, pacmanAlto)) {
                    loseLife();  
                    pausarJuegoParaMuerte();
                    return; 
                }
            }
        }
    }
}*/
void updateGame() {
    Uint32 currentTime = SDL_GetTicks();

    if (!isGamePaused && (!isLevelStarting || (currentTime - levelStartTime >= 5000))) {
        updatePacman();
        checkPelletCollision();

        if (!isDying) {
            for (auto& fantasma : fantasmas) {
                fantasma.update();
                fantasma.checkSalida(currentTime);

                if (fantasma.isVulnerable() && fantasma.checkCollisionWithPacman(pacmanX, pacmanY, pacmanAncho, pacmanAlto)) {
                    puntaje += 200;

                    float posicionesJaulaX[] = { 121.0f * escalaMapa + centroX, 106.0f * escalaMapa + centroX, 91.0f * escalaMapa + centroX };
                    float posicionX = posicionesJaulaX[posicionJaulaIndex % 3];
                    float posicionY = (mapaOriginalAlto - 122.0f) * escalaMapa + centroY;

                    fantasma.setEnJaula(true, currentTime);
                    fantasma.setVulnerable(false, currentTime);
                    fantasma.posX = posicionX;
                    fantasma.posY = posicionY;

                    posicionJaulaIndex++;

                    continue;
                }
                else if (!fantasma.isVulnerable() && fantasma.checkCollisionWithPacman(pacmanX, pacmanY, pacmanAncho, pacmanAlto)) {
                    loseLife();
                    pausarJuegoParaMuerte();
                    return;
                }
            }
        }
    }
}


void handleInput(unsigned char key) {
    if (!isGamePaused) {
        processPacmanInput(key);
    }
}