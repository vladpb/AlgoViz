#include "visualization.h"
#include "sorting.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

int arrayToSort[ARRAY_SIZE];

void initVisualization(int windowHeight) {
    srand(time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arrayToSort[i] = rand() % (windowHeight - 100) + 50;
    }
}

void renderArray(SDL_Renderer* renderer, int windowWidth, int windowHeight, const int* array) {
    int barWidth = windowWidth / ARRAY_SIZE;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        SDL_Rect bar = {i * barWidth, windowHeight - array[i], barWidth - 1, array[i]};
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &bar);
    }
}

void resetSorting(SortingState* state) {
    state->isPaused = false;
    state->isCompleted = false;
    state->currentStep = 0;
    state->shouldStep = false;
}

void updateSorting(const char* algorithm, int* array, int size, SortingState* state) {
    if (!state->isCompleted && (!state->isPaused || state->shouldStep)) {
        if (strcmp(algorithm, "Bubble Sort") == 0) {
            bubbleSortStep(array, size, state);
        } else if (strcmp(algorithm, "Quick Sort") == 0) {
            quickSortStep(array, size, state);
        }
        state->shouldStep = false;
    }
}

void renderSlider(SDL_Renderer* renderer, Slider* slider) {
    // Render the slider bar
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderFillRect(renderer, &slider->bar);

    // Render the slider handle
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(renderer, &slider->slider);
}

void handleSliderEvent(Slider* slider, SDL_Event* event) {
    if (event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEMOTION) {
        if (event->button.button == SDL_BUTTON_LEFT) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            if (mouseX >= slider->bar.x && mouseX <= slider->bar.x + slider->bar.w) {
                slider->slider.x = mouseX - slider->slider.w / 2;
                if (slider->slider.x < slider->bar.x) slider->slider.x = slider->bar.x;
                if (slider->slider.x > slider->bar.x + slider->bar.w - slider->slider.w)
                    slider->slider.x = slider->bar.x + slider->bar.w - slider->slider.w;

                float percentage = (float)(slider->slider.x - slider->bar.x) / (slider->bar.w - slider->slider.w);
                slider->currentValue = slider->minValue + (int)(percentage * (slider->maxValue - slider->minValue));
            }
        }
    }
}

void renderVisualization(SDL_Renderer* renderer, TTF_Font* font, int windowWidth, int windowHeight, const char* dataStructure, const char* algorithm, SortingState* state, Slider* speedSlider) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    renderArray(renderer, windowWidth, windowHeight, arrayToSort);
    renderSlider(renderer, speedSlider);

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
    renderText(renderer, font, state->isPaused ? "Resume" : "Pause", (SDL_Color){255, 255, 255, 255}, 15, 15, 70, 30);
    renderText(renderer, font, "Step", (SDL_Color){255, 255, 255, 255}, 105, 15, 70, 30);
    renderText(renderer, font, "Reset", (SDL_Color){255, 255, 255, 255}, 195, 15, 70, 30);
    renderText(renderer, font, "Back", (SDL_Color){255, 255, 255, 255}, 285, 15, 70, 30);

    // Render the speed value
    char speedText[20];
    snprintf(speedText, sizeof(speedText), "Speed: %d", speedSlider->currentValue);
    renderText(renderer, font, speedText, (SDL_Color){255, 255, 255, 255}, speedSlider->bar.x, speedSlider->bar.y - 30, 100, 20);
}

void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int x, int y, int w, int h) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}