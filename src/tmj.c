#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "tmj.h"
#include "stb_image.h"

int Base64Decode(const char *input, size_t input_len, char *output, size_t output_len) {
    // Base64 characters lookup table
    const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    int input_idx = 0, output_idx = 0;
    unsigned int buffer = 0;
    int bits_remaining = 0;

    while (input_idx < input_len) {
        char c = input[input_idx++];
        if (c == '=') break; // Padding, end of data

        // Find the character's position in the Base64 lookup table
        const char *ptr = strchr(base64_chars, c);
        if (ptr == NULL) {
            // Invalid character, not part of Base64 encoding
            return -1;
        }
        int value = ptr - base64_chars;

        // Append the bits of the current Base64 character to the buffer
        buffer = (buffer << 6) | value;
        bits_remaining += 6;

        // Convert 8 bits at a time to binary and store in the output
        while (bits_remaining >= 8 && output_idx < output_len) {
            bits_remaining -= 8;
            output[output_idx++] = (buffer >> bits_remaining) & 0xFF;
        }
    }

    return output_idx; // Return the length of the decoded binary data
}

int* BytesToIntegers(const char* input, int input_len, int* output_len) {
    if (input_len % sizeof(int) != 0) {
        fprintf(stderr, "Error: Input length is not a multiple of the integer size.\n");
        exit(EXIT_FAILURE);
    }

    *output_len = input_len / sizeof(int);
    int* output_array = malloc(*output_len * sizeof(int));

    for (int i = 0; i < *output_len; i++) {
        output_array[i] = 0;

        // Convert each byte to an integer in little-endian format
        for (int j = 0; j < sizeof(int); j++) {
            output_array[i] |= (unsigned char)input[i * sizeof(int) + j] << (8 * j);
        }
    }

    return output_array;
}

enum TMJKeys MapMediaLexify(const char* token, enum TMJKeys object){
    // NOTE: this might be better written (maintainable) with X-Macros
    switch(object){
        case MAP:
            if(     strcmp(token, "layers"          ) == 0) return MAP_LAYER;
            else if(strcmp(token, "tilesets"        ) == 0) return MAP_TILESET;
            else if(strcmp(token, "width"           ) == 0) return MAP_WIDTH;
            else if(strcmp(token, "height"          ) == 0) return MAP_HEIGHT;
            else if(strcmp(token, "infinite"        ) == 0) return MAP_INFINITE;
            else if(strcmp(token, "compressionlevel") == 0) return MAP_COMPRESSION_LEVEL;
            else if(strcmp(token, "orientation"     ) == 0) return MAP_ORIENTATION;
            else if(strcmp(token, "renderorder"     ) == 0) return MAP_RENDER_ORDER;
            else if(strcmp(token, "tiledversion"    ) == 0) return MAP_TILED_VERSION;
            else if(strcmp(token, "version"         ) == 0) return MAP_VERSION;
            else if(strcmp(token, "tilewidth"       ) == 0) return MAP_TILE_WIDTH;
            else if(strcmp(token, "tileheight"      ) == 0) return MAP_TILE_HEIGHT;
            else if(strcmp(token, "type"            ) == 0) return MAP_TYPE;
            else if(strcmp(token, "nextlayerid"     ) == 0) return MAP_NEXT_LAYER_ID;
            else if(strcmp(token, "nextobjectid"    ) == 0) return MAP_NEXT_OBJECT_ID;
            else return MAP_NOT_SUPPORTED;
        case MAP_LAYER:
            if(     strcmp(token, "data"       ) == 0) return LAYER_DATA;
            else if(strcmp(token, "id"         ) == 0) return LAYER_ID;
            else if(strcmp(token, "visible"    ) == 0) return LAYER_VISIBLE;
            else if(strcmp(token, "opacity"    ) == 0) return LAYER_OPACITY;
            else if(strcmp(token, "width"      ) == 0) return LAYER_WIDTH;
            else if(strcmp(token, "height"     ) == 0) return LAYER_HEIGHT;
            else if(strcmp(token, "x"          ) == 0) return LAYER_X;
            else if(strcmp(token, "y"          ) == 0) return LAYER_Y;
            else if(strcmp(token, "compression") == 0) return LAYER_COMPRESSION;
            else if(strcmp(token, "encoding"   ) == 0) return LAYER_ENCODING;
            else if(strcmp(token, "type"       ) == 0) return LAYER_TYPE;
            else if(strcmp(token, "name"       ) == 0) return LAYER_NAME;
            else return LAYER_NOT_SUPPORTED;
        case MAP_TILESET:
            if(     strcmp(token, "firstgid"   ) == 0) return TILESET_FIRST_GID;
            else if(strcmp(token, "columns"    ) == 0) return TILESET_COLUMNS;
            else if(strcmp(token, "tilecount"  ) == 0) return TILESET_TILE_COUNT;
            else if(strcmp(token, "tilewidth"  ) == 0) return TILESET_TILE_WIDTH;
            else if(strcmp(token, "tileheight" ) == 0) return TILESET_TILE_HEIGHT;
            else if(strcmp(token, "name"       ) == 0) return TILESET_NAME;
            else if(strcmp(token, "image"      ) == 0) return TILESET_IMAGE;
            else if(strcmp(token, "imagewidth" ) == 0) return TILESET_IMAGE_WIDTH;
            else if(strcmp(token, "imageheight") == 0) return TILESET_IMAGE_HEIGHT;
            else if(strcmp(token, "margin"     ) == 0) return TILESET_MARGIN;
            else if(strcmp(token, "spacing"    ) == 0) return TILESET_SPACING;
            else return TILESET_NOT_SUPPORTED;
        default:
            fprintf(stderr,"[%s] invalid object \"%d\".\n", __func__, object);
            exit(EXIT_FAILURE);
    }
}

