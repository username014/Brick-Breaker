#pragma once
#include "blocks.h"
#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

int Check_collision(SDL_Rect rect, SDL_Rect ball);
int Gameover(SDL_Renderer* renderer, TTF_Font* font);
void Texture_Init(char* string, TTF_Font* font, SDL_Renderer* renderer, SDL_Rect textRect, int mode, SDL_Color color);
void Texture_Rewrite(char* string, TTF_Font* font, SDL_Renderer* renderer, SDL_Rect textRect, int variable, SDL_Color color);
int Quit(SDL_Event event);
void Exit(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, struct Block* listOfBlocks);

#endif