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

struct Striker Striker_init(int maxX, int maxY, SDL_Color strikerColor);
void Striker_display(SDL_Renderer* renderer, Striker striker);
struct Striker Striker_update(Striker striker, int strikerXFac, int maxX);
int Striker_moving(SDL_Event event);

#endif

