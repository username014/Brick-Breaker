#pragma once
#ifndef BALL_H
#define BALL_H

typedef struct Ball {
    int posx, posy;
    int radius;
    int speed;
    SDL_Color color;
    float xFac, yFac;
    SDL_Renderer* renderer;
    SDL_Rect ball;
} Ball;

void Draw_circle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius);
void Ball_display(SDL_Renderer *renderer, Ball ball);

#endif