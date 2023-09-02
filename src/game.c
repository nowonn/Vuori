#include <math.h>
#include <string.h>
#include "mp3.h"
#include "game.h"
#include "png.h"
#include "tmj.h"

GameState InitializeGameState(void){
    // TODO: use object layer (Tiled) to abstract this
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
    
    sp[398].type = 0; sp[398].exists = false; sp[398].texture = 1;
    sp[398].x = 19.5 * mapS;sp[398].y = 113.5 * mapS; sp[398].z = 20; sp[398].size = 32;
    //3 -> 4
    sp[399].type = 0; sp[399].exists = false; sp[399].texture = 1;
    sp[399].x = 80.5 * mapS;sp[399].y = 86.5 * mapS; sp[399].z = 20; sp[399].size = 32;
    //corridor map 4
    sp[400].type = 0; sp[400].exists = false; sp[400].texture = 1;
    sp[400].x = 111.5 * mapS;sp[400].y = 18.5 * mapS; sp[400].z = 20; sp[400].size = 32;
    //4 -> 5
    sp[401].type = 0; sp[401].exists = false; sp[401].texture = 1;
    sp[401].x = 55.5 * mapS;sp[401].y = 7.5 * mapS; sp[401].z = 20; sp[401].size = 32;//end
    
    sp[402].type = 3; sp[402].exists = true; sp[402].texture = 3;
    sp[402].x = 61.5 * mapS;sp[402].y = 65.5 * mapS; sp[402].z = 20; sp[402].size = 32;
    sp[403].type = 3; sp[403].exists = true; sp[403].texture = 3;
    sp[403].x = 111.5 * mapS;sp[403].y = 107.5 * mapS; sp[403].z = 20; sp[403].size = 32;
    sp[404].type = 3; sp[404].exists = true; sp[404].texture = 3;
    sp[404].x = 19.5 * mapS;sp[404].y = 95.5 * mapS; sp[404].z = 20; sp[404].size = 32;
    sp[305].type = 3; sp[305].exists = true; sp[305].texture = 3;
    sp[305].x = 100.5 * mapS;sp[305].y = 64.5 * mapS; sp[305].z = 20; sp[305].size = 32;
    sp[406].type = 3; sp[406].exists = true; sp[406].texture = 3;
    sp[406].x = 15.5 * mapS;sp[406].y = 42.5 * mapS; sp[406].z = 20; sp[406].size = 32;
    sp[407].type = 3; sp[407].exists = true; sp[407].texture = 3;
    sp[407].x = 102.5 * mapS;sp[407].y = 37.5 * mapS; sp[407].z = 20; sp[407].size = 32;
    sp[408].type = 3; sp[408].exists = true; sp[408].texture = 3;
    sp[408].x = 87.5 * mapS;sp[408].y = 29.5 * mapS; sp[408].z = 20; sp[408].size = 32;
    sp[409].type = 3; sp[409].exists = true; sp[409].texture = 3;
    sp[409].x = 18.5 * mapS;sp[409].y = 6.5 * mapS; sp[409].z = 20; sp[409].size = 32;
    sp[410].type = 3; sp[410].exists = true; sp[410].texture = 3;
    sp[410].x = 124.5 * mapS;sp[410].y = 8.5 * mapS; sp[410].z = 20; sp[410].size = 32;
    sp[411].type = 3; sp[411].exists = true; sp[411].texture = 3;
    sp[411].x = 30.5 * mapS;sp[411].y = 53.5 * mapS; sp[411].z = 20; sp[411].size = 32;
    sp[412].type = 3; sp[412].exists = true; sp[412].texture = 3;
    sp[412].x = 50.5 * mapS;sp[412].y = 3.5 * mapS; sp[412].z = 20; sp[412].size = 32;
    
    sp[413].type = 4; sp[413].exists = true; sp[413].texture = 4;
    sp[413].x = 111.5 * mapS;sp[413].y = 2.5 * mapS; sp[413].z = 20; sp[413].size = 32;
    sp[414].type = 4; sp[414].exists = false; sp[414].texture = 5;
    sp[414].x = 48.5 * mapS;sp[414].y = 36.5 * mapS; sp[414].z = 20; sp[414].size = 32;
    sp[415].type = 4; sp[415].exists = false; sp[415].texture = 6;
    sp[415].x = 106.5 * mapS;sp[415].y = 115.5 * mapS; sp[415].z = 20; sp[415].size = 32;
    sp[416].type = 4; sp[416].exists = false; sp[416].texture = 7;
    sp[416].x = 59.5 * mapS;sp[416].y = 16.5 * mapS; sp[416].z = 20; sp[416].size = 32;
    sp[417].type = 4; sp[417].exists = false; sp[417].texture = 8;
    sp[417].x = 22.5 * mapS;sp[417].y = 16.5 * mapS; sp[417].z = 20; sp[417].size = 32;
    
    /*
sp[b].type = 4; sp[b].exists = false; sp[b].texture = ;
    sp[b].x = .5 * mapS;sp[b].y = .5 * mapS; sp[b].z = 20; sp[b].size = 32;
*/
    
    GameState gs = {
        .playerAngle = 1.2f,
        .framesToMove = 0, .framesToMoveBack = 0,
        .fogDist = 512,
        .bobbing = 0,
        .stepped = false,
        .brightness = 0.6f, .timer = 0,
        .playingAudio = false,
        .mapWalls = malloc(sizeof(int) * 128 * 128),
        .mapFloor = malloc(sizeof(int) * 128 * 128),
        .mapCeiling = malloc(sizeof(int) * 128 * 128),
    };

    int* mapWalls = GetLayerBuffer(&map1, WALLS);
    int* mapFloor = GetLayerBuffer(&map1, FLOOR);
    int* mapCeiling = GetLayerBuffer(&map1, CEILING);

    memcpy(gs.mapWalls, mapWalls, sizeof(int) * 128 * 128);
    memcpy(gs.mapFloor, mapFloor, sizeof(int) * 128 * 128);
    memcpy(gs.mapCeiling, mapCeiling, sizeof(int) * 128 * 128);

    CreateSprites(&gs);
    return gs;
}

