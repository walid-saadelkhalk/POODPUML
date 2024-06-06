#include "../hpp_files/Sound.hpp"
#include <iostream>


// Initialisation de l'instance unique
Sound& Sound::getInstance() {
    static Sound instance;
    return instance;
}

// Constructeur privé
Sound::Sound() : music(nullptr) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Erreur lors de l'initialisation de SDL_mixer: " << Mix_GetError() << std::endl;
    }
}

// Destructeur pour nettoyer les ressources
Sound::~Sound() {
    if (music != nullptr) {
        Mix_FreeMusic(music);
    }
    Mix_CloseAudio();
}

// Méthode pour jouer une musique
void Sound::playMusic(const std::string& filePath) {
    if (music != nullptr) {
        Mix_FreeMusic(music);
    }
    music = Mix_LoadMUS(filePath.c_str());
    if (music == nullptr) {
        std::cerr << "Erreur lors du chargement de la musique: " << Mix_GetError() << std::endl;
    } else {
        Mix_PlayMusic(music, -1);
    }
}

// Méthode pour arrêter la musique
void Sound::stopMusic() {
    Mix_HaltMusic();
    if (music != nullptr) {
        Mix_FreeMusic(music);
        music = nullptr;
    }
}
