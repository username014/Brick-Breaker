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

void Draw_circle(SDL_Renderer* renderer, int centreX, int centreY, int radius);
struct Ball Ball_init(int spawnX, int spawnY, SDL_Color ballColor);
void Ball_display(SDL_Renderer* renderer, Ball ball);
struct Ball Ball_update(Ball ball, int maxX, int maxY, int restoreX, int restoreY);
struct Ball Ball_interaction_with_Striker(Ball ball, SDL_Rect rect1, SDL_Rect rect2, float strikerPosX, float strikerWidth);

#endif