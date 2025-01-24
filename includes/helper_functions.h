#pragma once
#include "blocks.h"
#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

int Check_collision(SDL_Rect rect, SDL_Rect ball);
int Gameover(SDL_Renderer* renderer, TTF_Font* font);

#endif