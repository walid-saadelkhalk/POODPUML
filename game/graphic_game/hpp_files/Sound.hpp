#ifndef SOUND_HPP
#define SOUND_HPP

#include <SDL2/SDL_mixer.h>
#include <string>

class Sound {
public:
    // Méthode statique pour obtenir l'instance unique de Sound
    static Sound& getInstance();

    // Méthode pour jouer une musique
    void playMusic(const std::string& filePath);

    // Méthode pour arrêter la musique
    void stopMusic();

private:
    // Constructeur privé pour empêcher l'instanciation directe
    Sound();

    // Déclaration mais non définition pour empêcher la copie et l'affectation
    Sound(const Sound&) = delete;
    Sound& operator=(const Sound&) = delete;

    // Destructeur pour nettoyer les ressources
    ~Sound();

    // Pointeur vers la musique en cours
    Mix_Music* music;
};

#endif // SOUND_HPP
