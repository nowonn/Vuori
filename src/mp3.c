#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "mp3.h"

ma_engine engine;

void AudioMediaPlay(struct AudioMedia* md){
    if(!md->binStart){
        HRSRC res = FindResource(NULL, md->name, RT_RCDATA);
        md->binStart = (char*)LockResource(LoadResource(NULL, res));
        md->size = SizeofResource(NULL, res);
        ma_resource_manager_register_encoded_data(
            ma_engine_get_resource_manager(&engine), md->name,
            md->binStart, md->size);
    }
    ma_engine_play_sound(&engine, md->name, NULL);
}

