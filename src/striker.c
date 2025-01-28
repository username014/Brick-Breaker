#include "SDL.h"
#include "../includes/striker.h"

struct Striker Striker_init(int maxX, int maxY, SDL_Color strikerColor) {
    struct Striker striker;
    striker.posx = maxX / 2 - 50;
    striker.posy = maxY - 50;
    striker.width = (rand() % 2 + 1) * 50;
    striker.height = 5;
    striker.speed = (rand() % 2 + 1) * 10;
    striker.color = strikerColor;
    striker.strikerRect = (SDL_Rect){ striker.posx, striker.posy, striker.width, striker.height };
    return striker;
}

void Striker_display(SDL_Renderer* renderer, Striker striker) {
    SDL_SetRenderDrawColor(renderer, striker.color.r, striker.color.g, striker.color.b, 255);
    SDL_RenderFillRect(renderer, &striker.strikerRect);
}

struct Striker Striker_update(Striker striker, int xFac, int maxX) {
    striker.posx += striker.speed * xFac;
    if (striker.posx <= 0) {
        striker.posx = 0;
    }
    else if (striker.posx + striker.width >= maxX) {
        striker.posx = maxX - striker.width;
    }
    striker.strikerRect = (SDL_Rect){ striker.posx, striker.posy, striker.width, striker.height };
    return striker;
}

int Striker_moving(SDL_Event event) {
    int variable = 0;
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_LEFT) {
            variable = -1;
        }
        if (event.key.keysym.sym == SDLK_RIGHT) {
            variable = 1;
        }
    }
    if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT) {
           variable = 0;
        }
    }
    return variable;
}