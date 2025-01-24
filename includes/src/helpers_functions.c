#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include "../includes/blocks.h"
#include "../includes/helper_functions.h"

int Check_collision(SDL_Rect rect, SDL_Rect ball) { // Функция проверки столкновения объектов
    return SDL_HasIntersection(&rect, &ball);
}

int Gameover(SDL_Renderer* renderer, TTF_Font* font) { // Функция завершения игры (когда заканчиваются жизни)
    int gameOver = 1;
    SDL_Event event;
    while (gameOver) {
        while (SDL_PollEvent(&event)) {
            SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, 255);
            SDL_RenderClear(renderer);
            if (event.type == SDL_QUIT) {
                return 0;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    return 0;
                }
                if (event.key.keysym.sym == SDLK_SPACE) {
                    return 1;
                }
            }
        }
    }
}