#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include <stdio.h>

int main()
{
    ma_result result;
    ma_engine engine;
    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        printf("Failed to initialize audio engine.");
        return -1;
    }
    
    ma_engine_play_sound(&engine, "echo1.mp3", NULL);
    
    printf("Press Enter to quit...");
    getchar();
    
    ma_engine_uninit(&engine);
    
    return 0;
}