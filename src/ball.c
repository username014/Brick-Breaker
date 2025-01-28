#include "SDL.h"
#include "../includes/ball.h"

void Draw_circle(SDL_Renderer* renderer, int centreX, int centreY, int radius){

    int x = (radius - 1);
    int y = 0;
    int xError = 1;
    int yError = 1;
    int error = (xError - radius * 2);

    while (x >= y){
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

        if (error <= 0){ // Проверка на движение вверх по окружности
            ++y;
            error += yError;
            yError += 2;
        }

        if (error > 0){ // Проверка на движение влево по окружности
            --x;
            xError += 2;
            error += (xError - radius * 2);
        }
    }
}

struct Ball Ball_init(int spawnX, int spawnY, SDL_Color ballColor) {
    struct Ball ball;
    ball.posx = spawnX;
    ball.posy = spawnY;
    ball.radius = 4;
    ball.speed = 5;
    ball.color = ballColor;
    ball.xFac = pow((-1), (rand() % 2)) / 2;
    ball.yFac = -1;
    return ball;
}

void Ball_display(SDL_Renderer *renderer, Ball ball) {
    SDL_SetRenderDrawColor(renderer, ball.color.r, ball.color.g, ball.color.b, 255);
    Draw_circle(renderer, ball.posx, ball.posy, ball.radius);
}

struct Ball Ball_update(Ball ball, int maxX, int maxY, int restoreX, int restoreY) {
    if (ball.posx <= 0 || ball.posx >= maxX) {
        ball.xFac *= -1;
    }
    if (ball.posy <= 0) {
        ball.yFac *= -1;
    }
    if (ball.posy >= maxY) {
        ball.posx = restoreX;
        ball.posy = restoreY;
        ball.xFac = pow((-1), (rand() % 2)) / 2;
        ball.yFac = -1;
    }

    ball.posx += ball.xFac * ball.speed;
    ball.posy += ball.yFac * ball.speed;
    return ball;
}

struct Ball Ball_interaction_with_Striker(Ball ball, SDL_Rect rect1, SDL_Rect rect2, float strikerPosX, float strikerWidth){
    if (Check_collision(rect1, rect2)) {
        ball.yFac *= -1;
        ball.xFac = (float)((ball.posx - (strikerPosX + strikerWidth / 2)) / (float)(strikerWidth / 4));
    }
    return ball;
};