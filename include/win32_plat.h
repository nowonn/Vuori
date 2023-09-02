#ifndef __WIN32_PLAT_H__
#define __WIN32_PLAT_H__

/*
TO-DO LIST
- MORE PORTALS
- dmg animation
- door animations
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "mp3.h"
#include "tmj.h"
#include "game.h"
#include "globals.h"

// TODO: Figure out what to do with the callback variables
extern b32 running;
extern b32 gameState;
extern b32 gameFinish;
extern b32 mainMenuState;
extern RenderBuffer renderBuffer;

extern int buttonAmount;
extern int buttonSelected;
extern u32 buttonColor;

extern int depth[120];//120 = rayAmount
extern const int mapX;
extern const int mapY;
extern const int mapS;
extern int hp;
extern int items;

extern sprite sp[420]; 

LRESULT CALLBACK windowCallback(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

//int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
//int main(void);

#endif
