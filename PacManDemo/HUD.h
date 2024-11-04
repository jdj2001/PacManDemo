/*#ifndef HUD_H
#define HUD_H

#include <string>
#include <map>

class SoundManager {
public:
    SoundManager();
    ~SoundManager();
    void loadSound(const std::string& soundName, const std::string& filePath);  // Cargar un sonido
    void playSound(const std::string& soundName);  // Reproducir un sonido específico
    void stopAllSounds();  // Detener todos los sonidos (opcional)

private:
    std::map<std::string, unsigned int> soundMap;  // Mapa de sonidos cargados
    void initAudioSystem();  // Inicializa la librería de audio
    void closeAudioSystem(); // Libera los recursos de audio
};

#endif*/