void ClearScreen(u32 color){
    u32 *pixel = renderBuffer.pixels;
    
    for (int y = 0; y < renderBuffer.height; y++){
        for (int x = 0; x < renderBuffer.width; x++) *pixel++ = color; 
    }   
}

void CreateSprites(GameState* gs){
    int sprite = 0;
    int spriteX, spriteY;
    int* mapTrees = GetLayerBuffer(&trees, FLOOR);
    //int* mapFloor = GetLayerBuffer(&map1, FLOOR);
    
    for (int floor = 0; floor < mapX*mapY; floor++){
        // This is because mapTrees is only 64x64
        // This means it repeats 4 times
        if(mapTrees[floor%(64*64)] == 1){
            spriteX = (floor%128);
            spriteY = mapY - floor/128;
            
            sp[sprite].type = 1; sp[sprite].texture = 0;
            sp[sprite].x = spriteX * mapS + 32; sp[sprite].y = spriteY * mapS - 32;
            sp[sprite].z = 20; sp[sprite].size = 32;
            
            if (gs->mapFloor[floor + 1] < MAP_GROUND) {
                sp[sprite].exists = 1;
            }
            else {
                sp[sprite].exists = 0;
            }
            
            sprite++;
        }
    }
}

void DrawRectInPixels(int x0, int y0, int x1, int y1, u32 color){
    x0 = clamp(0, x0, renderBuffer.width);
    x1 = clamp(0, x1, renderBuffer.width);
    y0 = renderBuffer.height - y0;
    y1 = renderBuffer.height - y1;
    y0 = clamp(0, y0, renderBuffer.height);
    y1 = clamp(0, y1, renderBuffer.height);
    for (int y = y1; y < y0; y++){
        u32 *pixel = renderBuffer.pixels+x0+renderBuffer.width*y;
        for (int x = x0; x < x1; x++) *pixel++ = color; 
    }
};

