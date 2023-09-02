#ifndef __GAME_H__
#define __GAME_H__

#include "globals.h"
#include "png.h"
GameState InitializeGameState(void);
void ClearScreen(u32 color);
void CreateSprites(GameState* gs);
void DrawRectInPixels(int x0, int y0, int x1, int y1, u32 color);
void DrawOnScreen(Image* img, int startingX, int startingY, f32 shade, f32 pSize);
void DrawSprites(GameState* gs, v2 playerP, f32 playerAngle, int fogDist, f32 dt, f32 bobbing, f32 brightness);
void SimulateGame(int lineWidth, int rayAmount, GameState* gs, Input *input, f32 dt);

#endif
