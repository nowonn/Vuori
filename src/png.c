#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include "png.h"

void ImageMediaDecodeData(struct ImageMedia* md){
    if(!md->binStart){
        HRSRC res = FindResource(NULL, md->name, RT_RCDATA);
        md->binStart = LockResource(LoadResource(NULL, res));
        md->size = SizeofResource(NULL, res);
    }
    if(!md->data)
        md->data = stbi_load_from_memory(md->binStart, md->size, &md->width, &md->height, &md->channels, 4);
}

unsigned char* ImageMediaGetData(struct ImageMedia* md){
    md->decode_data(md);
    return md->data;
}

void ImageMediaFreeData(struct ImageMedia* md){
    stbi_image_free(md->data);
    md->data = NULL;
    md->width = 0;
    md->height = 0;
    md->channels = 0;
}

unsigned char* GetImageBuffer(struct ImageMedia* md){
    return md->get_data(md);
}

int GetImageWidth(struct ImageMedia* md){
    return md->decode_data(md),md->width;
}

int GetImageHeight(struct ImageMedia* md){
    return md->decode_data(md),md->height;
}

void FreeImageBuffer(struct ImageMedia* md){
    md->free_data(md);
}

