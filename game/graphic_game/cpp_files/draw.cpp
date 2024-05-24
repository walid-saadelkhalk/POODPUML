#include "../hpp_files/World.hpp"
#include <iostream>

void World::drawText(const std::string &text, int x, int y, int size) {
    TTF_Font* font = TTF_OpenFont("assets/font/MorrisRoman-Black.ttf", size);

    if (font == nullptr) {
        std::cerr << "Erreur lors du chargement de la police : " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Color textColor = {255, 255, 255}; 

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);

    if (textSurface == nullptr) {
        std::cerr << "Erreur lors de la création de la surface de texte : " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    if (textTexture == nullptr) {
        std::cerr << "Erreur lors de la création de la texture de texte : " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        return;
    }

    int textWidth = textSurface->w;
    int textHeight = textSurface->h;

    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);

    SDL_Rect dstRect = {x, y, textWidth, textHeight};
    SDL_RenderCopy(renderer, textTexture, nullptr, &dstRect);
    SDL_DestroyTexture(textTexture);
}

SDL_Texture* World::loadTexture(const std::string &file) {
    SDL_Texture* newTexture = IMG_LoadTexture(renderer, file.c_str());
    if (newTexture == nullptr) {
        std::cerr << "Erreur lors du chargement de l'image " << file << " : " << IMG_GetError() << std::endl;
    } else {
        std::cout << "Image chargée avec succès : " << file << std::endl;
    }
    return newTexture;
}

void World::renderTexture(SDL_Texture* tex, int x, int y, int w, int h) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(renderer, tex, NULL, &dst);
}

std::vector<SDL_Texture*> World::loadGifFrames(const std::string &path, int frameCount) {
    std::vector<SDL_Texture*> frames;
    for (int i = 0; i < frameCount; ++i) {
        std::string framePath = path + "/intro_" + (i < 10 ? "00" : (i < 100 ? "0" : "")) + std::to_string(i) + ".png";
        SDL_Texture* frame = loadTexture(framePath);
        if (frame != nullptr) {
            frames.push_back(frame);
        } else {
            std::cerr << "Erreur lors du chargement de la frame : " << framePath << std::endl;
        }
    }
    return frames;
}
