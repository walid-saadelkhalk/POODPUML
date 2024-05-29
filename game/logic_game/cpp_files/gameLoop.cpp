#include "./logic_game/hpp_files/gameLoop.hpp"
#include "graphic_game/hpp_files/pages.hpp"
#include "./logic_game/hpp_files/data.hpp"
#include "./logic_game/hpp_files/Grid.hpp"
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

// The main loop of the game
// It will handle the events and render the game based on the current state
// The main loop will call different functions to render the different pages of the game

void mainLoop(World& world, std::vector<Button*>& buttons, Player& player) {
    std::cout << "Game loop started!" << std::endl;



    bool stateChanged = true;
    bool levelSelected = false; 
    const int FPS = 60;
    const int frameDelay = 2000 / FPS;

    Uint32 frameStart;
    int frameTime;
    SDL_Event event;
    bool gameisrunning = true;

    std::vector<SDL_Texture*> gifFrames = world.loadGifFrames("assets/images/intro", 40); 

    int currentFrame = 0;
    Uint32 lastFrameTime = 0;
    const Uint32 frameInterval = 45; 

    // Load the matrix from the file
    std::vector<std::vector<int>> matrix = Grid::readMatrixFromFile("matrice.txt");
    if (matrix.empty()) {
        std::cerr << "Erreur: Impossible de lire la matrice depuis le fichier." << std::endl;
        return;
    }
    
    Grid grid(matrix[0].size(), matrix.size(), matrix);

    std::vector<SDL_Texture*> textures;
    for (int i = 0; i <= 6; ++i) {
        std::string path = "assets/images/" + std::to_string(i) + ".png";
        SDL_Texture* texture = world.loadTexture(path);
        if (texture) {
            textures.push_back(texture);
        }
    }
    //End of loading textures
    
    while (gameisrunning) {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    gameisrunning = false;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        int x = event.button.x;
                        int y = event.button.y;

                        if (world.getCurrentState() == State::Intro) {
                            if (buttons[0]->isClickedAtPosition(x, y)) {
                                buttons[0]->click();
                                world.switchState(State::Menu);
                                stateChanged = true;
                            }
                        } else if (world.getCurrentState() == State::Menu) {
                            if (buttons[2]->isClickedAtPosition(x, y)) {
                                buttons[2]->click();
                                world.switchState(State::Game);
                            } else if (buttons[3]->isClickedAtPosition(x, y)) {
                                buttons[3]->click();
                                world.switchState(State::Settings);
                            } else if (buttons[4]->isClickedAtPosition(x, y)) {
                                buttons[4]->click();
                                world.switchState(State::Score);
                            }

                        } else if (world.getCurrentState() == State::Settings) {
                            if (buttons[5]->isClickedAtPosition(x, y)) {
                                buttons[5]->click();
                                std::cout << "THE SHIRE" << std::endl;
                            } else if (buttons[6]->isClickedAtPosition(x, y)) {
                                buttons[6]->click();
                                std::cout << "MORDOR" << std::endl;
                            } else if (buttons[7]->isClickedAtPosition(x, y)) {
                                buttons[7]->click();
                                std::cout << "ON" << std::endl;
                            } else if (buttons[8]->isClickedAtPosition(x, y)) {
                                buttons[8]->click();
                                std::cout << "OFF" << std::endl;
                            } else if (buttons[1]->isClickedAtPosition(x, y)) {
                                buttons[1]->click();
                                world.switchState(State::Menu);
                            }
                        } else if (world.getCurrentState() == State::Score) {
                            if (buttons[1]->isClickedAtPosition(x, y)) {
                                buttons[1]->click();
                                world.switchState(State::Menu);
                            }
                        } else if (world.getCurrentState() == State::Game) {
                            if (buttons[1]->isClickedAtPosition(x, y)) {
                                buttons[1]->click();
                                world.switchState(State::Menu);
                                //create the first objectjson in the file
                                // json(player, 0, 0, 0);
                            }
                        }

                    }
                    break;

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_RETURN) {
                        State newState;
                        switch (world.getCurrentState()) {
                            case State::Intro:
                                newState = State::Menu;
                                break;
                            case State::Menu:
                                newState = State::Settings;
                                break;
                            case State::Settings:
                                newState = State::Game;
                                break;
                            case State::Game:
                                newState = State::Score;
                                break;
                            default:
                                newState = State::Intro;
                                break;
                        }
                        world.switchState(newState);
                        stateChanged = true;
                    }
                    break;
            }
        }

        // SDL_SetRenderDrawColor(world.getRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(world.getRenderer());

        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastFrameTime > frameInterval && currentFrame < gifFrames.size() - 1) {
            currentFrame++;
            lastFrameTime = currentTime;
        }

        switch (world.getCurrentState()) {
            case State::Intro:
                introPage(world, buttons, gifFrames, currentFrame);
                break;
            case State::Menu:
                menuPage(world, buttons);
                break;
            case State::Settings:
                settingsPage(world, buttons);
                break;
            case State::Score:
                scorePage(world, buttons);
                break;
            case State::Game:
                gamePage(world, buttons);
                grid.renderGrid(world.getRenderer(), textures);
                break;
            default:
                std::cerr << "État invalide !" << std::endl;
                break;
        }

        SDL_RenderPresent(world.getRenderer());

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    std::cout << "Game loop ended!" << std::endl;
}


