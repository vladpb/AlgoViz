#include "particles.h"
#include <stdlib.h>

Particle particles[MAX_PARTICLES];

void initParticles(int windowWidth, int windowHeight) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].x = rand() % windowWidth;
        particles[i].y = rand() % windowHeight;
        particles[i].speedX = (rand() % 200 - 100) / 100.0f;
        particles[i].speedY = (rand() % 200 - 100) / 100.0f;
        particles[i].color.r = rand() % 256;
        particles[i].color.g = rand() % 256;
        particles[i].color.b = rand() % 256;
        particles[i].color.a = rand() % 156 + 100;
    }
}

void updateAndRenderParticles(SDL_Renderer* renderer, int windowWidth, int windowHeight) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].x += particles[i].speedX;
        particles[i].y += particles[i].speedY;

        if (particles[i].x < 0 || particles[i].x > windowWidth)
            particles[i].speedX *= -1;
        if (particles[i].y < 0 || particles[i].y > windowHeight)
            particles[i].speedY *= -1;

        SDL_SetRenderDrawColor(renderer,
                               particles[i].color.r,
                               particles[i].color.g,
                               particles[i].color.b,
                               particles[i].color.a);
        SDL_RenderDrawPoint(renderer, (int)particles[i].x, (int)particles[i].y);
    }
}