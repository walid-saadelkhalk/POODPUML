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

void menuPage(World& world, std::vector<Button*>& buttons) {
    SDL_Texture* bgMenuTexture = world.loadTexture("assets/images/menu_page.png");
    world.renderTexture(bgMenuTexture, 0, 0, 1500, 720);


    if (!buttons.empty()) {
        buttons[2]->draw();
        buttons[3]->draw();
        buttons[4]->draw();
    }

    SDL_DestroyTexture(bgMenuTexture);
    SDL_RenderPresent(world.getRenderer());
}