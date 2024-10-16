#include "visualization.h"
#include "sorting.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

int arrayToSort[ARRAY_SIZE];

void initVisualization(int windowHeight, SortingState* state) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arrayToSort[i] = rand() % (windowHeight - 100) + 50;
    }

    state->isPaused = false;
    state->isCompleted = false;
    state->hasStarted = false;
    state->currentStep = 0;
    state->shouldStep = false;
    state->animationProgress = 0.0f;
    state->compareIndex1 = -1;
    state->compareIndex2 = -1;
    state->swapIndex1 = -1;
    state->swapIndex2 = -1;
    state->pivotIndex = -1;
    state->low = -1;
    state->high = -1;
    state->i = -1;
    state->j = 0;
}

void resetSorting(SortingState* state) {
    state->isPaused = false;
    state->hasStarted = false;
    state->isCompleted = false;
    state->currentStep = 0;
    state->animationProgress = 0.0f;
    state->shouldStep = false;
    state->compareIndex1 = -1;
    state->compareIndex2 = -1;
    state->swapIndex1 = -1;
    state->swapIndex2 = -1;
    state->pivotIndex = -1;
    state->low = -1;
    state->high = -1;
    state->i = -1;
    state->j = 0;
}

void renderArray(SDL_Renderer* renderer, int windowWidth, int windowHeight, const int* array, SortingState* state) {
    int barWidth = windowWidth / ARRAY_SIZE;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        int barHeight = state->hasStarted ? array[i] : (int)(array[i] * state->animationProgress);
        SDL_Rect bar = {i * barWidth, windowHeight - barHeight, barWidth - 1, barHeight};

        // Default color
        SDL_Color color = {0, 255, 0, 255}; // Green

        // Swap color
        if (i == state->swapIndex1 || i == state->swapIndex2) {
            color = (SDL_Color){255, 0, 0, 255}; // Red
        }
            // Comparison color
        else if (i == state->compareIndex1 || i == state->compareIndex2) {
            color = (SDL_Color){255, 255, 0, 255}; // Yellow
        }
            // Pivot color (for quicksort)
        else if (i == state->pivotIndex) {
            color = (SDL_Color){255, 165, 0, 255}; // Orange
        }
            // Sorted portion (optional)
        else if (state->isCompleted) {
            color = (SDL_Color){128, 128, 128, 255}; // Gray
        }

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &bar);
    }

    // Render progress bar
    if (state->hasStarted) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue
        float progress = (float)state->currentStep / (float)(ARRAY_SIZE * (ARRAY_SIZE - 1) / 2); // Adjust total steps as needed
        int progressWidth = (int)(progress * windowWidth);
        SDL_Rect indicator = {0, windowHeight - 5, progressWidth, 5};
        SDL_RenderFillRect(renderer, &indicator);
    }
}

    void updateSorting(const char *algorithm, int *array, int size, SortingState *state) {
        if (!state->isCompleted && (!state->isPaused || state->shouldStep)) {
            if (strcmp(algorithm, "Bubble Sort") == 0) {
                bubbleSortStep(array, size, state);
            } else if (strcmp(algorithm, "Quick Sort") == 0) {
                quickSortStep(array, size, state);
            }
            state->shouldStep = false;
        }
    }

    void renderSlider(SDL_Renderer *renderer, Slider *slider) {
        // Render the slider bar
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_RenderFillRect(renderer, &slider->bar);

        // Render the slider handle
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderFillRect(renderer, &slider->slider);
    }

    void handleSliderEvent(Slider *slider, SDL_Event *event) {
        if (event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEMOTION) {
            if (event->button.button == SDL_BUTTON_LEFT) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX >= slider->bar.x && mouseX <= slider->bar.x + slider->bar.w) {
                    slider->slider.x = mouseX - slider->slider.w / 2;
                    if (slider->slider.x < slider->bar.x) slider->slider.x = slider->bar.x;
                    if (slider->slider.x > slider->bar.x + slider->bar.w - slider->slider.w)
                        slider->slider.x = slider->bar.x + slider->bar.w - slider->slider.w;

                    float percentage = (float) (slider->slider.x - slider->bar.x) / (slider->bar.w - slider->slider.w);
                    slider->currentValue =
                            slider->minValue + (int) (percentage * (slider->maxValue - slider->minValue));
                }
            }
        }
    }

    void renderVisualization(SDL_Renderer *renderer, TTF_Font *font, int windowWidth, int windowHeight,
                             const char *dataStructure, const char *algorithm, SortingState *state,
                             Slider *speedSlider) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        renderArray(renderer, windowWidth, windowHeight, arrayToSort, state);
        renderSlider(renderer, speedSlider);

        // Render control buttons
        SDL_Rect startPauseButton = {10, 10, 80, 40};
        SDL_Rect stepButton = {100, 10, 80, 40};
        SDL_Rect resetButton = {190, 10, 80, 40};
        SDL_Rect backButton = {280, 10, 80, 40};

        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderFillRect(renderer, &startPauseButton);
        SDL_RenderFillRect(renderer, &stepButton);
        SDL_RenderFillRect(renderer, &resetButton);
        SDL_RenderFillRect(renderer, &backButton);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &startPauseButton);
        SDL_RenderDrawRect(renderer, &stepButton);
        SDL_RenderDrawRect(renderer, &resetButton);
        SDL_RenderDrawRect(renderer, &backButton);

        // Render button text
        const char *startPauseText = !state->hasStarted ? "Start" :
                                     (state->isPaused ? "Resume" : "Pause");
        renderText(renderer, font, startPauseText, (SDL_Color) {255, 255, 255, 255}, 15, 15, 70, 30);
        renderText(renderer, font, "Step", (SDL_Color) {255, 255, 255, 255}, 105, 15, 70, 30);
        renderText(renderer, font, "Reset", (SDL_Color) {255, 255, 255, 255}, 195, 15, 70, 30);
        renderText(renderer, font, "Back", (SDL_Color) {255, 255, 255, 255}, 285, 15, 70, 30);

        // Render the speed value
        char speedText[20];
        snprintf(speedText, sizeof(speedText), "Speed: %d", speedSlider->currentValue);
        renderText(renderer, font, speedText, (SDL_Color) {255, 255, 255, 255}, speedSlider->bar.x,
                   speedSlider->bar.y - 30, 100, 20);
    }

    void renderText(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, int x, int y, int w, int h) {
        SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect rect = {x, y, w, h};
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

void updateAnimation(SortingState* state, float deltaTime) {
    if (!state->hasStarted) {
        state->animationProgress += deltaTime * 2;
        if (state->animationProgress > 1.0f) {
            state->animationProgress = 1.0f;
        }
    }
}