void MapMediaPrepareParser(struct MapMedia* md, json_stream *json, enum TMJKeys object){
    enum json_type type = json_next(json);
    switch (type) {
        case JSON_STRING:
            size_t str_len; // This includes the NULL terminator
            json_get_string(json, &str_len);
            switch(object){
            }
            break;
        case JSON_ARRAY: // Consumed '['
            while (json_peek(json) != JSON_ARRAY_END && !json_get_error(json))
                MapMediaPrepareParser(md, json, object);
            json_next(json); // Consumed ']'
            break;
        case JSON_OBJECT: // Consumed '{'
            while (json_peek(json) != JSON_OBJECT_END && !json_get_error(json)) {
                json_next(json);

                const char* next_object_str = json_get_string(json, NULL);
                enum TMJKeys next_object = MapMediaLexify(next_object_str, object);

                switch(next_object){
                    case MAP_NOT_SUPPORTED: case LAYER_NOT_SUPPORTED: case TILESET_NOT_SUPPORTED:
                        fprintf(stderr, "[%s] WARNING: (key:value) pair (\"%s\":", __func__, next_object_str);
                }

                MapMediaPrepareParser(md, json, next_object);

                switch(next_object){
                    case MAP_NOT_SUPPORTED:
                        fprintf(stderr, "%s) from %s is not supported.\n", next_object_str, md->name);
                        break;
                    case LAYER_NOT_SUPPORTED:
                        fprintf(stderr, "%s) from Layer %d (%s) is not supported.\n", next_object_str, md->layerCounter, md->name);
                        break;
                    case TILESET_NOT_SUPPORTED:
                        fprintf(stderr, "%s) from Tileset %d (%s) is not supported.\n", next_object_str, md->tilesetCounter, md->name);
                        break;
                }
            }
            switch(object){
                case MAP_LAYER: md->layerCounter++; break;
                case MAP_TILESET: md->tilesetCounter++; break;
            }
            json_next(json); // Consumed '}'
            break;
        case JSON_OBJECT_END: case JSON_ARRAY_END: return;
        case JSON_ERROR:
                fprintf(stderr, "error: %zu: %s\n",
                        json_get_lineno(json),
                        json_get_error(json));
                exit(EXIT_FAILURE);
    }
}

