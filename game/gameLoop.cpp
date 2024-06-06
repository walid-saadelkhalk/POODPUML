#include "./gameLoop.hpp"
#include "./game.hpp"
#include "graphic_game/hpp_files/pages.hpp"
#include "logic_game/hpp_files/timer.hpp"
#include "logic_game/hpp_files/Wave.hpp"
#include "logic_game/hpp_files/InputBox.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void mainLoop(World& world, std::vector<Button*>& buttons, std::unique_ptr<Player>& player, Grid& grid) {
    std::cout << "Game loop started!" << std::endl;

    int waveNumber = 1;
    int enemiesPerWave = 10;
    int enemiesKilled = 0;
    int enemiesAtExit = 0;
    Wave wave(enemiesPerWave, grid.cells);

    bool stateChanged = true;
    bool levelSelected = false;
    const int FPS = 20;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;
    SDL_Event event;
    bool gameisrunning = true;

    std::vector<SDL_Texture*> gifFrames = world.loadGifFrames("assets/images/intro", 40);

    int currentFrame = 0;
    Uint32 lastFrameTime = 0;
    const Uint32 frameInterval = 45;

    Uint32 startTime = 0;
    Uint32 currentTime = 0;
    Uint32 elapsedTime = 0;
    bool resetTimer = true;

    InputBox inputBox(400, 300, 200, 50, world.getRenderer());

    while (gameisrunning) {
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
                                world.switchState(State::EnterName);
                                stateChanged = true;
                            }
                        } else if (world.getCurrentState() == State::EnterName) {
                            // Ne rien faire, l'entrée est gérée par le clavier
                        } else if (world.getCurrentState() == State::Menu) {
                            if (buttons[2]->isClickedAtPosition(x, y)) {
                                buttons[2]->click();
                                world.switchState(State::Game);
                                resetTimer = true;
                                startTime = SDL_GetTicks();
                                std::cout << "Starting game..." << std::endl;
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
                                elapsedTime = (SDL_GetTicks() - startTime) / 1000;
                            } else {
                                int cellWidth = 40;
                                int cellHeight = 40;

                                int xCell = x / cellWidth;
                                int yCell = y / cellHeight;
                                if (grid.isCellEmpty(xCell, yCell)) {
                                    player->addTower(xCell, yCell, world.getRenderer(), grid);
                                }
                            }
                        }
                    }
                    break;

                case SDL_KEYDOWN:
                    if (world.getCurrentState() == State::EnterName) {
                        if (event.key.keysym.sym == SDLK_RETURN) {
                            player->setName(inputBox.getText());
                            world.switchState(State::Menu);
                            stateChanged = true;
                        }
                    } else {
                        if (event.key.keysym.sym == SDLK_RETURN) {
                            State newState;
                            switch (world.getCurrentState()) {
                                case State::Intro:
                                    newState = State::EnterName;
                                    break;
                                case State::Menu:
                                    newState = State::Settings;
                                    break;
                                case State::Settings:
                                    newState = State::Game;
                                    resetTimer = true;
                                    startTime = SDL_GetTicks();
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
                    }
                    break;

                case SDL_TEXTINPUT:
                    if (world.getCurrentState() == State::EnterName) {
                        inputBox.handleEvent(&event);
                    }
                    break;

                case SDL_KEYUP:
                    if (world.getCurrentState() == State::EnterName && event.key.keysym.sym == SDLK_BACKSPACE) {
                        inputBox.handleEvent(&event);
                    }
                    break;
            }
        }

        currentTime = SDL_GetTicks();
        if (world.getCurrentState() == State::Game) {
            if (resetTimer) {
                startTime = SDL_GetTicks();
                resetTimer = false;
            }
            elapsedTime = (currentTime - startTime) / 1000;
        }

        SDL_RenderClear(world.getRenderer());

        currentTime = SDL_GetTicks();
        if (currentTime - lastFrameTime > frameInterval && currentFrame < gifFrames.size() - 1) {
            currentFrame++;
            lastFrameTime = currentTime;
        }

        // Mettre à jour la vague d'ennemis
        if (world.getCurrentState() == State::Game) {
            wave.update(currentTime, enemiesAtExit);
            if (wave.getEnemies().empty() && elapsedTime > 0) {
                waveNumber++;
                enemiesPerWave += 0;
                wave = Wave(enemiesPerWave, grid.cells);
                player->incrementTowers();
                resetTimer = true;
            }
            for (auto& tower : player->getTowers()) {
                tower->update(wave);
            }
        }

        switch (world.getCurrentState()) {
            case State::Intro:
                introPage(world, buttons, gifFrames, currentFrame);
                break;
            case State::EnterName:
                world.drawText("Enter your name:", 400, 250, 24);
                inputBox.render();
                break;
            case State::Menu:
                menuPage(world, buttons);
                elapsedTime = 0;
                break;
            case State::Settings:
                settingsPage(world, buttons);
                break;
            case State::Score:
                scorePage(world, buttons);
                break;
            case State::Game:
                frameStart = SDL_GetTicks();
                gamePage(world, buttons, waveNumber, *player);
                renderMatrix(world, grid, wave, *player);
                renderTimer(world, elapsedTime);
                if (wave.update(currentTime, enemiesAtExit)) {
                    int gameTime = elapsedTime;
                    std::cout << "End of game. Player: " << player->getName() << ", Time: " << gameTime << "s, Waves: " << waveNumber << std::endl; // Debug log
                    endGame(*player, grid, gameTime, false, waveNumber);
                    world.switchState(State::Menu);
                    resetGame(world, player, grid, wave);  // Réinitialiser le jeu en cas de défaite
                    waveNumber = 1;  // Reset wave number
                    enemiesPerWave = 10;  // Reset the number of enemies per wave
                    enemiesKilled = 0;
                    enemiesAtExit = 0;
                    std::cout << "Game reset complete. Returning to menu." << std::endl; // Debug log
                }
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
