#ifndef ALGOVIZ_APP_H
#define ALGOVIZ_APP_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "visualization.h"

typedef enum {
    MAIN_MENU_STATE,
    DATA_STRUCTURE_MENU_STATE,
    ALGORITHM_MENU_STATE,
    VISUALIZATION_STATE,
    SETTINGS_STATE,
    QUIT_STATE
} AppState;

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    AppState state;
    SortingState sortingState;
    int windowWidth;
    int windowHeight;
    const char* selectedDataStructure;
    const char* selectedAlgorithm;
} VisualizerApp;

void initApp(VisualizerApp* app, int width, int height);
void cleanupApp(VisualizerApp* app);
void handleEvents(VisualizerApp* app, SDL_Event* event);

#endif //ALGOVIZ_APP_H