#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#define fps 60
#define PI 3.1415926535f
#define DR 0.0174533f

// Maybe move most of this to a "utils.c"
#define frameDelay (1000 / fps)
#define clamp(min, val, max) (val < min ? min : (val > max ? max : val))
#define DegToRad(a) (a * PI/180.f)
#define FixAng(a) (a > 2*PI ? a - 2 * PI : (a < 0 ? a + 2 * PI : a))
#define dist(x0, y0, x1, y1, ang) ((f32)sqrt((x1 - (f32)x0) * (x1 - (f32)x0) + (y1 - (f32)y0) * (y1 - (f32)y0)))
#define createRGB(r, g, b) ((((u32)r & 0xff) << 16) + (((u32)g & 0xff) << 8) + ((u32)b & 0xff))
#define getRed(hexValue) (((u32)hexValue >> 16) & 0xFF)
#define getGreen(hexValue) (((u32)hexValue >> 8) & 0xFF)
#define getBlue(hexValue) (((u32)hexValue) & 0xFF)
#define Pressed(b) (input->buttons[b].isDown && input->buttons[b].changed)
#define Released(b) (!input->buttons[b].isDown && input->buttons[b].changed)
#define IsDown(b) (input->buttons[b].isDown)

#define WIN32_LEAN_AND_MEAN

#include <stdint.h>
#include <stdbool.h>
#include <windows.h>

typedef int8_t s8;
typedef uint8_t u8;
typedef int16_t s16;
typedef uint16_t u16;
typedef int32_t s32;
typedef uint32_t u32;
typedef int64_t s64;
typedef uint64_t u64;
typedef float f32;
typedef double f64;

typedef bool b32;

enum Buttons{
    BUTTON_LEFT,
    BUTTON_RIGHT,
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_INTERACT,
    BUTTON_ESCAPE,
    BUTTON_SPRINT,
    BUTTON_COUNT,
};

// Magic numbers:
// Ceiling: 0 (no ceiling), 5 (ceiling)
// Floor: 1 (grass), 4 (concrete)
// Walls: 0 (no wall), 3 (brick wall), 4 (darker brick wall), 7 (doors), 8 (fence), 53 (becomes brick wall when picking up key), 57(becomes door when picking up key)
// Trees: 0 (no tree), 1 (tree !!! THIS HAS NOTHING TO DO WITH THE GRASS TILE)

enum MapTiles{
    MAP_EMPTY = 0,
    MAP_GRASS,
    MAP_BRICK,
    MAP_DARKER_BRICK,
    MAP_GROUND,
    MAP_CEILING,
    MAP_DOOR,
    MAP_FENCE,
    MAP_RAISE_BRICK,
    MAP_FALL_FLOOR,
    MAP_RAISE_CEILING,
    MAP_RAISE_DOOR,
    MAP_WHITE,
};

typedef struct v2{
    union{
        struct{
            f32 x;
            f32 y;
        };
        f32 e[2];
    };
} v2;

typedef struct RenderBuffer{
    int width, height;
    u32 *pixels;
    BITMAPINFO bitmapInfo;
} RenderBuffer;

typedef struct Button{
    b32 isDown;
    b32 changed;
} Button;

typedef struct{
    int mouseX;
    int mouseY;
    Button buttons[BUTTON_COUNT];
} Input;

typedef struct GameState{
    v2 playerP, playerDP;
    int framesToMove, framesToMoveBack;
    int xO, yO;
    int xReach, yReach;
    int fogDist;
    f32 playerAngle, bobbing;
    f32 brightness, timer;
    b32 stepped, playingAudio;

    int* mapWalls;
    int* mapFloor;
    int* mapCeiling;
} GameState;

typedef struct{
    int type;
    int texture;
    b32 exists;
    f32 x, y, z;
    int size;
} sprite; 

extern sprite sp[]; 
extern b32 running;
extern b32 gameState;
extern b32 gameFinish;
extern b32 mainMenuState;
extern RenderBuffer renderBuffer;

extern int buttonAmount, buttonSelected;
extern u32 buttonColor;

extern int depth[120];//120 = rayAmount
extern const int mapX, mapY, mapS;
extern int hp, items;

#endif
