#include "../hpp_files/pages.hpp"
#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include "../hpp_files/Sound.hpp"
#include <string>

#include <string>

extern std::string menuBackgroundPath;

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
    SDL_Texture* bgMenuTexture = world.loadTexture(menuBackgroundPath.c_str());
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

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            int x = event.button.x;
            int y = event.button.y;

            if (buttons[5]->isClickedAtPosition(x, y)) {
                buttons[5]->click();
                menuBackgroundPath = "assets/images/menu_page2.png";
                std::cout << "THE SHIRE" << std::endl;
                world.switchState(State::Menu);
            } else if (buttons[6]->isClickedAtPosition(x, y)) {
                buttons[6]->click();
                menuBackgroundPath = "assets/images/menu_page.png";
                std::cout << "MORDOR" << std::endl;
                world.switchState(State::Menu);
            } else if (buttons[7]->isClickedAtPosition(x, y)) {
                buttons[7]->click();
                Sound::getInstance().playMusic("assets/song/gameSong.mp3");
                std::cout << "ON" << std::endl;
                world.switchState(State::Menu);
            } else if (buttons[8]->isClickedAtPosition(x, y)) {
                buttons[8]->click();
                Sound::getInstance().stopMusic();
                std::cout << "OFF" << std::endl;
                world.switchState(State::Menu);
            } else if (buttons[1]->isClickedAtPosition(x, y)) {
                buttons[1]->click();
                world.switchState(State::Menu);
            }
        }
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

    std::ifstream i("data.json");
    nlohmann::json j;
    i >> j;
    
    // Sort the array in descending order based on the score
    std::sort(j.begin(), j.end(), [](const nlohmann::json& a, const nlohmann::json& b) {
        return a["wave"].get<int>() > b["wave"].get<int>();
    });
    
    int y_offset = 100;
    int count = 1;
    
    // Display only the top 10 scores
    for(const auto& joueur : j) {
        if (joueur["nom"] == "Sam Gamgeez") {
            world.drawText(count == 1 ? "1st" : std::to_string(count), 620, y_offset, 40);
            world.drawText("Death : " + std::to_string(static_cast<int>(joueur["death"])), 730, y_offset, 40);
            world.drawText("Wave : " + std::to_string(static_cast<int>(joueur["wave"])), 980, y_offset, 40);
            world.drawText("Time : " + std::to_string(static_cast<int>(joueur["time"])), 1230, y_offset, 40);
            y_offset += 55;
            count++;
            if (count >= 11) {
                break;
            }
        }
    }

    SDL_RenderPresent(world.getRenderer());

    if (background) {
        SDL_DestroyTexture(background);
    }
}

void gamePage(World& world, std::vector<Button*>& buttons, int waveNumber, std::unique_ptr<Player>& player, Player& players) {  
    SDL_Rect viewport;
    viewport.x = 1000;
    viewport.y = 0;
    viewport.w = 500;
    viewport.h = 720;
    std::string playerName = player->getName();
    SDL_RenderSetViewport(world.getRenderer(), &viewport);

    SDL_SetRenderDrawColor(world.getRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(world.getRenderer());

    world.drawText("DATA", 10, 10, 80);
    world.drawText("Player: " + playerName, 40, 150, 40);
    world.drawText("Wave: " + std::to_string(waveNumber), 40, 350, 40);
    world.drawText("EKIA: compteur a mettre ici", 40, 450, 40);
    world.drawText("Towers level: mettre logique", 40, 550, 40);    
    world.drawText("Towers available: " + std::to_string(players.getNumTowers()), 40, 650, 40);
    if (!buttons.empty()) {
        buttons[9]->draw();
    }

    SDL_RenderSetViewport(world.getRenderer(), nullptr);
}

