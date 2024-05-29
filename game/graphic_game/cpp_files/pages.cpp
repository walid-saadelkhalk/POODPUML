#include "../hpp_files/pages.hpp"

void cleanUpTextures(std::vector<SDL_Texture*>& textures) {
    for (SDL_Texture* texture : textures) {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }
    textures.clear();
}

void cleanUpButtons(std::vector<Button*>& buttons) {
    for (Button* button : buttons) {
        delete button; 
    }
    buttons.clear();
}

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


void settingsPage(World& world, std::vector<Button*>& buttons) {
    SDL_Texture* background = world.loadTexture("assets/images/settings.png");
    SDL_SetRenderDrawColor(world.getRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(world.getRenderer());

    if (background) {
        int width, height;
        SDL_QueryTexture(background, nullptr, nullptr, &width, &height);
        world.renderTexture(background, 0, 0, width, height);
    }

    if (!buttons.empty()) {
        buttons[1]->draw();
        buttons[5]->draw();
        buttons[6]->draw();
        buttons[7]->draw();
        buttons[8]->draw();
    }
    SDL_RenderPresent(world.getRenderer());

    if (background) {
        SDL_DestroyTexture(background);
    }
}

void scorePage(World& world, std::vector<Button*>& buttons) {
    SDL_Texture* background = world.loadTexture("assets/images/score.png");
    SDL_SetRenderDrawColor(world.getRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(world.getRenderer());

    if (background) {
        int width, height;
        SDL_QueryTexture(background, nullptr, nullptr, &width, &height);
        world.renderTexture(background, 0, 0, width, height);
    }

    if (!buttons.empty()) {
        buttons[1]->draw();

    }
    SDL_RenderPresent(world.getRenderer());

    if (background) {
        SDL_DestroyTexture(background);
    }
}

void gamePage(World& world, std::vector<Button*>& buttons) {
    SDL_Rect viewport;
    viewport.x = 1000;
    viewport.y = 0;
    viewport.w = 500;
    viewport.h = 720;
    SDL_RenderSetViewport(world.getRenderer(), &viewport);
    SDL_Texture* square = world.loadTexture("assets/images/1.png");
    SDL_SetRenderDrawColor(world.getRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(world.getRenderer());

    world.drawText("SHOP", 10, 10, 80);
    if (square) {
        world.renderTexture(square, 0, 100, 500, 100);
    }

    if (!buttons.empty()) {
        buttons[9]->draw();

    }

    if (square) {
        SDL_DestroyTexture(square);
    }
    SDL_RenderSetViewport(world.getRenderer(), nullptr);
}

void gamePage(World& world, std::vector<Button*>& buttons) {
    SDL_Rect viewport;
    viewport.x = 1000;
    viewport.y = 0;
    viewport.w = 500;
    viewport.h = 720;
    SDL_RenderSetViewport(world.getRenderer(), &viewport);
    SDL_Texture* square = world.loadTexture("assets/images/1.png");
    SDL_SetRenderDrawColor(world.getRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(world.getRenderer());

    world.drawText("SHOP", 10, 10, 80);
    if (square) {
        world.renderTexture(square, 0, 100, 500, 100);
    }

    if (!buttons.empty()) {
        buttons[9]->draw();

    }

    if (square) {
        SDL_DestroyTexture(square);
    }
    SDL_RenderSetViewport(world.getRenderer(), nullptr);
}


void gamePage(World& world, std::vector<Button*>& buttons) {
    SDL_SetRenderDrawColor(world.getRenderer(), 15, 16, 36, 255);
    SDL_RenderClear(world.getRenderer());

    if (!buttons.empty()) {
        buttons[1]->draw();
    }
    SDL_RenderPresent(world.getRenderer());
}