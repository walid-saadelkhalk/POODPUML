#include "../hpp_files/pages.hpp"

void introPage(World& world, std::vector<Button*>& buttons, std::vector<SDL_Texture*>& gifFrames, int currentFrame) {
    SDL_SetRenderDrawColor(world.getRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(world.getRenderer());

    if (!gifFrames.empty()) {
        SDL_Texture* currentTexture = gifFrames[currentFrame];
        world.renderTexture(currentTexture, 0, 0, 1500, 720);
    }

    world.drawText("YOU", 50, 300, 100);
    world.drawText("SHALL", 140, 400, 100);
    world.drawText("NOT", 230, 500, 100);
    world.drawText("PASS", 320, 600, 100);

    if (!buttons.empty()) {
        buttons[0]->draw();
    }
    SDL_RenderPresent(world.getRenderer());
}

void menuPage(World& world, std::vector<Button*>& buttons, bool& levelSelected) {
    SDL_SetRenderDrawColor(world.getRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(world.getRenderer());

    world.drawText("PARK", 620, 10, 100);
    world.drawText("AND", 850, 60, 100);
    world.drawText("FURIOUS", 1050, 110, 100);
    world.drawText("Choose your Level", 30, 400, 60);

    if (!buttons.empty()) {
        for (size_t i = 2; i < buttons.size(); ++i) {
            buttons[i]->draw();
        }

        if (levelSelected) {
            buttons[1]->draw(); 
        }
    }
    SDL_RenderPresent(world.getRenderer());
}