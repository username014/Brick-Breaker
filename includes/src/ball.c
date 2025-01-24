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

void Ball_display(SDL_Renderer *renderer, Ball ball) {
    SDL_SetRenderDrawColor(renderer, ball.color.r, ball.color.g, ball.color.b, 255);
    Draw_circle(renderer, ball.posx, ball.posy, ball.radius);
}