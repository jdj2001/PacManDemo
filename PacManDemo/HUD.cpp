#include "HUD.h"
#include <iostream>

// Incluir la biblioteca de audio según la que elijas, por ejemplo, SDL_mixer
//#include <SDL_mixer.h>

SoundManager::SoundManager() {
    initAudioSystem();  // Inicializa el sistema de audio al crear el gestor de sonido
}

SoundManager::~SoundManager() {
    closeAudioSystem();  // Libera los recursos al destruir el gestor de sonido
}

void SoundManager::initAudioSystem() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Error inicializando el sistema de audio: " << Mix_GetError() << std::endl;
    }
}

void SoundManager::closeAudioSystem() {
    for (auto& pair : soundMap) {
        Mix_FreeChunk(reinterpret_cast<Mix_Chunk*>(pair.second));
    }
    soundMap.clear();
    Mix_CloseAudio();
}

void SoundManager::loadSound(const std::string& soundName, const std::string& filePath) {
    Mix_Chunk* sound = Mix_LoadWAV(filePath.c_str());
    if (sound == nullptr) {
        std::cerr << "Error cargando sonido " << filePath << ": " << Mix_GetError() << std::endl;
    }
    else {
        soundMap[soundName] = reinterpret_cast<unsigned int>(sound);  // Almacena el sonido
    }
}

void SoundManager::playSound(const std::string& soundName) {
    auto it = soundMap.find(soundName);
    if (it != soundMap.end()) {
        Mix_PlayChannel(-1, reinterpret_cast<Mix_Chunk*>(it->second), 0);  // Reproduce el sonido una vez
    }
    else {
        std::cerr << "Sonido no encontrado: " << soundName << std::endl;
    }
}

void SoundManager::stopAllSounds() {
    Mix_HaltChannel(-1);  // Detiene todos los canales de sonido
}
