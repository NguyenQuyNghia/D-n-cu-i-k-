#pragma once
#ifndef EASYMODE_H_
#define EASYMODE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <ctime>
class Tetris
{
public:
    Tetris()
    {

    }
    ~Tetris()
    {

    }
    void setCurrentTime(Uint32 t)
    {
        currentTime=t;
    }
    bool isrunning()
    {
        return running;
    }
    bool isvalid();

    bool init(const char* title);
    void nextTetrimino();
    void handleEvents();
    void setPosRect(SDL_Rect& rect,int x=0,int y=0,int w=BlockW,int h=BlockH);
    void movePosRect(SDL_Rect& rect,int x,int y);
    void gameplay();
    void updateRender();
    void clean();
private:
    enum { ScreenW=432, ScreenH = 600};
    enum {BlockW=36,BlockH=36};
    enum {Lines=15,Cols=10};
    SDL_Window* window=NULL;
    SDL_Renderer* render=NULL;
    SDL_Texture* background=NULL, *blocks=NULL;
    SDL_Rect srcR={0,0,BlockW,BlockH}, destR={0,0,BlockW,BlockH};
    bool running=false;
    int field[Lines][Cols]={0};
    static const int figures[7][4];
    struct Point
    {
        int x,y;
    } items[4],backup[4];
    int color =1;
    int dx=0;
    bool rotate = false;
    unsigned int delay=500;
    Uint32 startTime=0, currentTime=0;
};

#endif