#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include "app.h"
#include "menu.h"
#include "particles.h"
#include "visualization.h"
#include "sorting.h"

#define WINDOW_WIDTH 1408
#define WINDOW_HEIGHT 792

int main(int argc, char* argv[]) {
    VisualizerApp app;
    initApp(&app, WINDOW_WIDTH, WINDOW_HEIGHT);
    initParticles(WINDOW_WIDTH, WINDOW_HEIGHT);
    initVisualization(WINDOW_HEIGHT);

    Slider speedSlider = {
        .bar = {WINDOW_WIDTH - 220, WINDOW_HEIGHT - 50, 200, 20},
        .slider = {WINDOW_WIDTH - 220, WINDOW_HEIGHT - 55, 20, 30},
        .minValue = 1,
        .maxValue = 100,
        .currentValue = 50
    };

    while (app.state != QUIT_STATE) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            handleEvents(&app, &event);
            if (app.state == VISUALIZATION_STATE) {
                handleSliderEvent(&speedSlider, &event);
            }
        }
        //Clear the renderer at the start of each frame
        SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
        SDL_RenderClear(app.renderer);


        switch (app.state) {
            case MAIN_MENU_STATE:
                renderMainMenu(&app);
                updateAndRenderParticles(app.renderer, app.windowWidth, app.windowHeight);
                break;
            case DATA_STRUCTURE_MENU_STATE:
                renderDataStructureMenu(&app);
                updateAndRenderParticles(app.renderer, app.windowWidth, app.windowHeight);
                break;
            case ALGORITHM_MENU_STATE:
                renderAlgorithmMenu(&app);
                updateAndRenderParticles(app.renderer, app.windowWidth, app.windowHeight);
                break;
            case VISUALIZATION_STATE:
                updateSorting(app.selectedAlgorithm, arrayToSort, ARRAY_SIZE, &app.sortingState);
                renderVisualization(app.renderer, app.font, app.windowWidth, app.windowHeight,
                                    app.selectedDataStructure, app.selectedAlgorithm, &app.sortingState, &speedSlider);
                SDL_Delay(101 - speedSlider.currentValue);
                break;
            case SETTINGS_STATE:
                // Implement settings rendering
                break;
        }
        SDL_RenderPresent(app.renderer);
        SDL_Delay(16);
    }

    cleanupApp(&app);
    return 0;
}