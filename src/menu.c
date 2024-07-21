#include "menu.h"
#include "app.h"
#include <SDL_ttf.h>

#define MAX_BUTTONS 4

static Button buttons[MAX_BUTTONS];
static int buttonCount = 0;

Button* getButtons() {
    return buttons;
}

int getButtonCount() {
    return buttonCount;
}

void clearButtons() {
    buttonCount = 0;
}

void addButton(VisualizerApp* app, int x, int y, int width, int height, char* text) {
    if (buttonCount >= MAX_BUTTONS) return;

    Button button = {
        .rect = {x, y, width, height},
        .text = text,
        .color = {50, 50, 50, 255}  // Dark gray color
    };
    buttons[buttonCount++] = button;
}

static void renderButton(VisualizerApp* app, Button* button) {
    SDL_SetRenderDrawColor(app->renderer, button->color.r, button->color.g, button->color.b, button->color.a);
    SDL_RenderFillRect(app->renderer, &button->rect);

    SDL_SetRenderDrawColor(app->renderer, 255, 255, 255, 255);  // White border
    SDL_RenderDrawRect(app->renderer, &button->rect);

    SDL_Color textColor = {255, 255, 255, 255};  // White text
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(app->font, button->text, textColor);
    SDL_Texture* message = SDL_CreateTextureFromSurface(app->renderer, surfaceMessage);

    int textWidth = surfaceMessage->w;
    int textHeight = surfaceMessage->h;
    SDL_Rect messageRect = {
        button->rect.x + (button->rect.w - textWidth) / 2,
        button->rect.y + (button->rect.h - textHeight) / 2,
        textWidth,
        textHeight
    };

    SDL_RenderCopy(app->renderer, message, NULL, &messageRect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}

void renderMenu(VisualizerApp* app) {
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
    SDL_RenderClear(app->renderer);

    for (int i = 0; i < buttonCount; i++) {
        renderButton(app, &buttons[i]);
    }
}


void renderMainMenu(VisualizerApp* app) {
    clearButtons();
    addButton(app, (app->windowWidth - 300) / 2, 200, 300, 60, "Start Visualization");
    addButton(app, (app->windowWidth - 300) / 2, 300, 300, 60, "Settings");
    addButton(app, (app->windowWidth - 300) / 2, 400, 300, 60, "Quit");
    renderMenu(app);
}

void renderDataStructureMenu(VisualizerApp* app) {
    clearButtons();
    addButton(app, (app->windowWidth - 300) / 2, 200, 300, 60, "Array");
    addButton(app, (app->windowWidth - 300) / 2, 300, 300, 60, "Linked List");
    addButton(app, (app->windowWidth - 300) / 2, 400, 300, 60, "Back");
    renderMenu(app);
}

void renderAlgorithmMenu(VisualizerApp* app) {
    clearButtons();
    addButton(app, (app->windowWidth - 300) / 2, 200, 300, 60, "Bubble Sort");
    addButton(app, (app->windowWidth - 300) / 2, 300, 300, 60, "Quick Sort");
    addButton(app, (app->windowWidth - 300) / 2, 400, 300, 60, "Back");
    renderMenu(app);
}