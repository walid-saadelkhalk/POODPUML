#include "./logic_game/hpp_files/timer.hpp"
#include <iostream>

void renderTimer(World& world, Uint32 elapsedTime) {
    if (TTF_WasInit() == 0) {
        TTF_Init();
    }

    TTF_Font* font = TTF_OpenFont("assets/font/MorrisRoman-Black.TTF", 24);
    if (!font) {
        std::cerr << "Erreur de chargement de la police : " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Color color = {255, 255, 255};
    std::string timeText = "Temps : " + std::to_string(elapsedTime) + "s";
    SDL_Surface* surface = TTF_RenderText_Solid(font, timeText.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(world.getRenderer(), surface);

    SDL_Rect dstRect = {1300, 200, surface->w, surface->h};

    SDL_RenderCopy(world.getRenderer(), texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}
