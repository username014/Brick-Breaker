#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SDL.h"
#include "../includes/blocks.h"

SDL_Color BLACK = { 0, 0, 0 };
SDL_Color WHITE = { 255, 255, 255 };
SDL_Color GREEN = { 0, 255, 0 };
SDL_Color BLUE = { 0, 0, 255 };

void Blocks_populating(int blockWidth, int blockHeight, int gapHorizontal, int gapVertical, SDL_Renderer* renderer, Block* listOfBlocks) { // јлгоритм заполнени€ массива, состо€щего из блоков
    int WIDTH = 1200;
    int HEIGHT = 800;
    int index = 0;
    for (int i = 0; i < WIDTH; i += blockWidth + gapHorizontal) {
        for (int j = 0; j < HEIGHT / 2; j += blockHeight + gapVertical) {
            struct Block block; // каждому блоку задаютс€ свои параметры
            block.posx = i;
            block.posy = j;
            block.width = blockWidth;
            block.height = blockHeight;
            if (rand() % 3 == 0) {
                block.color = WHITE;
                block.level = 0;
            }
            else if (rand() % 3 == 1) {
                block.color = GREEN;
                block.level = 1;
            }
            else {
                block.color = BLUE;
                block.level = 2;
            }
            block.damage = 100;
            if (block.level == 2) {
                block.health = 300;
            }
            else if (block.level == 1){
                block.health = 200;
            }
            else {
                block.health = 100;
            }
            block.blockRect.x = block.posx;
            block.blockRect.y = block.posy;
            block.blockRect.w = block.width;
            block.blockRect.h = block.height;
            listOfBlocks[index++] = block;
        }
    }
}

void Blocks_display(SDL_Renderer* renderer, Block* listOfBlocks, int block_number) {
    SDL_SetRenderDrawColor(renderer, listOfBlocks[block_number].color.r, listOfBlocks[block_number].color.g, listOfBlocks[block_number].color.b, 255);
    SDL_RenderFillRect(renderer, &listOfBlocks[block_number].blockRect);
}