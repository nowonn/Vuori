#ifndef __MP3_H__
#define __MP3_H__

#include "miniaudio.h"
#include "binary.h"

extern ma_engine engine;

struct AudioMedia{
    char *binStart;
    unsigned long size;
    const char *name;

    void (*play)(struct AudioMedia*);
};

void AudioMediaPlay(struct AudioMedia* md);

#define PlayAudio(name) name.play(&name)

#undef INCLUDE
#define INCLUDE(filename) extern struct AudioMedia filename;
#include "mp3_files.h"

#undef DEFINE
#define DEFINE(filename) \
    struct AudioMedia filename = { \
        .binStart = NULL, \
        .name = #filename ".mp3", \
        .play = AudioMediaPlay, \
    };

#endif
