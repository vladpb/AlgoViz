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
} SortingState;

void initVisualization(int windowHeight);
void renderVisualization(SDL_Renderer* renderer, TTF_Font* font, int windowWidth, int windowHeight, const char* dataStructure, const char* algorithm, SortingState* state);
void bubbleSortStep(SortingState* state);
void quickSortStep(SortingState* state);
void resetSorting(SortingState* state);
void renderArray(SDL_Renderer* renderer, int windowWidth, int windowHeight);
void updateSorting(const char* algorithm, SortingState* state);
void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int x, int y, int w, int h);
int partition(int low, int high);

#endif //ALGOVIZ_VISUALIZATION_H