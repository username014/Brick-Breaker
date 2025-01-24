#pragma once
#ifndef BLOCKS_H
#define BLOCKS_H

SDL_Color BLACK;
SDL_Color WHITE;
SDL_Color GREEN;
SDL_Color BLUE;

typedef struct Block {
    int posx, posy;
    int width, height;
    SDL_Color color;
    int level;
    int damage;
    int health;
    SDL_Rect blockRect;
    SDL_Rect* blocks;
    SDL_Renderer* renderer;
} Block;

void Blocks_populating(int blockWidth, int blockHeight, int horizontalGap, int verticalGap, SDL_Renderer* renderer, Block* listOfBlocks);
void Blocks_display(SDL_Renderer* renderer, Block* listOfBlocks, int block_number);

#endif