#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include "app.h"
#include "menu.h"
#include "particles.h"
#include "visualization.h"

#define WINDOW_WIDTH 1408
#define WINDOW_HEIGHT 792

void resetSorting();

int main(int argc, char* argv[]) {
    VisualizerApp app;
    initApp(&app, WINDOW_WIDTH, WINDOW_HEIGHT);
    initParticles(WINDOW_WIDTH, WINDOW_HEIGHT);
    initVisualization( WINDOW_HEIGHT);

    AppState previousState = MAIN_MENU_STATE;
    resetSorting(&app.sortingState);

    while (app.state != QUIT_STATE) {
        handleEvents(&app);

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
                updateSorting(app.selectedAlgorithm, &app.sortingState);
            renderVisualization(app.renderer, app.font, app.windowWidth, app.windowHeight,
                                app.selectedDataStructure, app.selectedAlgorithm, &app.sortingState);
            break;
            case SETTINGS_STATE:
                // Implement settings rendering
                    break;
        }
        previousState = app.state;
        SDL_RenderPresent(app.renderer);
        SDL_Delay(16);
    }

    cleanupApp(&app);
    return 0;
}