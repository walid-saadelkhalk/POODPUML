#include "gameLoop.hpp"
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

// The main loop of the game
// It will handle the events and render the game based on the current state
// The main loop will call different functions to render the different pages of the game

void mainLoop(Window& window, std::vector<Button*>& buttons) {
    std::cout << "Game loop started!" << std::endl;

    bool stateChanged = true;
    bool levelSelected = false; 
    const int FPS = 60;
    const int frameDelay = 2000 / FPS;

    Uint32 frameStart;
    int frameTime;
    SDL_Event event;
    bool gameisrunning = true;

    std::vector<SDL_Texture*> gifFrames = window.loadGifFrames("assets/images", 40); 

    int currentFrame = 0;
    Uint32 lastFrameTime = 0;
    const Uint32 frameInterval = 50; 

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

                        if (window.getCurrentState() == State::Intro) {
                            if (buttons[0]->isClickedAtPosition(x, y)) {
                                buttons[0]->click();
                                window.switchState(State::Menu);
                                stateChanged = true;
                            }
                        } else if (window.getCurrentState() == State::Menu) {
                            for (size_t i = 1; i < buttons.size(); ++i) {
                                if (buttons[i]->isClickedAtPosition(x, y)) {
                                    buttons[i]->click();
                                    if (i == 1) {  
                                        window.switchState(State::Settings);
                                        stateChanged = true;
                                    } else {
                                        levelSelected = true; 
                                    }
                                }
                            }
                        }
                    }
                    break;

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_RETURN) {
                        State newState;
                        switch (window.getCurrentState()) {
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
                        window.switchState(newState);
                        stateChanged = true;
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
        SDL_RenderClear(window.renderer);

        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastFrameTime > frameInterval && currentFrame < gifFrames.size() - 1) {
            currentFrame++;
            lastFrameTime = currentTime;
        }

        switch (window.getCurrentState()) {
            case State::Intro:
                introPage(window, buttons, gifFrames, currentFrame);
                break;
            case State::Menu:
                menuPage(window, buttons, levelSelected);
                break;
            case State::Settings:
                if (stateChanged) {
                    SDL_RenderClear(window.renderer);
                    stateChanged = false;
                }
                break;
            default:
                std::cerr << "État invalide !" << std::endl;
                break;
        }

        SDL_RenderPresent(window.renderer);

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    std::cout << "Game loop ended!" << std::endl;
}

void introPage(Window& window, std::vector<Button*>& buttons, std::vector<SDL_Texture*>& gifFrames, int currentFrame) {
    SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
    SDL_RenderClear(window.renderer);

    if (!gifFrames.empty()) {
        SDL_Texture* currentTexture = gifFrames[currentFrame];
        window.renderTexture(currentTexture, 0, 0, 1500, 720);
    }

    window.drawText("YOU", 50, 300, 100);
    window.drawText("SHALL", 140, 400, 100);
    window.drawText("NOT", 230, 500, 100);
    window.drawText("PASS", 320, 600, 100);

    if (!buttons.empty()) {
        buttons[0]->draw();
    }
    SDL_RenderPresent(window.renderer);
}

void menuPage(Window& window, std::vector<Button*>& buttons, bool& levelSelected) {
    SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
    SDL_RenderClear(window.renderer);

    window.drawText("PARK", 620, 10, 100);
    window.drawText("AND", 850, 60, 100);
    window.drawText("FURIOUS", 1050, 110, 100);
    window.drawText("Choose your Level", 30, 400, 60);

    if (!buttons.empty()) {
        for (size_t i = 2; i < buttons.size(); ++i) {
            buttons[i]->draw();
        }

        if (levelSelected) {
            buttons[1]->draw(); 
        }
    }
    SDL_RenderPresent(window.renderer);
}
