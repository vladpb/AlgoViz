#include "visualization.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ARRAY_SIZE 50
int arrayToSort[ARRAY_SIZE];
int quickSortTop = -1;

typedef struct {
    int low;
    int high;
} QuickSortState;

QuickSortState quickSortStack[ARRAY_SIZE];

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void quickSortStep(SortingState* state) {
    if (!state->isCompleted && !state->isPaused) {
        if (quickSortTop == -1) {
            // Initialize the quicksort
            quickSortStack[++quickSortTop] = (QuickSortState){0, ARRAY_SIZE - 1};
        }

        if (quickSortTop >= 0) {
            QuickSortState current = quickSortStack[quickSortTop--];
            int pivot = partition(current.low, current.high);

            if (pivot - 1 > current.low) {
                quickSortStack[++quickSortTop] = (QuickSortState){current.low, pivot - 1};
            }
            if (pivot + 1 < current.high) {
                quickSortStack[++quickSortTop] = (QuickSortState){pivot + 1, current.high};
            }
        } else {
            state->isCompleted = true;
        }
        state->currentStep++;
    }
}

void bubbleSort(SDL_Renderer* renderer, int windowWidth, int windowHeight, SortingState* state) {
    if (!state->isCompleted && !state->isPaused) {
        if (state->currentStep < ARRAY_SIZE - 1) {
            for (int j = 0; j < ARRAY_SIZE - state->currentStep - 1; j++) {
                if (arrayToSort[j] > arrayToSort[j + 1]) {
                    swap(&arrayToSort[j], &arrayToSort[j + 1]);
                }
                renderArray(renderer, windowWidth, windowHeight);
                SDL_RenderPresent(renderer);
                SDL_Delay(10);
            }
            state->currentStep++;
        } else {
            state->isCompleted = true;
        }
    }
}

int partition(int low, int high) {
    int pivot = arrayToSort[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arrayToSort[j] < pivot) {
            i++;
            swap(&arrayToSort[i], &arrayToSort[j]);
        }
    }
    swap(&arrayToSort[i + 1], &arrayToSort[high]);
    return (i + 1);
}


void resetSorting(SortingState* state) {
    state->isPaused = false;
    state->isCompleted = false;
    state->currentStep = 0;
    state->shouldStep = false;
    quickSortTop = -1;  // Reset quicksort state
}

void stepSort(SortingState* state) {
    if (!state->isCompleted) {
        state->isPaused = false;
        state->currentStep++;
        state->isPaused = true;
    }
}


void quickSort(SDL_Renderer* renderer, int windowWidth, int windowHeight, int low, int high, SortingState* state) {
    if (low < high && !state->isPaused && !state->isCompleted) {
        int pi = partition(low, high);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        renderArray(renderer, windowWidth, windowHeight);
        SDL_RenderPresent(renderer);
        SDL_Delay(50);  // Slow down the visualization

        quickSort(renderer, windowWidth, windowHeight, low, pi - 1, state);
        quickSort(renderer, windowWidth, windowHeight, pi + 1, high, state);

        state->currentStep++;
        if (state->currentStep >= ARRAY_SIZE) {
            state->isCompleted = true;
        }
    }
}

void initVisualization(int windowHeight) {
    srand(time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arrayToSort[i] = rand() % (windowHeight - 100) + 50;  // Leave some space at the top and bottom
    }
}

void renderArray(SDL_Renderer* renderer, int windowWidth, int windowHeight) {
    int barWidth = windowWidth / ARRAY_SIZE;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        SDL_Rect bar = {i * barWidth, windowHeight - arrayToSort[i], barWidth - 1, arrayToSort[i]};
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Green bars
        SDL_RenderFillRect(renderer, &bar);
    }
}

void bubbleSortStep(SortingState* state) {
    if (state->currentStep < ARRAY_SIZE - 1) {
        for (int j = 0; j < ARRAY_SIZE - state->currentStep - 1; j++) {
            if (arrayToSort[j] > arrayToSort[j + 1]) {
                swap(&arrayToSort[j], &arrayToSort[j + 1]);
            }
        }
        state->currentStep++;
    } else {
        state->isCompleted = true;
    }
}

void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int x, int y, int w, int h) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void updateSorting(const char* algorithm, SortingState* state) {
    if (!state->isCompleted && (!state->isPaused || state->shouldStep)) {
        if (strcmp(algorithm, "Bubble Sort") == 0) {
            bubbleSortStep(state);
        } else if (strcmp(algorithm, "Quick Sort") == 0) {
            quickSortStep(state);
        }
        state->shouldStep = false;
    }
}

void renderVisualization(SDL_Renderer* renderer, TTF_Font* font, int windowWidth, int windowHeight, const char* dataStructure, const char* algorithm, SortingState* state) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render the array or linked list
    if (strcmp(dataStructure, "Array") == 0) {
        renderArray(renderer, windowWidth, windowHeight);
    } else if (strcmp(dataStructure, "Linked List") == 0) {
        // Implement linked list visualization
    }

    // Render control buttons
    SDL_Rect pauseButton = {10, 10, 80, 40};
    SDL_Rect stepButton = {100, 10, 80, 40};
    SDL_Rect resetButton = {190, 10, 80, 40};
    SDL_Rect backButton = {280, 10, 80, 40};

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &pauseButton);
    SDL_RenderFillRect(renderer, &stepButton);
    SDL_RenderFillRect(renderer, &resetButton);
    SDL_RenderFillRect(renderer, &backButton);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &pauseButton);
    SDL_RenderDrawRect(renderer, &stepButton);
    SDL_RenderDrawRect(renderer, &resetButton);
    SDL_RenderDrawRect(renderer, &backButton);

    // Render button text
    SDL_Color textColor = {255, 255, 255, 255};
    renderText(renderer, font, state->isPaused ? "Resume" : "Pause", textColor, 15, 15, 70, 30);
    renderText(renderer, font, "Step", textColor, 105, 15, 70, 30);
    renderText(renderer, font, "Reset", textColor, 195, 15, 70, 30);
    renderText(renderer, font, "Back", textColor, 285, 15, 70, 30);

    SDL_RenderPresent(renderer);
}