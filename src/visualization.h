#ifndef ALGOVIZ_VISUALIZATION_H
#define ALGOVIZ_VISUALIZATION_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>

#define ARRAY_SIZE 50

typedef struct {
    bool isPaused;
    bool isCompleted;
    int currentStep;
    bool shouldStep;
    int speed;
} SortingState;

typedef struct {
    SDL_Rect bar;
    SDL_Rect slider;
    int minValue;
    int maxValue;
    int currentValue;
} Slider;

void initVisualization(int windowHeight);
void renderVisualization(SDL_Renderer* renderer, TTF_Font* font, int windowWidth, int windowHeight, const char* dataStructure, const char* algorithm, SortingState* state, Slider* speedSlider);
void resetSorting(SortingState* state);
void renderArray(SDL_Renderer* renderer, int windowWidth, int windowHeight, const int* array);
void updateSorting(const char* algorithm, int* array, int size, SortingState* state);
void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int x, int y, int w, int h);
void renderSlider(SDL_Renderer* renderer, Slider* slider);
void handleSliderEvent(Slider* slider, SDL_Event* event);

extern int arrayToSort[ARRAY_SIZE];

#endif //ALGOVIZ_VISUALIZATION_H