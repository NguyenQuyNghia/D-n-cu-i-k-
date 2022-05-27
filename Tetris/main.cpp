
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "EasyMode.h"
#include "Menu.h"
#include "HardMode.h"

using namespace std;
int main(int argc,char* argv[])
{
    int mode;
    create_main_menu(mode);
    if (mode==isEasyMode)
    {
        srand(time(0));
        Tetris* tetris=new Tetris();
        const char* title = "Tetris";
        if(tetris->init(title))
        {
            while (tetris->isrunning())
            {
                tetris->setCurrentTime(SDL_GetTicks());
                tetris->handleEvents();
                tetris->gameplay();
                tetris->updateRender();
            }
        }
        else
        {
            cout<<"Fail to init";
        }
        tetris->clean();
    }
    else if (mode==isHardMode)
    {
        srand(time(NULL));
	    newGame();
    }
    
    else 
    {
        SDL_Quit();
    }
    
    
}
