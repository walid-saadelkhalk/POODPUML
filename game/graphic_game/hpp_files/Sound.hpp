#ifndef SOUND_HPP
#define SOUND_HPP

#include <SDL2/SDL_mixer.h>
#include <string>

class Sound {
public:
    // Static method to get the unique instance of the class
    static Sound& getInstance();

    // Method to play music
    void playMusic(const std::string& filePath);

    // Method to stop music
    void stopMusic();

private:
    // Private constructor to prevent direct instantiation
    Sound();

    // Undefine copy constructor and assignment operator
    Sound(const Sound&) = delete;
    Sound& operator=(const Sound&) = delete;

    // Destructor to clean up resources
    ~Sound();

    // Pointer to the music
    Mix_Music* music;
};

#endif
