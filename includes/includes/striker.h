#pragma once
#ifndef STRIKER_H
#define STRIKER_H

typedef struct Striker {
    int posx, posy;
    int width, height;
    int speed;
    SDL_Color color;
    SDL_Rect strikerRect;
    SDL_Renderer* renderer;
} Striker;

void Striker_display(SDL_Renderer* renderer, Striker striker);

#endif

