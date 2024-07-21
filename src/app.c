#include "app.h"
#include "menu.h"
#include <stdio.h>
#include <string.h>

void initApp(VisualizerApp* app, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! TTF_Error: %s\n", TTF_GetError());
        exit(1);
    }

    app->window = SDL_CreateWindow("AlgoViz 0.1",
                                   SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   width, height,
                                   SDL_WINDOW_SHOWN);
    if (app->window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED);
    if (app->renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    app->font = TTF_OpenFont("C:/Users/vlad_/CLionProjects/AlgoViz/assets/fonts/DIN_Regular.ttf", 24);
    if (app->font == NULL) {
        printf("Failed to load font! TTF_Error: %s\n", TTF_GetError());
        exit(1);
    }

    app->state = MAIN_MENU_STATE;
    app->windowWidth = width;
    app->windowHeight = height;
    app->selectedDataStructure = NULL;
    app->selectedAlgorithm = NULL;

    // Add buttons to the menu
    int buttonWidth = 300;
    int buttonHeight = 60;
    int startY = (height - (3 * buttonHeight + 2 * 20)) / 2;  // Center vertically

    addButton(app, (width - buttonWidth) / 2, startY, buttonWidth, buttonHeight, "Start Visualization");
    addButton(app, (width - buttonWidth) / 2, startY + buttonHeight + 20, buttonWidth, buttonHeight, "Settings");
    addButton(app, (width - buttonWidth) / 2, startY + 2 * (buttonHeight + 20), buttonWidth, buttonHeight, "Quit");
}

void cleanupApp(VisualizerApp* app) {
    TTF_CloseFont(app->font);
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    TTF_Quit();
    SDL_Quit();
}

void handleEvents(VisualizerApp* app) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            app->state = QUIT_STATE;
        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            if (app->state == VISUALIZATION_STATE) {
                SDL_Rect pauseButton = {10, 10, 80, 40};
                SDL_Rect stepButton = {100, 10, 80, 40};
                SDL_Rect resetButton = {190, 10, 80, 40};
                SDL_Rect backButton = {280, 10, 80, 40};

                if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &pauseButton)) {
                    app->sortingState.isPaused = !app->sortingState.isPaused;
                } else if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &stepButton)) {
                    app->sortingState.shouldStep = true;
                    app->sortingState.isPaused = true;
                } else if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &resetButton)) {
                    resetSorting(&app->sortingState);
                    initVisualization(app->windowHeight);
                } else if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &backButton)) {
                    app->state = ALGORITHM_MENU_STATE;
                    resetSorting(&app->sortingState);
                }
            }
            Button* buttons = getButtons();
            int buttonCount = getButtonCount();
            for (int i = 0; i < buttonCount; i++) {
                if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &buttons[i].rect)) {
                    if (app->state == MAIN_MENU_STATE) {
                        if (strcmp(buttons[i].text, "Start Visualization") == 0) {
                            app->state = DATA_STRUCTURE_MENU_STATE;
                        } else if (strcmp(buttons[i].text, "Settings") == 0) {
                            app->state = SETTINGS_STATE;
                        } else if (strcmp(buttons[i].text, "Quit") == 0) {
                            app->state = QUIT_STATE;
                        }
                    } else if (app->state == DATA_STRUCTURE_MENU_STATE) {
                        if (strcmp(buttons[i].text, "Array") == 0) {
                            app->selectedDataStructure = "Array";
                            app->state = ALGORITHM_MENU_STATE;
                        } else if (strcmp(buttons[i].text, "Linked List") == 0) {
                            app->selectedDataStructure = "Linked List";
                            app->state = ALGORITHM_MENU_STATE;
                        } else if (strcmp(buttons[i].text, "Back") == 0) {
                            app->state = MAIN_MENU_STATE;
                        }
                    } else if (app->state == ALGORITHM_MENU_STATE) {
                        if (strcmp(buttons[i].text, "Bubble Sort") == 0) {
                            app->selectedAlgorithm = "Bubble Sort";
                            app->state = VISUALIZATION_STATE;
                        } else if (strcmp(buttons[i].text, "Quick Sort") == 0) {
                            app->selectedAlgorithm = "Quick Sort";
                            app->state = VISUALIZATION_STATE;
                        } else if (strcmp(buttons[i].text, "Back") == 0) {
                            app->state = DATA_STRUCTURE_MENU_STATE;
                        }
                    }
                }
            }
        }
    }
}
