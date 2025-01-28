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


void Texture_Init(char* string, TTF_Font* font, SDL_Renderer* renderer, SDL_Rect textRect, int mode, SDL_Color color){
    if (mode == 0) {
        SDL_Surface* text = TTF_RenderText_Solid(font, string, color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text);
        SDL_QueryTexture(texture, NULL, NULL, &textRect.w, &textRect.h);
    }
    else if (mode == 1) {
        SDL_Surface* text = TTF_RenderText_Solid(font, string, color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text);
        SDL_RenderCopy(renderer, texture, NULL, &textRect);
    }
}


void Texture_Rewrite(char* string, TTF_Font* font, SDL_Renderer* renderer, SDL_Rect textRect, int variable, SDL_Color color) {
    char str[100];
    strcpy(str, string);
    char char_variable[sizeof(int) * 10];
    sprintf(char_variable, "%d", variable);
    strcat(str, char_variable);
    SDL_Surface* text = TTF_RenderText_Solid(font, str, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text);
    SDL_RenderCopy(renderer, texture, NULL, &textRect);
}

int Quit(SDL_Event event) {
    if (event.type == SDL_QUIT) {
        return 0;
    }
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
            return 0;
        }
    }
}

void Exit(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, struct Block* listOfBlocks) {
    free(listOfBlocks);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
