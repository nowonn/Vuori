#ifndef __PNG_H__
#define __PNG_H__

#include "stb_image.h"
#include "binary.h"

typedef struct ImageMedia {
    const unsigned char *binStart;
    unsigned long size;
    const char *name;

    int width, height, channels;
    unsigned char *data;

    void (*decode_data)(struct ImageMedia*);
    unsigned char* (*get_data)(struct ImageMedia*);
    void (*free_data)(struct ImageMedia*);
} Image;

void ImageMediaDecodeData(struct ImageMedia* md);
unsigned char* ImageMediaGetData(struct ImageMedia* md);
void ImageMediaFreeData(struct ImageMedia* md);
unsigned char* GetImageBuffer(struct ImageMedia* md);
int GetImageWidth(struct ImageMedia* md);
int GetImageHeight(struct ImageMedia* md);
void FreeImageBuffer(struct ImageMedia* md);

// TODO: make a different include for maps
#undef INCLUDE
#define INCLUDE(filename) extern struct ImageMedia filename;
#include "png_files.h"

#undef DEFINE
#define DEFINE(filename) \
    struct ImageMedia filename = { \
        .binStart = NULL, \
        .name = #filename ".png", \
        .data = NULL, \
        .decode_data = ImageMediaDecodeData, \
        .get_data = ImageMediaGetData, \
        .free_data = ImageMediaFreeData, \
    };

#endif

