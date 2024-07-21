#ifndef ALGOVIZ_PARTICLES_H
#define ALGOVIZ_PARTICLES_H

#include <SDL.h>

#define MAX_PARTICLES 100

typedef struct {
    float x, y;
    float speedX, speedY;
    SDL_Color color;
} Particle;

void initParticles(int windowWidth, int windowHeight);
void updateAndRenderParticles(SDL_Renderer* renderer, int windowWidth, int windowHeight);

#endif //ALGOVIZ_PARTICLES_H