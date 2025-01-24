#include "SDL.h"
#include "../includes/striker.h"

void Striker_display(SDL_Renderer* renderer, Striker striker) {
    SDL_SetRenderDrawColor(renderer, striker.color.r, striker.color.g, striker.color.b, 255);
    SDL_RenderFillRect(renderer, &striker.strikerRect);
}