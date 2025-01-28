#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include "includes/helper_functions.h"
#include "includes/striker.h"
#include "includes/blocks.h"
#include "includes/ball.h"


#define WIDTH 1200
#define HEIGHT 800
#define FPS 30


SDL_Color RED = {255, 0, 0};


void Init_SDL(SDL_Window** window, SDL_Renderer** renderer, TTF_Font** font, TTF_Font** gameoverFont, TTF_Font** pressButtonFont) {
    srand((unsigned int)time(NULL));
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    *window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    *font = TTF_OpenFont("C:/Users/Admin/Documents/Times new roman/timesnewromanpsmt.ttf", 15);
    *gameoverFont = TTF_OpenFont("C:/Users/Admin/Documents/Times new roman/timesnewromanps_italicmt.ttf", 65);
    *pressButtonFont = TTF_OpenFont("C:/Users/Admin/Documents/Times new roman/timesnewromanps_italicmt.ttf", 25);
}


void Init_textures(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect* scoreTextRect, SDL_Rect* livesTextRect, SDL_Rect* gameoverTextRect, SDL_Rect* pressButtonTextRect) {
    Texture_Init("Score : 0", font, renderer, *scoreTextRect, 0, WHITE);
    Texture_Init("Lives : 3", font, renderer, *livesTextRect, 0, WHITE);
    Texture_Init("Game over", font, renderer, *gameoverTextRect, 0, RED);
    Texture_Init("Press <space> to restart or <esc> to exit", font, renderer, *pressButtonTextRect, 0, RED);
}

void Init_blocks(SDL_Renderer* renderer, struct Block** listOfBlocks, int* numBlocks) {
    int blockWidth = rand() % 31 + 20;
    int horizontalGap = (blockWidth % 10 == 0) ? 10 : 10 - blockWidth % 10;
    int verticalGap = horizontalGap;
    int blockHeight = 20 - verticalGap;
    *numBlocks = (WIDTH / (blockWidth + horizontalGap)) * (HEIGHT / (2 * (blockHeight + verticalGap)));
    *listOfBlocks = (struct Block*)malloc(sizeof(struct Block) * (*numBlocks));
    if (*listOfBlocks == NULL) {
        exit(0);
    }
    Blocks_populating(blockWidth, blockHeight, horizontalGap, verticalGap, renderer, *listOfBlocks);
}


int SDL_main() {
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font, * gameoverFont, * pressButtonFont;

    Init_SDL(&window, &renderer, &font, &gameoverFont, &pressButtonFont);

    SDL_Rect scoreTextRect = { 20, HEIGHT - 50, 60, 20 };
    SDL_Rect livesTextRect = { WIDTH - 120, HEIGHT - 50, 60, 20 };
    SDL_Rect gameoverTextRect = { WIDTH / 2 - 200, HEIGHT / 2 - 150, 100, 40 };
    SDL_Rect pressButtonTextRect = { WIDTH / 2 - 215, HEIGHT / 2 + 150, 415, 30 };
    Init_textures(renderer, font, &scoreTextRect, &livesTextRect, &gameoverTextRect, &pressButtonTextRect);

    struct Block* listOfBlocks;
    int numBlocks;
    int lives = 3, score = 0, running = 1, strikerXFac = 0;

    struct Striker striker = Striker_init(WIDTH, HEIGHT, WHITE);
    struct Ball ball = Ball_init(striker.posx + 50, HEIGHT - 60, WHITE);
    Init_blocks(renderer, &listOfBlocks, &numBlocks);

    SDL_Event event;
    while (running) {
        SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, 255);
        SDL_RenderClear(renderer);

        Texture_Rewrite("Score : ", font, renderer, scoreTextRect, score, WHITE);
        Texture_Rewrite("Lives : ", font, renderer, livesTextRect, lives, WHITE);

        if (numBlocks == 0) {
            Init_blocks(renderer, &listOfBlocks, &numBlocks);
        }

        if (lives <= 0) {
            SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, 255);
            SDL_RenderClear(renderer);
            gameoverTextRect.w = 400;
            gameoverTextRect.h = 300;
            Texture_Init("Game over", font, renderer, gameoverTextRect, 1, RED);
            Texture_Init("Press <space> to restart or <esc> to exit", font, renderer, pressButtonTextRect, 1, RED);
            SDL_RenderPresent(renderer);
            running = Gameover(renderer, font);
            if (running == 0) {
                break;
            }
            lives = 3;
            score = 0;
            Init_blocks(renderer, &listOfBlocks, &numBlocks);
        }

        while (SDL_PollEvent(&event)) {
            running = Quit(event);
            strikerXFac = Striker_moving(event);
        }

        ball = Ball_interaction_with_Striker(ball, striker.strikerRect, (SDL_Rect) { ball.posx, ball.posy, ball.radius * 2, ball.radius * 2 }, striker.posx, striker.width);

        for (int i = 0; i < numBlocks; i++) {
            if (Check_collision(listOfBlocks[i].blockRect, (SDL_Rect) { ball.posx, ball.posy, ball.radius * 2, ball.radius * 2 })) {
                if (((ball.posx >= listOfBlocks[i].posx + listOfBlocks[i].width * 3 / 4 && ball.posx <= listOfBlocks[i].posx + listOfBlocks[i].width) && ball.xFac < 0) || ((ball.posx + ball.radius * 2 >= listOfBlocks[i].posx && ball.posx + ball.radius * 2 <= listOfBlocks[i].posx + listOfBlocks[i].width / 4) && ball.xFac > 0)) {
                    ball.xFac *= -1;
                }
                if (((ball.posy >= listOfBlocks[i].posy + listOfBlocks[i].height * 3 / 4 && ball.posy <= listOfBlocks[i].posy + listOfBlocks[i].height) && ball.yFac < 0) || ((ball.posy + ball.radius * 2 >= listOfBlocks[i].posy && ball.posy + ball.radius * 2 <= listOfBlocks[i].posy + listOfBlocks[i].height / 4) && ball.yFac > 0)) {
                    ball.yFac *= -1;
                }
                listOfBlocks[i] = Blocks_update(listOfBlocks, i);
                if (listOfBlocks[i].health <= 0) {
                    score += 5 * (listOfBlocks[i].level + 1);
                    for (int j = i; j < numBlocks - 1; j++) {
                        listOfBlocks[j] = listOfBlocks[j + 1];
                    }
                    numBlocks--;
                }
            }
        }

        striker = Striker_update(striker, strikerXFac, WIDTH);

        ball = Ball_update(ball, WIDTH, HEIGHT, striker.posx + striker.width / 2, striker.posy - 10);
        if (ball.posy >= HEIGHT) {
            lives--;
        }

        Striker_display(renderer, striker);
        Ball_display(renderer, ball);
        for (int i = 0; i < numBlocks; i++) {
            Blocks_display(renderer, listOfBlocks, i);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
    }
    Exit(window, renderer, font, listOfBlocks);
    return 0;
}