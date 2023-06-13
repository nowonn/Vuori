int redAmount;
b32 tookDmg;
u32 screenColor;

internal void
ClearScreen(u32 color){
    u32 *pixel = renderBuffer.pixels;
    
    for (int y = 0; y < renderBuffer.height; y++){
        for (int x = 0; x < renderBuffer.width; x++) *pixel++ = color; 
    }   
}

internal void
DrawRectInPixels(int x0, int y0, int x1, int y1, u32 color){
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

internal void
DrawMap(){
    int x;
    int y;
    u32 color;
    for (y = 0; y < mapY; y++){
        for (x = 0; x < mapX; x++){
            if (mapWalls[y*mapX + x] == 1) {color = 0xffffff;} else {color = 0xb1b1b1;}
            DrawRectInPixels(x * mapS, (7 - y) * mapS, (x + 1) * mapS, (8 - y) * mapS, color);
        }
    }
}

internal void
DrawOnScreen(int imageMap[], int imgW, int imgH, int startingX, int startingY, f32 shade){
    int imgX, imgY;
    for (imgY = 0; imgY < imgH; imgY++){
        for (imgX = 0; imgX < imgW; imgX++){
            int pixel = (imgY*imgW + imgX) * 3;
            int red = imageMap[pixel] * shade;
            int green = imageMap[pixel + 1] * shade;
            int blue = imageMap[pixel + 2] * shade;
            
            u32 color = createRGB(red, green, blue);
            
            if (color != 0xff00ff) DrawRectInPixels(startingX + imgX, startingY + imgY,
                                                    startingX + imgX + 1, startingY + imgY + 1,
                                                    color);
        }
    }
}

internal void
DrawSprites(v2 playerP, f32 playerAngle, int fogDist, f32 dt, f32 bobbing){
    int x, y, sprite;
    b32 isTransparent = false;
    
    for(sprite = 0; sprite < 400; sprite++){
        if (sp[sprite].type == 0 && sp[sprite].exists == 1){ 
            if (playerP.x < sp[sprite].x + 30 && playerP.x > sp[sprite].x - 30 && playerP.y < sp[sprite].y + 30 && playerP.y > sp[sprite].y - 30) {
                if (sprite == 384){
                    memcpy(mapWalls, mapWalls2, sizeof(mapWalls));
                    memcpy(mapFloor, mapFloor2, sizeof(mapFloor));
                    memcpy(mapCeiling, mapCeiling2, sizeof(mapCeiling));
                    sp[385].exists = true;
                    sp[386].exists = true;
                    CreateSprites();
                }
                if (sprite == 385){
                    mapWalls[109*128+107] = 7;
                }
                if (sprite == 386){
                    memcpy(mapWalls, mapWalls3, sizeof(mapWalls));
                    memcpy(mapFloor, mapFloor3, sizeof(mapFloor));
                    memcpy(mapCeiling, mapCeiling3, sizeof(mapCeiling));
                    CreateSprites();
                }
                sp[sprite].exists = false;
            }
        }
        if (sp[sprite].type == 2 && sp[sprite].exists == 1) {
            int gridX = (int)sp[sprite].x >> 6, gridY = mapY - 1 - ((int)sp[sprite].y >> 6);
            int gridXPlus = ((int)sp[sprite].x + 5) >> 6;
            int gridYPlus = mapY - 1 - (((int)sp[sprite].y + 5) >> 6);
            int gridXMinus = ((int)sp[sprite].x - 5) >> 6;
            int gridYMinus = mapY - 1 - (((int)sp[sprite].y - 5) >> 6);
            
            if (sp[sprite].x > playerP.x && mapWalls[gridY * mapX + gridXMinus] == 0) sp[sprite].x -= (sp[sprite].x - playerP.x) / (1 + abs(dist(sp[sprite].x, sp[sprite].y, playerP.x, playerP.y, 0))) * dt * 125;
            if (sp[sprite].x < playerP.x && mapWalls[gridY * mapX + gridXPlus] == 0) sp[sprite].x += (playerP.x - sp[sprite].x) / (1 + abs(dist(sp[sprite].x, sp[sprite].y, playerP.x, playerP.y, 0))) * dt * 125;
            if (sp[sprite].y > playerP.y && mapWalls[gridYMinus * mapX + gridX] == 0) sp[sprite].y -= (sp[sprite].y - playerP.y) / (1 + abs(dist(sp[sprite].x, sp[sprite].y, playerP.x, playerP.y, 0))) * dt * 125;
            if (sp[sprite].y < playerP.y && mapWalls[gridYPlus * mapX + gridX] == 0) sp[sprite].y += (playerP.y - sp[sprite].y) / (1 + abs(dist(sp[sprite].x, sp[sprite].y, playerP.x, playerP.y, 0))) * dt * 125;
            if (playerP.x < sp[sprite].x + 20 && playerP.x > sp[sprite].x - 20 && playerP.y < sp[sprite].y + 20 && playerP.y > sp[sprite].y - 20 && !tookDmg) {
                hp--;
                tookDmg = true;
                redAmount = 255;
                screenColor = 0xff0000;
                sp[sprite].exists = 0;
                if (hp < 1) running = false;
            }
            
            if (tookDmg){
                DrawRectInPixels(0, 0, 960, 640, screenColor);
                screenColor = createRGB(redAmount--, 0, 0);
                if (redAmount == 0) tookDmg = false;
            }
        }
        
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
        
        if (spriteX >= 0 && spriteX <= 480 && spriteY >= 0 && spriteY <= 240 && sp[sprite].exists == 1)
        {
            for(x = spriteX - scale/2; x < spriteX + scale/2; x++){
                textureY = 31;
                f32 shade = (1 - b / fogDist) * (1 - b / fogDist) * 0.5;
                if (shade < 0 || b >= fogDist) shade = 0;
                for(y = 0; y < scale; y++){
                    if (x > 0 && x < 120 && b < depth[x]){
                        isTransparent = false;
                        int pixel = ((int)textureY*32 + (int)textureX) * 3 + sp[sprite].texture * 1024 * 3;
                        if (allSprites[pixel] + allSprites[pixel + 1] +  allSprites[pixel + 2] == 765 || shade == 0) isTransparent = true;
                        int red = allSprites[pixel] * shade;
                        int green = allSprites[pixel + 1] * shade;
                        int blue = allSprites[pixel + 2] * shade;
                        
                        u32 color = createRGB(red, green, blue);
                        
                        if (!isTransparent)
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
        }
    }
}