void MapMediaParse(struct MapMedia* md, json_stream *json, enum TMJKeys object){
    enum json_type type = json_next(json);
    switch (type) {
        case JSON_NULL: fprintf(stderr, "[%s] null value for enum \"%d\".\n", __func__, object); break;
        case JSON_TRUE:
            switch(object){
                case MAP_INFINITE: md->infinite = true; break;
                case LAYER_VISIBLE: md->layers[md->layerCounter].visible = true; break;
            }
        case JSON_FALSE:
            switch(object){
                case MAP_INFINITE: md->infinite = false; break;
                case LAYER_VISIBLE: md->layers[md->layerCounter].visible = false; break;
            }
        case JSON_NUMBER:
            double n = json_get_number(json);
            switch(object){
                case MAP_WIDTH: md->width = (int)n; break;
                case MAP_HEIGHT: md->height = (int)n; break;
                case MAP_COMPRESSION_LEVEL: md->compressionLevel = (int)n; break;
                case MAP_TILE_WIDTH: md->tileWidth = (int)n; break;
                case MAP_TILE_HEIGHT: md->tileHeight = (int)n; break;
                case MAP_NEXT_LAYER_ID: md->nextLayerId = (int)n; break;
                case MAP_NEXT_OBJECT_ID: md->nextObjectId = (int)n; break;
                case LAYER_ID: md->layers[md->layerCounter].id = (int)n; break;
                case LAYER_WIDTH: md->layers[md->layerCounter].width = (int)n; break;
                case LAYER_HEIGHT: md->layers[md->layerCounter].height = (int)n; break;
                case LAYER_X: md->layers[md->layerCounter].x = (int)n; break;
                case LAYER_Y: md->layers[md->layerCounter].y = (int)n; break;
                case LAYER_OPACITY: md->layers[md->layerCounter].opacity = n; break;
                case TILESET_FIRST_GID: md->tilesets[md->tilesetCounter].firstGid = (int)n; break;
                case TILESET_COLUMNS: md->tilesets[md->tilesetCounter].columns = (int)n; break;
                case TILESET_TILE_COUNT: md->tilesets[md->tilesetCounter].tileCount = (int)n; break;
                case TILESET_TILE_WIDTH: md->tilesets[md->tilesetCounter].tileWidth = (int)n; break;
                case TILESET_TILE_HEIGHT: md->tilesets[md->tilesetCounter].tileHeight = (int)n; break;
                case TILESET_IMAGE_WIDTH: md->tilesets[md->tilesetCounter].imageWidth = (int)n; break;
                case TILESET_IMAGE_HEIGHT: md->tilesets[md->tilesetCounter].imageHeight = (int)n; break;
                case TILESET_MARGIN: md->tilesets[md->tilesetCounter].margin = (int)n; break;
                case TILESET_SPACING: md->tilesets[md->tilesetCounter].spacing = (int)n; break;
            }
            break;
        case JSON_STRING:
            size_t str_len;
            const char* str = json_get_string(json, &str_len);
            switch(object){
                case MAP_ORIENTATION:
                    md->orientation = malloc(sizeof(char) * str_len);
                    strcpy(md->orientation, str);
                    break;
                case MAP_RENDER_ORDER:
                    md->renderOrder = malloc(sizeof(char) * str_len);
                    strcpy(md->renderOrder, str);
                    break;
                case MAP_TILED_VERSION:
                    md->tiledVersion = malloc(sizeof(char) * str_len);
                    strcpy(md->tiledVersion, str);
                    break;
                case MAP_VERSION:
                    md->version = malloc(sizeof(char) * str_len);
                    strcpy(md->version, str);
                    break;
                case MAP_TYPE:
                    md->type = malloc(sizeof(char) * str_len);
                    strcpy(md->type, str);
                    break;
                case LAYER_DATA:
                    md->layers[md->layerCounter].encodedData = malloc(sizeof(char) * str_len);
                    strcpy(md->layers[md->layerCounter].encodedData, str);
                    break;
                case LAYER_COMPRESSION:
                    md->layers[md->layerCounter].compression = malloc(sizeof(char) * str_len);
                    strcpy(md->layers[md->layerCounter].compression, str);
                    break;
                case LAYER_ENCODING:
                    md->layers[md->layerCounter].encoding = malloc(sizeof(char) * str_len);
                    strcpy(md->layers[md->layerCounter].encoding, str);
                    break;
                case LAYER_TYPE: 
                    md->layers[md->layerCounter].type = malloc(sizeof(char) * str_len);
                    strcpy(md->layers[md->layerCounter].type, str);
                    break;
                case LAYER_NAME:
                    md->layers[md->layerCounter].name = malloc(sizeof(char) * str_len);
                    strcpy(md->layers[md->layerCounter].name, str);
                    break;
                case TILESET_NAME:
                    md->tilesets[md->tilesetCounter].name = malloc(sizeof(char) * str_len);
                    strcpy(md->tilesets[md->tilesetCounter].name, str);
                    break;
                case TILESET_IMAGE:
                    md->tilesets[md->tilesetCounter].image = malloc(sizeof(char) * str_len);
                    strcpy(md->tilesets[md->tilesetCounter].image, str);
                    break;
            }
            break;
        case JSON_ARRAY: // Consumed '['
            while (json_peek(json) != JSON_ARRAY_END && !json_get_error(json))
                MapMediaParse(md, json, object);
            json_next(json); // Consumed ']'
            break;
        case JSON_OBJECT: // Consumed '{'
            while (json_peek(json) != JSON_OBJECT_END && !json_get_error(json)) {
                json_next(json);

                const char* next_object_str = json_get_string(json, NULL);
                enum TMJKeys next_object = MapMediaLexify(next_object_str, object);

                MapMediaParse(md, json, next_object);
            }
            switch(object){
                case MAP_LAYER: md->layerCounter++; break;
                case MAP_TILESET: md->tilesetCounter++; break;
            }
            json_next(json); // Consumed '}'
            break;
        case JSON_OBJECT_END: case JSON_ARRAY_END: return;
    }
}

