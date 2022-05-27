#pragma once
#ifndef HARDMODE_H_
#define HARDMODE_H_

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>

#define Cols 5
#define Rows 10
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 611
#define BOARD_WIDTH 306
#define BOARD_HEIGHT 611
#define SCREEN_PAD 1
#define TITLE_FONT_SIZE 200
#define FONT_PATH "ShortBaby-Mg2w.ttf"
#define CELL_FONT_SIZE 23
#define GOVER_FONT_SIZE 50
typedef unsigned int Board[Rows][Cols];
static unsigned int STEP_DELAY=500;
static Uint32 start=0,end=0;
static int WINNING_BLOCK=8192;
static int score=0;
static int squareSize = 60;
struct Color {
	int r,g,b,a;
};
struct Position
{
	int x,y;
};
static std::vector <Color> color = {
    {255, 127, 89, 255},
    {224, 74, 69, 255},
    {237, 207, 114, 255},
    {65, 216, 127, 255},
    {54, 63, 135, 255},
    {78, 89, 178, 255},
    {109, 118, 191, 255},
    {84, 47, 132, 255},
    {125, 77, 188, 255},
    {163, 77, 188, 255},
    {176, 109, 196, 255},
    {0, 102, 204, 255},
    {0, 153, 255, 255},
    {51, 153, 255, 255},
    {153, 204, 255, 255},
    {102, 255, 102, 255}
};

void render_game(SDL_Renderer *renderer, Board board, TTF_Font *font);
void handle_move(SDL_Event e, Board board, SDL_Renderer *renderer);
void draw_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Rect rect, SDL_Color color);
void draw_white_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Rect rect);
void display_text(SDL_Renderer *renderer, const char *text, int size);
void merge( Board board,Position idx,SDL_Renderer *renderer, TTF_Font *font);
bool can_merge(Board board);
void delete_empty_block (Board board,SDL_Renderer *renderer, TTF_Font *font);
void move_left(Board board);
void move_right(Board board);
bool is_continue_merge(Board board,Position &idx);
void merge_y (Board board,Position idx,SDL_Renderer *renderer, TTF_Font *font);
void merge_x (Board board,Position idx,SDL_Renderer *renderer, TTF_Font *font);
bool isWinning(Board board);
bool isGameOver(Board board);
void newGame();
void drop_block(Board board,bool &success,bool &nextBlock,Position &idx);
void retry (SDL_Renderer *renderer,int size,SDL_Window *window);
void set_current_time (Uint32 t);
void swap(int a,int b);
void update_score (Board board);
void hammer(SDL_Renderer *renderer,Board board, TTF_Font *font);

#endif