void DrawOnScreen(Image* img, int startingX, int startingY, f32 shade, f32 pSize){
    int imgX, imgY;
    const unsigned char* imageMap = GetImageBuffer(img);
    int imgW = GetImageWidth(img), imgH = GetImageHeight(img);
    for (imgY = 0; imgY < imgH; imgY++){
        for (imgX = 0; imgX < imgW; imgX++){
            int pixel = (imgY*imgW + imgX) * 4;
            int red = imageMap[pixel] * shade;
            int green = imageMap[pixel + 1] * shade;
            int blue = imageMap[pixel + 2] * shade;
            int alpha = imageMap[pixel + 3] * shade;
            
            u32 color = createRGB(red, green, blue);
            
            if (alpha != 0) DrawRectInPixels(startingX + imgX * pSize,
                                                    startingY + imgY * pSize,
                                                    startingX + (imgX + 1) * pSize,
                                                    startingY + (imgY + 1) * pSize,
                                                    color);
        }
    }
}
// If we are passing the GameState, all other arguments (except dt) can be removed
void DrawSprites(GameState* gs, v2 playerP, f32 playerAngle, int fogDist, f32 dt, f32 bobbing, f32 brightness){
    int* mapWalls2 = GetLayerBuffer(&map2, WALLS);
    int* mapFloor2 = GetLayerBuffer(&map2, FLOOR);
    int* mapCeiling2 = GetLayerBuffer(&map2, CEILING);

    int* mapWalls3 = GetLayerBuffer(&map3, WALLS);
    int* mapFloor3 = GetLayerBuffer(&map3, FLOOR);
    int* mapCeiling3 = GetLayerBuffer(&map3, CEILING);

    int* mapWalls4 = GetLayerBuffer(&map4, WALLS);
    int* mapFloor4 = GetLayerBuffer(&map4, FLOOR);
    int* mapCeiling4 = GetLayerBuffer(&map4, CEILING);

    int* mapWalls5 = GetLayerBuffer(&map5, WALLS);
    int* mapFloor5 = GetLayerBuffer(&map5, FLOOR);
    int* mapCeiling5 = GetLayerBuffer(&map5, CEILING);

    size_t TEMP_SIZEOF_REPLACER = sizeof(int) * 128 * 128;

    for(int x, y, sprite = 0; sprite < 420; sprite++){
        if (playerAngle > PI && playerAngle < 2 * PI) sprite = 419 - sprite;
        if (sp[sprite].exists == 1){
            if (playerP.x < sp[sprite].x + 30 && playerP.x > sp[sprite].x - 30 && playerP.y < sp[sprite].y + 30 && playerP.y > sp[sprite].y - 30) {
                if (sp[sprite].type == 0){
                    PlayAudio(key);
                    switch(sprite){
                        case 384: 
                        memcpy(gs->mapWalls, mapWalls2, TEMP_SIZEOF_REPLACER);
                        memcpy(gs->mapFloor, mapFloor2, TEMP_SIZEOF_REPLACER);
                        memcpy(gs->mapCeiling, mapCeiling2, TEMP_SIZEOF_REPLACER);
                        sp[385].exists = true;
                        sp[386].exists = true;
                        sp[413].exists = false;
                        sp[414].exists = true;
                        CreateSprites(gs); break;
                        case 385: 
                        gs->mapWalls[109*128+107] = MAP_DOOR; break;
                        case 386:
                        memcpy(gs->mapWalls, mapWalls3, TEMP_SIZEOF_REPLACER);
                        memcpy(gs->mapFloor, mapFloor3, TEMP_SIZEOF_REPLACER);
                        memcpy(gs->mapCeiling, mapCeiling3, TEMP_SIZEOF_REPLACER);
                        sp[398].exists = true;
                        sp[414].exists = false;
                        sp[415].exists = true;
                        CreateSprites(gs); break;
                        case 398:
                        memcpy(gs->mapWalls, mapWalls4, TEMP_SIZEOF_REPLACER);
                        memcpy(gs->mapFloor, mapFloor4, TEMP_SIZEOF_REPLACER);
                        memcpy(gs->mapCeiling, mapCeiling4, TEMP_SIZEOF_REPLACER);
                        /// XXX: temporary hack
                        for (int k = 0; k < 128*128; k++){
                            if (gs->mapWalls[k] == MAP_RAISE_BRICK) gs->mapWalls[k] = 52;
                            if (gs->mapWalls[k] == MAP_RAISE_DOOR) gs->mapWalls[k] = 56;
                            if (gs->mapFloor[k] == MAP_FALL_FLOOR) gs->mapFloor[k] = MAP_GROUND;
                            if (gs->mapCeiling[k] == MAP_RAISE_CEILING) gs->mapCeiling[k] = 55;
                            if (gs->mapCeiling[k] == MAP_FALL_FLOOR) gs->mapCeiling[k] = MAP_GROUND;
                        }
                        ///
                        sp[399].exists = true;
                        sp[415].exists = false;
                        sp[416].exists = true;
                        CreateSprites(gs); break;
                        case 399:
                        for (int k = 0; k < 128*128; k++){
                            if (gs->mapWalls[k] == MAP_BRICK) gs->mapWalls[k] = MAP_EMPTY;
                            /// NOTE: this might not be the intended behaviour
                            if (gs->mapFloor[k] == MAP_GROUND) gs->mapFloor[k] = MAP_WHITE;
                            ///
                            if (gs->mapCeiling[k] == MAP_GROUND) gs->mapCeiling[k] = MAP_EMPTY;
                            
                            if (gs->mapWalls[k] > 50) gs->mapWalls[k] -= 50;
                            /// NOTE: This serves no purpose
                            if (gs->mapFloor[k] > 50) gs->mapFloor[k] -= 50;
                            ///
                            if (gs->mapCeiling[k] > 50) gs->mapCeiling[k] -= 50;
                        }
                        sp[400].exists = true;
                        sp[416].exists = false;
                        break;
                        case 400:
                        memcpy(gs->mapWalls, mapWalls5, TEMP_SIZEOF_REPLACER);
                        memcpy(gs->mapFloor, mapFloor5, TEMP_SIZEOF_REPLACER);
                        memcpy(gs->mapCeiling, mapCeiling5, TEMP_SIZEOF_REPLACER);
                        sp[401].exists = true;
                        sp[417].exists = true;
                        CreateSprites(gs); break;
                        case 401:
                        gameFinish = true; gameState = false; break;
                    }
                    sp[sprite].exists = false;
                } else if (sp[sprite].type == 3 && hp < 3){
                    PlayAudio(heal); hp++;
                    sp[sprite].exists = false;
                } else if (sp[sprite].type == 4){
                    PlayAudio(secret);
                    items++;
                    sp[sprite].exists = false;
                }
            }
        }
        
        b32 isVisible = false;
        f32 spriteX = sp[sprite].x - playerP.x;
        f32 spriteY = sp[sprite].y - playerP.y;
        f32 spriteZ = sp[sprite].z;
        
        f32 CS = cos(playerAngle), SN = sin(playerAngle);
        f32 a = spriteY*CS - spriteX*SN;
        f32 b = spriteX*CS + spriteY*SN;
        spriteX = a; spriteY = b;
        if (b < 1 && b > -1) b = 1;
        
        spriteX = (spriteX*107/spriteY) + (120/2);//120 = rayAmount;
        spriteY = (spriteZ*107/spriteY) + (80/2);//80 = renderBuffer.height/lineWidth
        
        f32 scale = (sp[sprite].size)*80/b;
        if (scale < 0) scale = 0;// if (scale > 160) scale = 160;
        
        f32 textureX = 31.5, textureY = 31, xStep = 32/scale, yStep = 32/scale;
        
        const unsigned char* allSprites = GetImageBuffer(&sprites);
        // 64x144
        if (spriteX >= 0 && spriteX <= 130 && spriteY >= 0 && spriteY <= 240 && sp[sprite].exists == 1)
        {
            for(x = spriteX - scale/2; x < spriteX + scale/2; x++){
                textureY = 31;
                f32 shade = (1 - b / fogDist) * (1 - b / fogDist) * brightness;
                if (shade < 0 || b >= fogDist) shade = 0;
                for(y = 0; y < scale; y++){
                    if (x > 0 && x < 120 && b < depth[x]){
                        isVisible = true;
                        int pixel = ((int)textureY*32 + (int)textureX) * 4 + sp[sprite].texture * 32*32 * 4;
                        int red = allSprites[pixel] * shade;
                        int green = allSprites[pixel + 1] * shade;
                        int blue = allSprites[pixel + 2] * shade;
                        int alpha = allSprites[pixel + 3] * shade;
                        
                        u32 color = createRGB(red, green, blue);
                        
                        if (alpha != 0)
                            DrawRectInPixels((120 - x - 1) * 8,
                                             (spriteY - y) * 8 + sin(bobbing) * 3,
                                             (120 - x) * 8,
                                             (spriteY + 1 - y) * 8 + sin(bobbing) * 3,
                                             color);
                        textureY -= yStep; if (textureY < 0) textureY = 0;
                    }
                }
                
                textureX -= xStep; if (textureX < 0) textureX = 0;
            }
            
            if (sp[sprite].type == 2 && sp[sprite].exists == 1 && isVisible) {
                PlayAudio(follow);
                int gridX = (int)sp[sprite].x >> 6, gridY = mapY - 1 - ((int)sp[sprite].y >> 6);
                int gridXPlus = ((int)sp[sprite].x + 5) >> 6;
                int gridYPlus = mapY - 1 - (((int)sp[sprite].y + 5) >> 6);
                int gridXMinus = ((int)sp[sprite].x - 5) >> 6;
                int gridYMinus = mapY - 1 - (((int)sp[sprite].y - 5) >> 6);
                
                if (sp[sprite].x > playerP.x && gs->mapWalls[gridY * mapX + gridXMinus] == MAP_EMPTY) sp[sprite].x -= (sp[sprite].x - playerP.x) / (1 + abs(dist(sp[sprite].x, sp[sprite].y, playerP.x, playerP.y, 0))) * dt * 125;
                if (sp[sprite].x < playerP.x && gs->mapWalls[gridY * mapX + gridXPlus] == MAP_EMPTY) sp[sprite].x += (playerP.x - sp[sprite].x) / (1 + abs(dist(sp[sprite].x, sp[sprite].y, playerP.x, playerP.y, 0))) * dt * 125;
                if (sp[sprite].y > playerP.y && gs->mapWalls[gridYMinus * mapX + gridX] == MAP_EMPTY) sp[sprite].y -= (sp[sprite].y - playerP.y) / (1 + abs(dist(sp[sprite].x, sp[sprite].y, playerP.x, playerP.y, 0))) * dt * 125;
                if (sp[sprite].y < playerP.y && gs->mapWalls[gridYPlus * mapX + gridX] == MAP_EMPTY) sp[sprite].y += (playerP.y - sp[sprite].y) / (1 + abs(dist(sp[sprite].x, sp[sprite].y, playerP.x, playerP.y, 0))) * dt * 125;
                if (playerP.x < sp[sprite].x + 20 && playerP.x > sp[sprite].x - 20 && playerP.y < sp[sprite].y + 20 && playerP.y > sp[sprite].y - 20) {
                    hp--;
                    PlayAudio(ghost);
                    sp[sprite].exists = 0;
                    if (hp < 1) running = false;
                }
            }
        }
        if (playerAngle > PI && playerAngle < 2 * PI) sprite = 419 - sprite;
    }
}