void MapMediaLoadMap(struct MapMedia* md){
    if(!md->binStart){
        HRSRC res = FindResource(NULL, md->name, RT_RCDATA);
        md->binStart = LockResource(LoadResource(NULL, res));
        md->size = SizeofResource(NULL, res);
    }

    json_stream json;
    json_open_string(&json, md->binStart);
	json_set_streaming(&json, false);

    MapMediaPrepareParser(md, &json, MAP);
    md->layers = calloc(md->layerCounter, sizeof(struct Layer));
    md->tilesets = calloc(md->tilesetCounter, sizeof(struct TileSet));
    md->layerCounter = 0;
    md->tilesetCounter = 0;

    if (json_get_error(&json)) {
        fprintf(stderr, "error: %zu: %s\n",
                json_get_lineno(&json),
                json_get_error(&json));
        exit(EXIT_FAILURE);
    }
    json_close(&json);

    json_open_string(&json, md->binStart);
	json_set_streaming(&json, false);
    MapMediaParse(md, &json, MAP);
    json_close(&json);

    md->initialized = true;
}

void MapMediaLoadLayer(struct MapMedia* md, enum Layers ly){
    if(!md->initialized)
        md->load_map(md);

    if(!md->layers[ly].data){
        size_t base64_len = strlen(md->layers[ly].encodedData);
        // Max output length for Base64 decoding
        size_t max_output_len = (base64_len * 3) / 4;
        // First we decode Base64 to binary, to be able to decompress from zlib
        char* binary_data = malloc(max_output_len);
        int base64_decoded_len = Base64Decode(md->layers[ly].encodedData, base64_len, binary_data, max_output_len);

        if (base64_decoded_len < 0) {
            fprintf(stderr, "Invalid Base64 data from Map \"%s\"!\n", md->name);
            exit(EXIT_FAILURE);
        }

        int zlib_decoded_len;
        char* zlib_decoded_data = stbi_zlib_decode_malloc(binary_data, base64_decoded_len, &zlib_decoded_len);
        int int_array_len;
        md->layers[ly].data = BytesToIntegers(zlib_decoded_data, zlib_decoded_len, &int_array_len);

        free(binary_data);
    }
}

void MapMediaUnloadLayer(struct MapMedia* md, enum Layers ly){
    free(md->layers[ly].data);
    struct Layer tmp = {0};
    memcpy(&md->layers[ly], &tmp, sizeof(tmp));
}

// TODO: make sure png and mp3 also free and zero everything
void FreeMap(struct MapMedia* md){
    for(int i = 0; i < MAX_LAYERS; i++){
        md->unload_layer(md, i);
        free(md->layers[i].encodedData);
    }
    struct MapMedia tmp = {0};
    tmp.name = md->name;
    tmp.load_map = MapMediaLoadMap;
    tmp.load_layer = MapMediaLoadLayer;
    tmp.unload_layer = MapMediaUnloadLayer;
    tmp.unload_map = FreeMap;
    tmp.get_layer_data = MapMediaGetLayerData;
    memcpy(md, &tmp, sizeof(tmp));
}

int* MapMediaGetLayerData(struct MapMedia* md, enum Layers ly){
    md->load_layer(md, ly);
    return md->layers[ly].data;
}

int* GetLayerBuffer(struct MapMedia* md, enum Layers ly){
    return md->get_layer_data(md, ly);
}

int GetMapWidth(struct MapMedia* md){
    return md->load_map(md),md->width;
}

int GetMapHeight(struct MapMedia* md){
    return md->load_map(md),md->height;
}

