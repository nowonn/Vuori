#ifndef __TMJ_H__
#define __TMJ_H__

#include <stdbool.h>
#include "pdjson.h"
#include "binary.h"

enum TMJKeys {
    MAP, MAP_LAYER, MAP_TILESET,
    MAP_WIDTH, MAP_HEIGHT, MAP_INFINITE,
    MAP_COMPRESSION_LEVEL, MAP_ORIENTATION,
    MAP_RENDER_ORDER, MAP_TILED_VERSION, MAP_VERSION,
    MAP_TILE_WIDTH, MAP_TILE_HEIGHT,
    MAP_NEXT_LAYER_ID, MAP_NEXT_OBJECT_ID,
    MAP_TYPE, MAP_NOT_SUPPORTED,
    //MAP_TILESET_N, MAP_LAYER_N,

    LAYER_DATA, LAYER_ID, LAYER_VISIBLE,
    LAYER_WIDTH, LAYER_HEIGHT,
    LAYER_X, LAYER_Y,
    LAYER_COMPRESSION, LAYER_ENCODING,
    LAYER_TYPE, LAYER_NAME,
    LAYER_OPACITY,
    LAYER_NOT_SUPPORTED,

    TILESET_FIRST_GID, TILESET_COLUMNS,
    TILESET_TILE_COUNT,
    TILESET_TILE_WIDTH, TILESET_TILE_HEIGHT,
    TILESET_NAME, TILESET_IMAGE,
    TILESET_IMAGE_WIDTH, TILESET_IMAGE_HEIGHT,
    TILESET_MARGIN, TILESET_SPACING,
    TILESET_NOT_SUPPORTED,
};

struct Layer {
    int id;
    int width, height;
    int x, y; // <- Have no idea what the use for this is
    bool visible;
    double opacity;
    char* compression;//[16]; // Uncompressed, zlib or Zstandard (Only zlib supported for now)
    char* encoding;//[16]; // CSV or Base64 (Only Base64 supported for now)
    char* type;//[32]; // Only tilelayer supported for now
    //unsigned int tintColor; // Of type #xxxxxxxx, not yet supported
    // float opacity;
    char* name;//[256];
    char *encodedData;
    int *data; // Base64-zlib converted to int array
};

struct TileSet{
    int firstGid;
    int columns;
    int tileCount;
    int tileWidth, tileHeight;
    char* name;//[256];
    char* image;//[256];
    int imageWidth, imageHeight;
    int margin, spacing;
};

// NOTE: this may be changed later
enum Layers{
    FLOOR = 0, WALLS, CEILING, // This order has to be respected in Tiled
    MAX_LAYERS                   // This means Ceiling on top, then Walls, then Floor
};
#define MAX_TILESETS 8

typedef struct MapMedia {
    const char *binStart;
    unsigned long size;
    const char *name;

    bool initialized;
    int width, height;
    bool infinite;
    int compressionLevel; // Hopefully always -1
    char* orientation;//[32]; // Orthogonal, Isometric, Isometric (Staggered), Hexagonal (Staggered)
    char* renderOrder;//[16]; // Right Down, Right Up, Left Down, Left Up,
    char* tiledVersion;//[16]; // Made for Tiled version 1.10.1
    char* version;//[16]; // Made for version 1.10
    int tileWidth, tileHeight;
    char* type;//[16]; // Only map is supported for now
    int nextLayerId, nextObjectId;

    int layerCounter;
    int tilesetCounter;

    struct Layer* layers;//[MAX_LAYERS]; // Ceiling, Walls and Floor (for now)
    struct TileSet* tilesets;//[MAX_TILESETS];

    void (*load_map)(struct MapMedia*);
    void (*load_layer)(struct MapMedia*, enum Layers);
    void (*unload_layer)(struct MapMedia*, enum Layers);
    void (*unload_map)(struct MapMedia*);
    int* (*get_layer_data)(struct MapMedia*, enum Layers);
} Map;

int Base64Decode(const char *input, size_t input_len, char *output, size_t output_len);
int* BytesToIntegers(const char* input, int input_len, int* output_len);

enum TMJKeys MapMediaLexify(const char* token, enum TMJKeys object);
void MapMediaParse(struct MapMedia* md, json_stream *json, enum TMJKeys object);

void MapMediaLoadMap(struct MapMedia* md);
void MapMediaLoadLayer(struct MapMedia* md, enum Layers ly);
void MapMediaUnloadLayer(struct MapMedia* md, enum Layers ly);
void FreeMap(struct MapMedia* md);
int* MapMediaGetLayerData(struct MapMedia* md, enum Layers ly);
int* GetLayerBuffer(struct MapMedia* md, enum Layers ly);
int GetMapWidth(struct MapMedia* md);
int GetMapHeight(struct MapMedia* md);

#define LoadMap(name) name.load_map(&name)
#define LoadLayer(name, ly) name.load_layer(&name, ly)
#define UnloadMap(name, ly) name.unload_map(&name, ly)
#define UnloadLayer(name, ly) name.unload_layer(&name, ly)

#undef INCLUDE
#define INCLUDE(filename) extern struct MapMedia filename;
#include "tmj_files.h"

#undef DEFINE
#define DEFINE(filename) \
    struct MapMedia filename = { \
        .binStart = NULL, \
        .name = #filename ".tmj", \
        .initialized = false, \
        .load_map = MapMediaLoadMap, \
        .load_layer = MapMediaLoadLayer, \
        .unload_layer = MapMediaUnloadLayer, \
        .unload_map = FreeMap, \
        .get_layer_data = MapMediaGetLayerData, \
    };

#endif

