#pragma once
#ifndef MENU_H_
#define MENU_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <ctime>
#define isEasyMode 0
#define isHardMode 1
bool create_main_menu(int &mode);

#endif