// TODO: Try to remove lineWidth and rayAmount from here
// (maybe just make it a constant global, that would be fine)
void SimulateGame(int lineWidth, int rayAmount, GameState* gs, Input *input, f32 dt){
    const f32 accel = 1.26f;
    const f32 maxLineHeight = 820;
    const int playerSize = 40;
    const int renderDistance = 16;
    const int FOV = 66;

    if (Pressed(BUTTON_ESCAPE)) running = false;
    
    //int* mapWalls = GetLayerBuffer(&map1, WALLS);
    //int* mapFloor = GetLayerBuffer(&map1, FLOOR);
    //int* mapCeiling = GetLayerBuffer(&map1, CEILING);

    if (gameState){
        f32 speed = 75;
        if (!IsDown(BUTTON_SPRINT)) speed = 50;
        
        if (IsDown(BUTTON_LEFT) || Pressed(BUTTON_LEFT)) {
            gs->playerAngle += 2 * dt;
            if (gs->playerAngle >= 2 * PI) gs->playerAngle -= 2 * PI; 
            gs->playerDP.x = cos(gs->playerAngle);
            gs->playerDP.y = sin(gs->playerAngle);
        }
        // ^ These two are camera rotation v
        if (IsDown(BUTTON_RIGHT) || Pressed(BUTTON_RIGHT)) {
            gs->playerAngle -= 2 * dt;
            if (gs->playerAngle < 0) gs->playerAngle += 2 * PI; 
            gs->playerDP.x = cos(gs->playerAngle);
            gs->playerDP.y = sin(gs->playerAngle);
        }
        
        int playerGridPX = gs->playerP.x/64; //This is for collision detection
        int playerGridPY = mapY - gs->playerP.y/64;
        if (gs->playerDP.x < 0) { gs->xO = -playerSize/2; } else { gs->xO = playerSize/2; }
        if (gs->playerDP.y < 0) { gs->yO = -playerSize/2; } else { gs->yO = playerSize/2; }
        
        if (IsDown(BUTTON_UP) || Pressed(BUTTON_UP)) {
            if (gs->framesToMove == 5) gs->framesToMove++;
            else if (gs->framesToMove < 5) gs->framesToMove += 2;
            if (gs->bobbing < 2*PI) gs->bobbing += speed/4 * dt;
            else gs->bobbing -= 2*PI;
        }
        
        if (IsDown(BUTTON_DOWN) || Pressed(BUTTON_DOWN)) {
            if (gs->framesToMoveBack == 5) gs->framesToMoveBack++;
            else if (gs->framesToMoveBack < 5) gs->framesToMoveBack += 2;
            if (gs->bobbing > 0) gs->bobbing -= speed/4 * dt;
            else gs->bobbing += 2*PI;
        }
        
        if (sin(gs->bobbing) > 0) gs->stepped = false;      

        if (gs->framesToMove > 0){ //Add acceleration :D
            if (gs->mapWalls[playerGridPY * mapX + (int)((gs->playerP.x + gs->xO)/64)] == MAP_EMPTY || gs->mapWalls[playerGridPY * mapX + (int)((gs->playerP.x + gs->xO)/64)] > 50) {
                gs->playerP.x += gs->playerDP.x * dt * speed * pow(accel, gs->framesToMove);
            } // ^ These if statements check if there's a wall in front of you v
            if (gs->mapWalls[(int)(mapY - (gs->playerP.y + gs->yO)/64) * mapX + playerGridPX] == MAP_EMPTY || gs->mapWalls[(int)(mapY - (gs->playerP.y + gs->yO)/64) * mapX + playerGridPX] > 50) {
                gs->playerP.y += gs->playerDP.y * dt * speed * pow(accel, gs->framesToMove);
            }
            
            if (sin(gs->bobbing) < -0.80 && !gs->stepped) {
                // 1 means grass
                // 4 means concrete
                if (gs->mapFloor[playerGridPY * mapX + (int)((gs->playerP.x)/64)] == MAP_GRASS)
                    PlayAudio(grassstep);
                else PlayAudio(concrete);
                gs->stepped = true;
            }
            
            gs->framesToMove--;
        }
        
        if (gs->framesToMoveBack > 0){ //Super smart way to do it, yeah I know B)
            if (gs->mapWalls[playerGridPY * mapX + (int)((gs->playerP.x - gs->xO)/64)] == MAP_EMPTY || gs->mapWalls[playerGridPY * mapX + (int)((gs->playerP.x - gs->xO)/64)] > 50) {
                gs->playerP.x -= gs->playerDP.x * dt * speed * pow(accel, gs->framesToMoveBack);
            }
            if (gs->mapWalls[(int)(mapY - (gs->playerP.y - gs->yO)/64) * mapX + playerGridPX] == MAP_EMPTY ||
                gs->mapWalls[(int)(mapY - (gs->playerP.y - gs->yO)/64) * mapX + playerGridPX] > 50) {
                gs->playerP.y -= gs->playerDP.y * dt * speed * pow(accel, gs->framesToMoveBack);
            }
            
            if (sin(gs->bobbing) < -0.80 && !gs->stepped) {
                if (gs->mapFloor[playerGridPY * mapX + (int)((gs->playerP.x)/64)] == MAP_GRASS)
                    PlayAudio(grassstep);
                else PlayAudio(concrete);
                gs->stepped = true;
            }
            
            gs->framesToMoveBack--;
        }
        
        if (Pressed(BUTTON_INTERACT)){ //Interacting with doors
            if (gs->playerDP.x < 0) { gs->xReach = -playerSize; } else { gs->xReach = playerSize; }
            if (gs->playerDP.y < 0) { gs->yReach = -playerSize; } else { gs->yReach = playerSize; }
            
            if (gs->mapWalls[playerGridPY * mapX + (int)((gs->playerP.x + gs->xReach)/64)] == MAP_DOOR) {
                gs->mapWalls[playerGridPY * mapX + (int)((gs->playerP.x + gs->xReach)/64)] = MAP_EMPTY; 
                PlayAudio(door);
            }
            if (gs->mapWalls[playerGridPX + (int)(mapY - (gs->playerP.y + gs->yReach)/64) * mapX] == MAP_DOOR) {
                gs->mapWalls[playerGridPX + (int)(mapY - (gs->playerP.y + gs->yReach)/64) * mapX] = MAP_EMPTY; 
                PlayAudio(door);
            }
        }
    }
    
    if (mainMenuState){
        gs->playerP.x = 70.5*mapS;
        gs->playerP.y = 60.5*mapS;
        
        gs->playerAngle += dt/6;
        
        if (Pressed(BUTTON_UP) && gs->brightness < 1) gs->brightness += 0.1f;
        if (Pressed(BUTTON_DOWN) && gs->brightness >= 0.1) gs->brightness -= 0.1f;
        if (Pressed(BUTTON_RIGHT)) gs->fogDist += 64;
        if (Pressed(BUTTON_LEFT)) gs->fogDist -= 64;
        
        if (Pressed(BUTTON_INTERACT)) {
            gs->playerAngle = 0;
            gs->playerDP.x = cos(gs->playerAngle);
            gs->playerDP.y = sin(gs->playerAngle);
            
            gs->playerP.x = (mapX - 1) * mapS/2;
            gs->playerP.y = (mapY - 1) * mapS/2;
            
            mainMenuState = false; gameState = true;
        }
    }
    
    ClearScreen(0xb1b1b1);
    
    const unsigned char* skyTexture = GetImageBuffer(&sky);
    int widthS = GetImageWidth(&sky), heightS = GetImageHeight(&sky);
    int xS, yS; //Draw sky
    for (yS = 0; yS < heightS; yS++){
        for (xS = 0; xS < widthS; xS++){
            int xOff = -(int)(gs->playerAngle*360/3.14) - xS;
            if (xOff < 0) xOff += widthS * 10;
            xOff = xOff % widthS;
            int pixel = (yS*widthS + xOff) * 4;
            int red = skyTexture[pixel] * 0.1;
            int green = skyTexture[pixel + 1] * 0.1;
            int blue = skyTexture[pixel + 2] * 0.1;
            
            u32 color = createRGB(red, green, blue);
            
            DrawRectInPixels((widthS - xS - 1) * 4, yS*4, (widthS - xS) * 4, (yS + 1)*4, color);
        }
    }
    
    f64 rayAngle = gs->playerAngle - FOV / 2 * DR;
    if (rayAngle < 0) rayAngle += 2 * PI;
    if (rayAngle >= 2 * PI) rayAngle -= 2 * PI;

    for(int ray = 0; ray < rayAmount; ray++){// for each ray:
        int vMapTexture = 0, hMapTexture = 0;
        
        int dof = 0; //Check for rays that collide with the horizontal parts of the wall
        f32 distH = 727727, hX = gs->playerP.x, hY = gs->playerP.y;
        f32 aTan = -1 / tan(rayAngle);
        /// NOTE: these were previously uninitialized
        f64 rayY = 0, rayX = 0, xOffset = 0, yOffset = 0;
        ///
        if (rayAngle > PI) {
            rayY = (((int)gs->playerP.y >> 6) << 6) -0.0001;
            rayX = (gs->playerP.y - rayY)*aTan + gs->playerP.x;
            yOffset = -64;
            xOffset = -yOffset*aTan;
        }
        
        if (rayAngle < PI) {
            rayY = (((int)gs->playerP.y >> 6) << 6) + 64;
            rayX = (gs->playerP.y - rayY)*aTan + gs->playerP.x;
            yOffset = 64;
            xOffset = -yOffset*aTan;
        }
        
        if (rayAngle == 0 || rayAngle == PI){
            // !!!
            // yOffset may be undefined if rayAngle == PI (rare, but could happen)
            rayX = gs->playerP.x;
            rayY = gs->playerP.y;
            dof = renderDistance;
        }
        
        for (dof = dof; dof < renderDistance; dof++) {
            int mx = (int)(rayX) >> 6;
            int my = (int)(rayY) >> 6;
            int mp = (mapY - 1 - my) * mapX + mx;
            
            if (mp > 0 && mp < mapX*mapY && gs->mapWalls[mp] > MAP_EMPTY && gs->mapWalls[mp] < 50) {
                hMapTexture = gs->mapWalls[mp] - 1;
                dof = renderDistance;
                if (gs->mapWalls[mp] == MAP_DOOR){ rayX += xOffset/3; rayY += yOffset/3; }
                hX = rayX; hY = rayY;
                distH = dist(gs->playerP.x, gs->playerP.y, hX, hY, rayAngle);
            }
            else {
                rayX += xOffset;
                rayY += yOffset;
            }
            if (dof == renderDistance - 1){
                distH = renderDistance*mapS;
            }
        }
        
        dof = 0; //Check for rays that collide with the vertical parts of the wall
        f32 distV = 727727, vX = gs->playerP.x, vY = gs->playerP.y;
        f32 nTan = -tan(rayAngle);
        if (rayAngle > PI/2 && rayAngle < 3 * PI/2) {
            rayX = (((int)gs->playerP.x >> 6) << 6) - 0.0001;
            rayY = (gs->playerP.x - rayX)*nTan + gs->playerP.y;
            xOffset = -64;
            yOffset = -xOffset*nTan;
        }
        
        if (rayAngle < PI/2 || rayAngle > 3 * PI/2) {
            rayX = (((int)gs->playerP.x >> 6) << 6) + 64;
            rayY = (gs->playerP.x - rayX)*nTan + gs->playerP.y;
            xOffset = 64;
            yOffset = -xOffset*nTan;
        }
        
        if (rayAngle == PI/2 || rayAngle == 3 * PI/2){
            rayX = gs->playerP.x;
            rayY = gs->playerP.y;
            dof = renderDistance;
        }
        
        for(dof = dof; dof < renderDistance; dof++) {
            int mx = (int)(rayX) >> 6;
            int my = (int)(rayY) >> 6;
            int mp = (mapY - 1 - my) * mapX + mx;
            
            if (mp > 0 && mp < mapX*mapY && gs->mapWalls[mp] > MAP_EMPTY && gs->mapWalls[mp] < 50) {
                vMapTexture = gs->mapWalls[mp] - 1;
                dof = renderDistance;
                if (gs->mapWalls[mp] == MAP_DOOR){ rayX += xOffset/3; rayY += yOffset/3; }
                vX = rayX; vY = rayY;
                distV = dist(gs->playerP.x, gs->playerP.y, vX, vY, rayAngle);
            }
            else {
                rayX += xOffset;
                rayY += yOffset;
            }
            if (dof == renderDistance - 1){
                distV = renderDistance*mapS;
            } 
        }
        
        b32 hitH = false; //Choose the ray that hits first (horizontal or vertical)
        f64 distance;
        if (distV < distH) { hMapTexture = vMapTexture; rayX = vX; rayY = vY; distance = distV; }
        else { hitH = true; vMapTexture = hMapTexture; rayX = hX; rayY = hY; distance = distH; }
        
        const unsigned char* allTextures = GetImageBuffer(&textures);
        //Draw floor
        int y;// 430 is 320 (half screen height) + 110 (offset)
        for (y = 430; y < maxLineHeight; y++){
            f32 dy = y - (maxLineHeight / 2) - sin(gs->bobbing) * 3;
            f32 rAFix = cos(FixAng(gs->playerAngle - rayAngle));
            
            f32 textureX = gs->playerP.x/2 + cos(rayAngle)*404*32/dy/rAFix;
            f32 textureY = (mapS * mapY - gs->playerP.y)/2 - sin(rayAngle)*404*32/dy/rAFix;
            f32 floorD =  dist(gs->playerP.x/2, (mapY*32 - gs->playerP.y/2), textureX, textureY, rayAngle);
            f32 shade = (1 - floorD / gs->fogDist * 2) * (1 - floorD / gs->fogDist * 2) * gs->brightness * 0.8;
            if (shade < 0 || floorD * 2 >= gs->fogDist) shade = 0;
            
            // NOTE: this might be related to the mapFloor
            int mapValue;
            if ((int)(textureX/32.0) >= mapX || (int)(textureY/32.0) >= mapY || (int)(textureX/32.0) < 0 || (int)(textureY/32.0) < 0 || gs->mapFloor[(int)(textureY/32.0)*mapX + (int)(textureX/32.0)] > 50){
                mapValue = 0;//32*32;
                textureX += mapS*mapX;
                textureY += mapS*mapY;
                textureX = (int)(textureX) % mapX;
                textureY = (int)(textureY) % mapY;
                
            } else {
                // TODO: abstract this within map using name and firsgid
                // (this would require parsing textures, but should be possible with resources)
                // This is minus 1 because there is no transparent thingy anymore
                mapValue = (gs->mapFloor[(int)(textureY/32.0)*mapX + (int)(textureX/32.0)] - 1) * 32*32;
            }
            int pixel = (((int)(textureY)&31) * 32 + ((int)(textureX)&31)) * 4 + mapValue * 4;
            int red = allTextures[pixel] * shade;
            int green = allTextures[pixel + 1] * shade;
            int blue = allTextures[pixel + 2] * shade;
            
            u32 floorColor = createRGB(red, green, blue);
            
            if (floorD < renderDistance * mapS/2) DrawRectInPixels((rayAmount - ray - 1) * lineWidth, y - 110, (rayAmount - ray) * lineWidth, y + 1 - 110, floorColor);
            
            mapValue = (gs->mapCeiling[(int)(textureY/32.0)*mapX + (int)(textureX/32.0)] - 1) * 32*32;
            if (gs->mapCeiling[(int)(textureY/32.0)*mapX + (int)(textureX/32.0)] > 50) mapValue = 0;
            pixel = (((int)(textureY)&31) * 32 + ((int)(textureX)&31)) * 4 + mapValue * 4;
            red = allTextures[pixel] * shade;
            green = allTextures[pixel + 1] * shade;
            blue = allTextures[pixel + 2] * shade;
            
            u32 ceilingColor = createRGB(red, green, blue);
            
            // NOTE: this is where the ceiling is drawn
            if (mapValue > 0 && floorD < renderDistance * mapS/2) 
                DrawRectInPixels((rayAmount - ray - 1) * lineWidth,
                                 maxLineHeight - y - 1 - 110 + sin(gs->bobbing) * 6,
                                 (rayAmount - ray) * lineWidth,
                                 maxLineHeight - y - 110 + sin(gs->bobbing) * 6,
                                 ceilingColor);
        }
        
        //Draw the fake 3d finally
        f32 deltaAngle = gs->playerAngle - rayAngle;
        if (deltaAngle < 0) deltaAngle += 2 * PI;
        if (deltaAngle >= 2 * PI) deltaAngle -= 2 * PI;
        f32 lineHeight = 10;
        if (distance != 727727) distance *= cos(deltaAngle);
        if (distance != 727727) lineHeight = (mapS * maxLineHeight)/distance;
        f32 tYStep = 32.0/(f32)lineHeight;
        f32 tYOffset = 0;
        f32 shade = (1 - distance / gs->fogDist) * (1 - distance / gs->fogDist) * gs->brightness;
        if (shade < 0 || distance >= gs->fogDist) shade = 0;
        
        if (lineHeight > maxLineHeight) { tYOffset = (lineHeight - maxLineHeight) / 2.0; lineHeight = maxLineHeight; }
        f32 lineOffset = (maxLineHeight - lineHeight)/2 - 110 + sin(gs->bobbing) * 3;
        
        f32 textureY = tYOffset * tYStep;
        f32 textureX;
        if (hitH) { textureX = (int)(rayX / 2) % 32; if (rayAngle > PI) { textureX = 31 - textureX; } }
        else { 
            textureX = 31 - ((int)(rayY / 2) % 32);
            if (rayAngle > PI/2 && rayAngle < 3 * PI/2)
                textureX = (int)(rayY / 2) % 32;
        }
        
        depth[ray] = distance;
        
        for (y = 0; y < lineHeight; y++) {
            int pixel = ((int)textureY*32 + (int)textureX) * 4 + (hMapTexture*32*32*4);
            int red = allTextures[pixel] * shade;
            int green = allTextures[pixel + 1] * shade;
            int blue = allTextures[pixel + 2] * shade;
            int alpha = allTextures[pixel + 3] * shade;
            
            u32 wallColor = createRGB(red, green, blue);
            
            if (alpha != 0) DrawRectInPixels((rayAmount - ray - 1) * lineWidth, lineOffset + y, (rayAmount - ray) * lineWidth, lineOffset + y + 1, wallColor);
            textureY += tYStep;
        }
        
        rayAngle += FOV * DR / rayAmount;
        if (rayAngle < 0) rayAngle += 2 * PI;
        if (rayAngle >= 2 * PI) rayAngle -= 2 * PI;
    }
    
    DrawSprites(gs, gs->playerP, gs->playerAngle, gs->fogDist, dt, gs->bobbing, gs->brightness);
    
    if (hp < 3){
        DrawRectInPixels(0, 0, 120 * (3 - hp), 640, 0);
        DrawRectInPixels(960 - 120 * (3 - hp) - 15, 0, 960, 640, 0);
    }
    
    if (mainMenuState){
        DrawOnScreen(&credits, 20, 520, 1, 1);
        DrawOnScreen(&title, 310, 100, 1, 1.5f);
        if ((int)(gs->playerAngle*8)%3) DrawOnScreen(&press_to_start, 160, 380, 1, 1);
    }
    
    if(gameFinish){
        if (items >= 5){
            if (!gs->playingAudio) PlayAudio(victory);
            gs->playingAudio = true;
            DrawOnScreen(&won, 0, 0, 1, 2);
        } else {
            if (!gs->playingAudio) PlayAudio(fail);
            gs->playingAudio = true;
            DrawOnScreen(&finishbad, 0, 0, 0, 2);
            if (gs->timer > 9) DrawOnScreen(&finishbad, 20, 2, 0.6f, 1.88f);
            if (gs->timer > 3) DrawOnScreen(&escaped, 250, 120, 1, 1.88f);
            if (gs->timer > 6) DrawOnScreen(&but, 170, 240, 1, 1.88f);
            gs->timer += dt;
        }
    }
};
