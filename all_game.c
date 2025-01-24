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
SDL_Color DARK_GREEN = {0, 125, 0};
SDL_Color DARK_BLUE_1 = {0, 0, 170};
SDL_Color DARK_BLUE_2 = {0, 0, 60};

int SDL_main() {
    srand((unsigned int)time(NULL));
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Window* window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font* font = TTF_OpenFont("C:/Users/Admin/Documents/Times new roman/timesnewromanpsmt.ttf", 15);
    TTF_Font* gameoverFont = TTF_OpenFont("C:/Users/Admin/Documents/Times new roman/timesnewromanps_italicmt.ttf", 65);
    TTF_Font* pressButtonFont = TTF_OpenFont("C:/Users/Admin/Documents/Times new roman/timesnewromanps_italicmt.ttf", 25);

    int running = 1, lives = 3, score = 0;
    SDL_Rect scoreTextRect, livesTextRect, gameoverTextRect, pressButtonTextRect;
    SDL_Surface* scoreText = TTF_RenderText_Solid(font, "Score : 0", WHITE);
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreText);
    SDL_QueryTexture(scoreTexture, NULL, NULL, &scoreTextRect.w, &scoreTextRect.h);
    scoreTextRect.x = 20;
    scoreTextRect.y = HEIGHT - 50;
    SDL_Surface* livesText = TTF_RenderText_Solid(font, "Lives : 3", WHITE);
    SDL_Texture* livesTexture = SDL_CreateTextureFromSurface(renderer, livesText);
    SDL_QueryTexture(livesTexture, NULL, NULL, &livesTextRect.w, &livesTextRect.h);
    livesTextRect.x = WIDTH - 120;
    livesTextRect.y = HEIGHT - 50;

    SDL_Surface* gameoverText = TTF_RenderText_Solid(gameoverFont, "Game over", RED);
    SDL_Texture* gameoverTexture = SDL_CreateTextureFromSurface(renderer, gameoverText);
    SDL_QueryTexture(gameoverTexture, NULL, NULL, &gameoverTextRect.w, &gameoverTextRect.h);
    gameoverTextRect.x = WIDTH / 2 - 200;
    gameoverTextRect.y = HEIGHT / 2 - 150;
    SDL_Surface* pressButtonText = TTF_RenderText_Solid(pressButtonFont, "Press <space> to restart or <esc> to exit", RED);
    SDL_Texture* pressButtonTexture = SDL_CreateTextureFromSurface(renderer, pressButtonText);
    SDL_QueryTexture(pressButtonTexture, NULL, NULL, &pressButtonTextRect.w, &pressButtonTextRect.h);
    pressButtonTextRect.x = WIDTH / 2 - 215;
    pressButtonTextRect.y = HEIGHT / 2 + 150;

    Striker striker = {WIDTH/2 - 50, HEIGHT - 50, (rand() % 2 + 1) * 50, 5, (rand() % 2 + 1) * 10, WHITE, {striker.posx, striker.posy, striker.width, striker.height}, renderer};
    int strikerXFac = 0;
    Ball ball = {striker.posx + 50, HEIGHT - 60, 4, 5, WHITE, pow((-1), (rand() % 2)) / 2, -1, renderer};

    int blockWidth = rand() % 31 + 20;
    int horizontalGap;
    if (blockWidth % 10 == 0) {
        horizontalGap = 10;
    }
    else {
        horizontalGap = 10 - blockWidth % 10;
    }
    int verticalGap = horizontalGap;
    int blockHeight = 20 - verticalGap;
    int numBlocks = (WIDTH / (blockWidth + horizontalGap)) * (HEIGHT / (2 * (blockHeight + verticalGap)));
    struct Block* temporary = (struct Block*)malloc(sizeof(struct Block) * numBlocks); // создание динамического массива
    if (temporary == NULL) {
        exit(0);
    }
    struct Block* listOfBlocks = temporary;
    Blocks_populating(blockWidth, blockHeight, horizontalGap, verticalGap, renderer, listOfBlocks);

    SDL_Event event;
    while (running) {
        SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, 255);
        SDL_RenderClear(renderer);

        char scores[100];
        strcpy(scores, "Score : ");
        char char_score[sizeof(int)*10];
        sprintf(char_score, "%d", score);
        strcat(scores, char_score);
        scoreText = TTF_RenderText_Solid(font, scores, WHITE);
        scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreText);
        char live[100];
        strcpy(live, "Lives : ");
        char char_lives[sizeof(int)];
        sprintf(char_lives, "%d", lives);
        strcat(live, char_lives);
        livesText = TTF_RenderText_Solid(font, live, WHITE);
        livesTexture = SDL_CreateTextureFromSurface(renderer, livesText);
        SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreTextRect);
        SDL_RenderCopy(renderer, livesTexture, NULL, &livesTextRect);

        if (numBlocks == 0) {
            blockWidth = rand() % 31 + 20;
            if (blockWidth % 10 == 0) {
                horizontalGap = 10;
            }
            else {
                horizontalGap = 10 - blockWidth % 10;
            }
            verticalGap = horizontalGap;
            blockHeight = 20 - verticalGap;
            numBlocks = (WIDTH / (blockWidth + horizontalGap)) * (HEIGHT / (2 * (blockHeight + verticalGap)));
            struct Block* temporary = (struct Block*)realloc(listOfBlocks, sizeof(struct Block) * numBlocks);
            if (temporary == NULL) {
                exit(0);
            }
            listOfBlocks = temporary;
            Blocks_populating(blockWidth, blockHeight, horizontalGap, verticalGap, renderer, listOfBlocks);
        }

        if (lives <= 0) {
            SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, 255);
            SDL_RenderClear(renderer);
            gameoverTextRect.w = 400;
            gameoverTextRect.h = 300;
            SDL_RenderCopy(renderer, gameoverTexture, NULL, &gameoverTextRect);
            SDL_RenderCopy(renderer, pressButtonTexture, NULL, &pressButtonTextRect);
            SDL_RenderPresent(renderer);
            running = Gameover(renderer, font);
            if (running == 0) {
                break;
            }
            lives = 3;
            score = 0;
            blockWidth = rand() % 31 + 20;
            if (blockWidth % 10 == 0) {
                horizontalGap = 10;
            }
            else {
                horizontalGap = 10 - blockWidth % 10;
            }
            verticalGap = horizontalGap;
            blockHeight = 20 - verticalGap;
            numBlocks = (WIDTH / (blockWidth + horizontalGap)) * (HEIGHT / (2 * (blockHeight + verticalGap)));
            struct Block *temporary = (struct Block*)realloc(listOfBlocks, sizeof(struct Block) * numBlocks);
            if (temporary == NULL) {
                exit(0);
            }
            listOfBlocks = temporary;
            Blocks_populating(blockWidth, blockHeight, horizontalGap, verticalGap, renderer, listOfBlocks);
        }

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = 0;
                }
                if (event.key.keysym.sym == SDLK_LEFT) {
                    strikerXFac = -1;
                }
                if (event.key.keysym.sym == SDLK_RIGHT) {
                    strikerXFac = 1;
                }
            }
            if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT) {
                    strikerXFac = 0;
                }
            }
        }

        if (Check_collision(striker.strikerRect, (SDL_Rect){ball.posx, ball.posy, ball.radius * 2, ball.radius * 2})) {
            ball.yFac *= -1;
            ball.xFac = (float)((ball.posx - (striker.posx+striker.width/2))/(float)(striker.width/4));
        }
        for (int i = 0; i < numBlocks; i++) {
            if (Check_collision(listOfBlocks[i].blockRect, (SDL_Rect) { ball.posx, ball.posy, ball.radius * 2, ball.radius * 2 })) {
                if (((ball.posx >= listOfBlocks[i].posx + listOfBlocks[i].width * 3 / 4 && ball.posx <= listOfBlocks[i].posx + listOfBlocks[i].width) && ball.xFac < 0) || ((ball.posx + ball.radius * 2 >= listOfBlocks[i].posx && ball.posx + ball.radius * 2 <= listOfBlocks[i].posx + listOfBlocks[i].width / 4) && ball.xFac > 0)) {
                    ball.xFac *= -1;
                }
                if (((ball.posy >= listOfBlocks[i].posy + listOfBlocks[i].height * 3 / 4 && ball.posy <= listOfBlocks[i].posy + listOfBlocks[i].height) && ball.yFac < 0) || ((ball.posy + ball.radius * 2 >= listOfBlocks[i].posy && ball.posy + ball.radius * 2 <= listOfBlocks[i].posy + listOfBlocks[i].height / 4) && ball.yFac > 0)) {
                    ball.yFac *= -1;
                }
                listOfBlocks[i].health -= listOfBlocks[i].damage;
                if (listOfBlocks[i].level == 1 && listOfBlocks[i].health == 100) {
                    listOfBlocks[i].color = DARK_GREEN;
                }
                else if (listOfBlocks[i].level == 2) {
                    if (listOfBlocks[i].health == 200) {
                        listOfBlocks[i].color = DARK_BLUE_1;
                    }
                    else if (listOfBlocks[i].health == 100) {
                        listOfBlocks[i].color = DARK_BLUE_2;
                    }
                }
                if (listOfBlocks[i].health <= 0) {
                    score += 5 * (listOfBlocks[i].level + 1);
                    for (int j = i; j < numBlocks - 1; j++) {
                        listOfBlocks[j] = listOfBlocks[j + 1];
                    }
                    numBlocks--;
                }
            }
        }

        striker.posx += striker.speed * strikerXFac;
        if (striker.posx <= 0) {
            striker.posx = 0;
        } else if (striker.posx + striker.width >= WIDTH) {
            striker.posx = WIDTH - striker.width;
        }
        striker.strikerRect = (SDL_Rect){striker.posx, striker.posy, striker.width, striker.height};

        if (ball.posx <= 0 || ball.posx >= WIDTH) {
            ball.xFac *= -1;
        }
        if (ball.posy <= 0) {
            ball.yFac *= -1;
        }
        if (ball.posy >= HEIGHT) {
            lives--;
            ball.posx = striker.posx + striker.width / 2;
            ball.posy = striker.posy - 10;
            ball.xFac = pow((-1), (rand() % 2)) / 2;
            ball.yFac = -1;
        }

        ball.posx += ball.xFac * ball.speed;
        ball.posy += ball.yFac * ball.speed;

        Striker_display(renderer, striker);
        Ball_display(renderer, ball);
        for (int i = 0; i < numBlocks; i++) {
            Blocks_display(renderer, listOfBlocks, i);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
    }
    free(listOfBlocks);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}