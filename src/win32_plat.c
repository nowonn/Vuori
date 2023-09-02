/*
TO-DO LIST
- MORE PORTALS
- dmg animation
- door animations
*/

#include "win32_plat.h"

// TODO: Figure out what to do with the callback variables
b32 running = true;
b32 gameState = false;
b32 gameFinish = false;
b32 mainMenuState = true;
RenderBuffer renderBuffer;

int buttonAmount = 3, buttonSelected = 0;
u32 buttonColor = 0xaa0000;

int depth[120];//120 = rayAmount
const int mapX = 128, mapY = 128, mapS = 64;
int hp = 3, items = 0;

sprite sp[420]; 

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
//int main(void){
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
    
    int lineWidth = 8;
    int rayAmount = renderBuffer.width / lineWidth;
    
    ma_result result = ma_engine_init(NULL, &engine); //Init audio engine
    if (result != MA_SUCCESS) {
        fprintf(stderr, "Failed to initialize audio engine.");
        exit(EXIT_FAILURE);
    }
    
    GameState gs = InitializeGameState();
    
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
                    //b32 wasDown = ((message.lParam & (1 << 30)) != 0);
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
                    ProcessButton('Z', BUTTON_INTERACT);
                    ProcessButton('X', BUTTON_SPRINT);
                    ProcessButton(VK_ESCAPE, BUTTON_ESCAPE);
                    
                } break;
                default: {
                    TranslateMessage(&message);
                    DispatchMessage(&message);
                }
            }
        }
        
        //Simulation
        SimulateGame(lineWidth, rayAmount, &gs, &input, lastDt);
        
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

LRESULT CALLBACK windowCallback(HWND window, UINT message, WPARAM wParam, LPARAM lParam){
    LRESULT result = 0;
    
    switch (message){
        case WM_CLOSE:
        case WM_DESTROY: {
            running = false;
        } break;
        case WM_SIZE:{ //Called when window is created
            // TODO: This HAS to be fixed soon
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
