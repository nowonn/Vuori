/*
TO-DO LIST
- SPRITE DRAW ORDER
- MORE LEVELS AND PORTALS
- dmg animation
- door animations
- include audio in .exe
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include "utils.c"
#include "math.c"
#include "platform_common.c"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "maps/Walls1.map"
#include "maps/Walls2.map"
#include "maps/Walls3.map"
#include "maps/Floor1.map"
#include "maps/Floor2.map"
#include "maps/Floor3.map"
#include "maps/Ceiling1.map"
#include "maps/Ceiling2.map"
#include "maps/Ceiling3.map"
#include "maps/Trees.map"
#include "assets/textures.ppm"
#include "assets/sky.ppm"
#include "assets/sprites.ppm"
#include "assets/credits.ppm"
#include "assets/title.ppm"
#include "assets/press_to_start.ppm"

struct {
    int width, height;
    u32 *pixels;
    BITMAPINFO bitmapInfo;
} typedef RenderBuffer;

global_variable RenderBuffer renderBuffer;

ma_result result;
ma_engine engine;

#include "createsprites.c"
#include "software_rendering.c"
#include "game.c"

#define fps 60
#define frameDelay (1000 / fps)

internal LRESULT CALLBACK windowCallback(HWND window, UINT message, WPARAM wParam, LPARAM lParam){
    LRESULT result = 0;
    
    switch (message){
        case WM_CLOSE:
        case WM_DESTROY: {
            running = false;
        } break;
        case WM_SIZE:{ //Called when window is created
            RECT rect;
            GetWindowRect(window, &rect);
            renderBuffer.width = rect.right - rect.left;
            renderBuffer.height = rect.bottom - rect.top;
            
            if(renderBuffer.pixels){
                VirtualFree(renderBuffer.pixels, 0, MEM_RELEASE);
            }
            renderBuffer.pixels = VirtualAlloc(0, sizeof(u32)*renderBuffer.width*renderBuffer.height, MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE);
            renderBuffer.bitmapInfo.bmiHeader.biSize = sizeof(renderBuffer.bitmapInfo.bmiHeader);
            renderBuffer.bitmapInfo.bmiHeader.biWidth = renderBuffer.width;
            renderBuffer.bitmapInfo.bmiHeader.biHeight = renderBuffer.height;
            renderBuffer.bitmapInfo.bmiHeader.biPlanes = 1;
            renderBuffer.bitmapInfo.bmiHeader.biBitCount = 32;
            renderBuffer.bitmapInfo.bmiHeader.biCompression = BI_RGB;
        } break;
        
        default: result = DefWindowProcA(window, message, wParam, lParam);
    }
    
    return result;
};  

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    WNDCLASSA windowClass = {0};
    windowClass.style = CS_HREDRAW|CS_VREDRAW;
    windowClass.lpfnWndProc = windowCallback;
    
    windowClass.lpszClassName = "Game_Window_Class";
    
    RegisterClassA(&windowClass);
    
    HWND window = CreateWindowExA(0, "Game_Window_Class", "Vuori", WS_VISIBLE|WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 960, 640, 0, 0, 0, 0);
    
    HDC hdc = GetDC(window);
    
    Input input = {0};
    
    LARGE_INTEGER lastCounter;
    QueryPerformanceCounter(&lastCounter);
    
    LARGE_INTEGER frequencyCounter;
    QueryPerformanceFrequency(&frequencyCounter);
    
    f32 lastDt = 0.01666f;
    
    rayAmount = renderBuffer.width / lineWidth;
    
    CreateSprites();
    
    sp[384].type = 0; sp[384].exists = true; sp[384].texture = 1; sp[384].x = 16.5 * mapS;
    sp[384].y = 46.5 * mapS; sp[384].z = 20; sp[384].size = 32;//key map1 -> map2
    sp[385].type = 0; sp[385].exists = false; sp[385].texture = 1; sp[385].x = 5.5 * mapS;
    sp[385].y = 18.5 * mapS; sp[385].z = 20; sp[385].size = 32;//key map2 -> door
    sp[386].type = 0; sp[386].exists = false; sp[386].texture = 1; sp[386].x = 111.5 * mapS;
    sp[386].y = 18.5 * mapS; sp[386].z = 20; sp[386].size = 32;//key map2 -> map3 
    
    sp[387].type = 2; sp[387].exists = true; sp[387].texture = 2; sp[387].x = 18.5 * mapS;sp[387].y = 124.5 * mapS; sp[387].z = 10; sp[387].size = 32;
    sp[388].type = 2; sp[388].exists = true; sp[388].texture = 2; sp[388].x = 124.5 * mapS;sp[388].y = 121.5 * mapS; sp[388].z = 10; sp[388].size = 32;
    sp[389].type = 2; sp[389].exists = true; sp[389].texture = 2; sp[389].x = 78.5 * mapS;sp[389].y = 105.5 * mapS; sp[389].z = 10; sp[389].size = 32;
    sp[390].type = 2; sp[390].exists = true; sp[390].texture = 2; sp[390].x = 18.5 * mapS;sp[390].y = 92.5 * mapS; sp[390].z = 10; sp[390].size = 32;
    sp[391].type = 2; sp[391].exists = true; sp[391].texture = 2; sp[391].x = 121.5 * mapS;sp[391].y = 88.5 * mapS; sp[391].z = 10; sp[391].size = 32;
    sp[392].type = 2; sp[392].exists = true; sp[392].texture = 2; sp[392].x = 52.5 * mapS;sp[392].y = 44.5 * mapS; sp[392].z = 10; sp[392].size = 32;
    sp[393].type = 2; sp[393].exists = true; sp[393].texture = 2; sp[393].x = 16.5 * mapS;sp[393].y = 42.5 * mapS; sp[393].z = 10; sp[393].size = 32;
    sp[394].type = 2; sp[394].exists = true; sp[394].texture = 2; sp[394].x = 8.5 * mapS;sp[394].y = 21.5 * mapS; sp[394].z = 10; sp[394].size = 32;
    sp[395].type = 2; sp[395].exists = true; sp[395].texture = 2; sp[395].x = 75.5 * mapS;sp[395].y = 8.5 * mapS; sp[395].z = 10; sp[395].size = 32;
    sp[396].type = 2; sp[396].exists = true; sp[396].texture = 2; sp[396].x = 23.5 * mapS;sp[396].y = 4.5 * mapS; sp[396].z = 10; sp[396].size = 32;
    sp[397].type = 2; sp[397].exists = true; sp[397].texture = 2; sp[397].x = 113.5 * mapS;sp[397].y = 3.5 * mapS; sp[397].z = 10; sp[397].size = 32;
    //sp[b].type = 2; sp[b].exists = true; sp[b].texture = 2; sp[b].x = 18.5 * mapS;sp[b].y = 124.5 * mapS; sp[b].z = 10; sp[b].size = 32;
    
    result = ma_engine_init(NULL, &engine); //Init audio engine
    if (result != MA_SUCCESS) {
        printf("Failed to initialize audio engine.");
        return -1;
    }
    
    
    while (running){ //Main Loop!
        //Input
        for (int i = 0; i < BUTTON_COUNT; i++) input.buttons[i].changed = false;
        
        MSG message;
        while (PeekMessageA(&message, window, 0, 0, PM_REMOVE)){
            switch (message.message) {
                case WM_SYSKEYDOWN: 
                case WM_SYSKEYUP: 
                case WM_KEYDOWN: 
                case WM_KEYUP: {
                    u32 vkCode = (u32)message.wParam;
                    b32 wasDown = ((message.lParam & (1 << 30)) != 0);
                    b32 isDown = ((message.lParam & (1 << 31)) == 0);
                    
#define ProcessButton(vk, b)\
if (vkCode == vk){\
input.buttons[b].changed = isDown != input.buttons[b].isDown;\
input.buttons[b].isDown = isDown;\
}
                    ProcessButton(VK_LEFT, BUTTON_LEFT);
                    ProcessButton(VK_RIGHT, BUTTON_RIGHT);
                    ProcessButton(VK_UP, BUTTON_UP);
                    ProcessButton(VK_DOWN, BUTTON_DOWN);
                    ProcessButton(0x5A, BUTTON_INTERACT);
                    ProcessButton(0x58, BUTTON_SPRINT);
                    ProcessButton(0x1B, BUTTON_ESCAPE);
                    
                } break;
                default: {
                    TranslateMessage(&message);
                    DispatchMessage(&message);
                }
            }
        }
        
        //Simulation
        SimulateGame(&input, lastDt);
        
        //Render
        StretchDIBits(hdc, 0, 0, renderBuffer.width, renderBuffer.height, 0, 0, renderBuffer.width, renderBuffer.height, renderBuffer.pixels, &renderBuffer.bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
        
        //Get frame time
        LARGE_INTEGER currentCounter;
        QueryPerformanceCounter(&currentCounter);
        
        lastDt = (f32)(currentCounter.QuadPart - lastCounter.QuadPart) / (f32)frequencyCounter.QuadPart;
        
        lastCounter = currentCounter;
        
        if (frameDelay > lastDt){
            Sleep(frameDelay - lastDt);
        }
    }
    
    ma_engine_uninit(&engine); //Uninit audio engine
};