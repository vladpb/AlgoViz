#ifndef ALGOVIZ_MENU_H
#define ALGOVIZ_MENU_H
#define MAX_BUTTONS 4

#include "app.h"

typedef struct {
    SDL_Rect rect;
    char* text;
    SDL_Color color;
} Button;

Button* getButtons();
int getButtonCount();

void renderMenu(VisualizerApp* app);
void renderMainMenu(VisualizerApp* app);
void renderDataStructureMenu(VisualizerApp* app);
void renderAlgorithmMenu(VisualizerApp* app);
void addButton(VisualizerApp* app, int x, int y, int width, int height, char* text);
void clearButtons();

#endif //ALGOVIZ_MENU_H