#include "Menu.h"
#include "HardMode.h"
#include <iostream>
#define isEasyMode 0
#define isHardMode 1
#define isOutGame 2
bool create_main_menu(int &mode)
{
    srand(time(0));
    TTF_Init();
    SDL_Window *window=NULL;
    SDL_Color colorEasy = {0, 0, 0};
    SDL_Color colorHard = {0, 0, 0};
    TTF_Font* Sans = TTF_OpenFont("ShortBaby-Mg2w.ttf", 24);
    SDL_Rect easy_rect; 
    easy_rect.x = 100;  
    easy_rect.y =100; 
    easy_rect.w = 250; 
    easy_rect.h = 100; 
    SDL_Rect hard_rect;
    hard_rect.x=100;
    hard_rect.y=200;
    hard_rect.w=250;
    hard_rect.h=100;
    if (SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
        std::cout<<SDL_GetError();
    }
    else
    {
        window=SDL_CreateWindow("SDL",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640,480,SDL_WINDOW_SHOWN);
        if (window==NULL)
        {
            std::cout<<SDL_GetError();
        }
        else
        {
            SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (render!=NULL)
            {
                SDL_Surface* loadSurf = IMG_Load("bkground.jpg");
				SDL_Texture* background = SDL_CreateTextureFromSurface(render, loadSurf);
                bool quit = false;
                SDL_Event event;
                
                while (!quit)
                {
                    while  (SDL_PollEvent(&event)!=0)
                    {
                        if (event.type==SDL_QUIT)
                        {
                            mode=isOutGame;
                            quit=true;
                            break;
                        }
                        else if (event.type==SDL_MOUSEMOTION)
                        {
                            int xm=event.motion.x;
                            int ym=event.motion.y;
                            if (xm>easy_rect.x&&xm<easy_rect.x+easy_rect.w&&ym>easy_rect.y&&ym<easy_rect.y+easy_rect.h)
                            {
                                colorEasy = {255,255,255};
                                colorHard = {0,0,0};
                            }
                            else if (xm>hard_rect.x&&xm<hard_rect.x+hard_rect.w&&ym>hard_rect.y&&ym<hard_rect.y+hard_rect.h)
                            {
                                colorEasy = {0,0,0};
                                colorHard = {255,255,255};
                            }
                            else
                            {
                                colorEasy = {0,0,0};
                                colorHard = {0,0,0};

                            }
                            break;
                        }
                        else if (event.type==SDL_MOUSEBUTTONDOWN)
                        {
                            if (event.button.button==SDL_BUTTON_LEFT)
                            {
                                int xb=event.button.x;
                                int yb=event.button.y;
                                if (xb>easy_rect.x&&xb<easy_rect.x+easy_rect.w&&yb>easy_rect.y&&yb<easy_rect.y+easy_rect.h)
                                {
                                    mode=isEasyMode;
                                    quit=true;
                                }
                                else if (xb>hard_rect.x&&xb<hard_rect.x+hard_rect.w&&yb>hard_rect.y&&yb<hard_rect.y+hard_rect.h)
                                {
                                    mode=isHardMode;
                                    quit=true;
                                }
                                else
                                {
                                    break;
                                }
                                
                                break;
                            }
                        }
                    }
            
                
                    SDL_RenderCopy(render, background, NULL, NULL);
                    SDL_Surface* surfaceEasy =
                        TTF_RenderText_Solid(Sans, "Easy mode", colorEasy); 
                    SDL_Texture* easy = SDL_CreateTextureFromSurface(render, surfaceEasy);
                    SDL_RenderCopy(render, easy, NULL, &easy_rect);
                    SDL_Surface* surfaceHard =
                        TTF_RenderText_Solid(Sans, "Hard mode", colorHard); 
                    SDL_Texture* hard = SDL_CreateTextureFromSurface(render, surfaceHard);
                    SDL_RenderCopy(render, hard, NULL, &hard_rect);
                    SDL_RenderPresent(render);
                }
            }
        }
    }
    
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}