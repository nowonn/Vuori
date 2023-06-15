v2 playerP;
int playerGridPX, playerGridPY;
v2 playerDP;
f32 playerAngle = 1.2;
f32 speed = 75, accel = 1.26;
int framesToMove = 0, framesToMoveBack = 0;
int playerSize = 40;

u32 wallColor;
f32 maxLineHeight = 820;
int lineWidth = 8;
int rayAmount;
int ray, mx, my, mp, dof;
f64 rayX, rayY, rayAngle, xOffset, yOffset, distance;
int xO, yO;
int xReach, yReach;
int renderDistance = 16;
int fogDist = 512;
f32 bobbing = 0;
b32 stepped = false;
f32 brightness = 0.6;

internal void
SimulateGame(Input *input, f32 dt){
    if (Pressed(BUTTON_ESCAPE)) running = false;
    
    if (gameState){
        if (!IsDown(BUTTON_SPRINT)) speed = 50;
        else speed = 75;
        
        if (IsDown(BUTTON_LEFT) || Pressed(BUTTON_LEFT)) {
            playerAngle += 2 * dt;
            if (playerAngle >= 2 * PI) playerAngle -= 2 * PI; 
            playerDP.x = cos(playerAngle);
            playerDP.y = sin(playerAngle);
        }
        // ^ These two are camera rotation v
        if (IsDown(BUTTON_RIGHT) || Pressed(BUTTON_RIGHT)) {
            playerAngle -= 2 * dt;
            if (playerAngle < 0) playerAngle += 2 * PI; 
            playerDP.x = cos(playerAngle);
            playerDP.y = sin(playerAngle);
        }
        
        playerGridPX = playerP.x/64; //This is for collision detection
        playerGridPY = mapY - playerP.y/64;
        if (playerDP.x < 0) { xO = -playerSize/2; } else { xO = playerSize/2; }
        if (playerDP.y < 0) { yO = -playerSize/2; } else { yO = playerSize/2; }
        
        if (IsDown(BUTTON_UP) || Pressed(BUTTON_UP)) {
            if (framesToMove == 5) framesToMove++;
            else if (framesToMove < 5) framesToMove += 2;
            if (bobbing < 2*PI) bobbing += speed/4 * dt;
            else bobbing -= 2*PI;
        }
        
        if (IsDown(BUTTON_DOWN) || Pressed(BUTTON_DOWN)) {
            if (framesToMoveBack == 5) framesToMoveBack++;
            else if (framesToMoveBack < 5) framesToMoveBack += 2;
            if (bobbing < 2*PI) bobbing += speed/4 * dt;
            else bobbing -= 2*PI;
        }
        
        if (sin(bobbing) > 0) stepped = false;
        
        if (framesToMove > 0){ //Add acceleration :D
            if (mapWalls[playerGridPY * mapX + (int)((playerP.x + xO)/64)] == 0) {
                playerP.x += playerDP.x * dt * speed * pow(accel, framesToMove);
            } // ^ These if statements check if there's a wall in front of you v
            if (mapWalls[(int)(mapY - (playerP.y + yO)/64) * mapX + playerGridPX] == 0) {
                playerP.y += playerDP.y * dt * speed * pow(accel, framesToMove);
            }
            
            if (sin(bobbing) < -0.80 && !stepped) {
                if (mapFloor[playerGridPY * mapX + (int)((playerP.x)/64)] == 1)
                    ma_engine_play_sound(&engine, "grassstep.mp3", NULL);
                else ma_engine_play_sound(&engine, "concrete.mp3", NULL);
                stepped = true;
            }
            
            framesToMove--;
        }
        
        if (framesToMoveBack > 0){ //Super smart way to do it, yeah I know B)
            if (mapWalls[playerGridPY * mapX + (int)((playerP.x - xO)/64)] == 0) {
                playerP.x -= playerDP.x * dt * speed * pow(accel, framesToMoveBack);
            }
            if (mapWalls[(int)(mapY - (playerP.y - yO)/64) * mapX + playerGridPX] == 0) {
                playerP.y -= playerDP.y * dt * speed * pow(accel, framesToMoveBack);
            }
            
            if (sin(bobbing) < -0.80 && !stepped) {
                if (mapFloor[playerGridPY * mapX + (int)((playerP.x)/64)] == 1)
                    ma_engine_play_sound(&engine, "grassstep.mp3", NULL);
                else ma_engine_play_sound(&engine, "concrete.mp3", NULL);
                stepped = true;
            }
            
            framesToMoveBack--;
        }
        
        if (Pressed(BUTTON_INTERACT)){ //Interacting with doors
            if (playerDP.x < 0) { xReach = -playerSize; } else { xReach = playerSize; }
            if (playerDP.y < 0) { yReach = -playerSize; } else { yReach = playerSize; }
            
            if (mapWalls[playerGridPY * mapX + (int)((playerP.x + xReach)/64)] == 7) {
                mapWalls[playerGridPY * mapX + (int)((playerP.x + xReach)/64)] = 0; 
                ma_engine_play_sound(&engine, "door.mp3", NULL);
            }
            if (mapWalls[playerGridPX + (int)(mapY - (playerP.y + yReach)/64) * mapX] == 7) {
                mapWalls[playerGridPX + (int)(mapY - (playerP.y + yReach)/64) * mapX] = 0; 
                ma_engine_play_sound(&engine, "door.mp3", NULL);
            }
        }
    }
    
    if (mainMenuState){
        playerP.x = 70.5*mapS;
        playerP.y = 60.5*mapS;
        
        playerAngle += dt/6;
        
        if (Pressed(BUTTON_UP) && brightness < 1) brightness += 0.1;
        if (Pressed(BUTTON_DOWN) && brightness >= 0.1) brightness -= 0.1;
        if (Pressed(BUTTON_RIGHT)) fogDist += 64;
        if (Pressed(BUTTON_LEFT)) fogDist -= 64;
        
        if (Pressed(BUTTON_INTERACT)) {
            playerAngle = 0;
            playerDP.x = cos(playerAngle);
            playerDP.y = sin(playerAngle);
            
            playerP.x = (mapX - 1) * mapS/2;
            playerP.y = (mapY - 1) * mapS/2;
            
            mainMenuState = false; gameState = true;
        }
    }
    
    ClearScreen(0xb1b1b1);
    
    int xS, yS; //Draw sky
    for (yS = 0; yS < 120; yS++){
        for (xS = 0; xS < 240; xS++){
            int xOff = -(int)(playerAngle*360/3.14) - xS;
            if (xOff < 0) xOff += 2400;
            xOff = xOff % 240;
            int pixel = (yS*240 + xOff) * 3;
            int red = skyTexture[pixel] * 0.1;
            int green = skyTexture[pixel + 1] * 0.1;
            int blue = skyTexture[pixel + 2] * 0.1;
            
            u32 color = createRGB(red, green, blue);
            
            DrawRectInPixels((240 - xS - 1) * 4, yS*4, (240 - xS) * 4, (yS + 1)*4, color);
        }
    }
    
    rayAngle = playerAngle - FOV / 2 * DR;
    if (rayAngle < 0) rayAngle += 2 * PI;
    if (rayAngle >= 2 * PI) rayAngle -= 2 * PI;
    
    for(ray = 0; ray < rayAmount; ray++){// for each ray:
        int vMapTexture = 0, hMapTexture = 0;
        
        dof = 0; //Check for rays that collide with the horizontal parts of the wall
        f32 distH = 727727, hX = playerP.x, hY = playerP.y;
        f32 aTan = -1 / tan(rayAngle);
        if (rayAngle > PI) {
            rayY = (((int)playerP.y >> 6) << 6) -0.0001;
            rayX = (playerP.y - rayY)*aTan + playerP.x;
            yOffset = -64;
            xOffset = -yOffset*aTan;
        }
        
        if (rayAngle < PI) {
            rayY = (((int)playerP.y >> 6) << 6) + 64;
            rayX = (playerP.y - rayY)*aTan + playerP.x;
            yOffset = 64;
            xOffset = -yOffset*aTan;
        }
        
        if (rayAngle == 0 || rayAngle == PI){
            rayX = playerP.x;
            rayY = playerP.y;
            dof = renderDistance;
        }
        
        for (dof = dof; dof < renderDistance; dof++) {
            mx = (int)(rayX) >> 6;
            my = (int)(rayY) >> 6;
            mp = (mapY - 1 - my) * mapX + mx;
            
            if (mp > 0 && mp < mapX*mapY && mapWalls[mp] > 0) {
                hMapTexture = mapWalls[mp] - 1;
                dof = renderDistance;
                if (mapWalls[mp] == 7){ rayX += xOffset/3; rayY += yOffset/3; }
                hX = rayX; hY = rayY;
                distH = dist(playerP.x, playerP.y, hX, hY, rayAngle);
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
        f32 distV = 727727, vX = playerP.x, vY = playerP.y;
        f32 nTan = -tan(rayAngle);
        if (rayAngle > PI/2 && rayAngle < 3 * PI/2) {
            rayX = (((int)playerP.x >> 6) << 6) - 0.0001;
            rayY = (playerP.x - rayX)*nTan + playerP.y;
            xOffset = -64;
            yOffset = -xOffset*nTan;
        }
        
        if (rayAngle < PI/2 || rayAngle > 3 * PI/2) {
            rayX = (((int)playerP.x >> 6) << 6) + 64;
            rayY = (playerP.x - rayX)*nTan + playerP.y;
            xOffset = 64;
            yOffset = -xOffset*nTan;
        }
        
        if (rayAngle == PI/2 || rayAngle == 3 * PI/2){
            rayX = playerP.x;
            rayY = playerP.y;
            dof = renderDistance;
        }
        
        for(dof = dof; dof < renderDistance; dof++) {
            mx = (int)(rayX) >> 6;
            my = (int)(rayY) >> 6;
            mp = (mapY - 1 - my) * mapX + mx;
            
            if (mp > 0 && mp < mapX*mapY && mapWalls[mp] > 0) {
                vMapTexture = mapWalls[mp] - 1;
                dof = renderDistance;
                if (mapWalls[mp] == 7){ rayX += xOffset/3; rayY += yOffset/3; }
                vX = rayX; vY = rayY;
                distV = dist(playerP.x, playerP.y, vX, vY, rayAngle);
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
        if (distV < distH) { hMapTexture = vMapTexture; rayX = vX; rayY = vY; distance = distV; }
        else { hitH = true; vMapTexture = hMapTexture; rayX = hX; rayY = hY; distance = distH; }
        
        //Draw floor
        int y;// 430 is 320 (half screen height) + 110 (offset)
        for (y = 430; y < maxLineHeight; y++){
            f32 dy = y - (maxLineHeight / 2) - sin(bobbing) * 3;
            f32 rAFix = cos(FixAng(playerAngle - rayAngle));
            
            f32 textureX = playerP.x/2 + cos(rayAngle)*404*32/dy/rAFix;
            f32 textureY = (mapS * mapY - playerP.y)/2 - sin(rayAngle)*404*32/dy/rAFix;
            f32 floorD =  dist(playerP.x/2, (mapY*32 - playerP.y/2), textureX, textureY, rayAngle);
            f32 shade = (1 - floorD / fogDist * 2) * (1 - floorD / fogDist * 2) * brightness * 0.8;
            if (shade < 0 || floorD * 2 >= fogDist) shade = 0;
            
            int mapValue;
            if ((int)(textureX/32.0) >= mapX || (int)(textureY/32.0) >= mapY || (int)(textureX/32.0) < 0 || (int)(textureY/32.0) < 0){
                mapValue = 1024;
                textureX += mapS*mapX;
                textureY += mapS*mapY;
                textureX = (int)(textureX) % mapX;
                textureY = (int)(textureY) % mapY;
                
            } else {
                mapValue = mapFloor[(int)(textureY/32.0)*mapX + (int)(textureX/32.0)] * 1024;
            }
            int pixel = (((int)(textureY)&31) * 32 + ((int)(textureX)&31)) * 3 + mapValue * 3;
            int red = allTextures[pixel] * shade;
            int green = allTextures[pixel + 1] * shade;
            int blue = allTextures[pixel + 2] * shade;
            
            u32 floorColor = createRGB(red, green, blue);
            
            if (floorD < renderDistance * mapS/2) DrawRectInPixels((rayAmount - ray - 1) * lineWidth, y - 110, (rayAmount - ray) * lineWidth, y + 1 - 110, floorColor);
            
            mapValue = mapCeiling[(int)(textureY/32.0)*mapX + (int)(textureX/32.0)] * 1024;
            pixel = (((int)(textureY)&31) * 32 + ((int)(textureX)&31)) * 3 + mapValue * 3;
            red = allTextures[pixel] * shade;
            green = allTextures[pixel + 1] * shade;
            blue = allTextures[pixel + 2] * shade;
            
            u32 ceilingColor = createRGB(red, green, blue);
            
            if (mapValue > 0 && floorD < renderDistance * mapS/2) 
                DrawRectInPixels((rayAmount - ray - 1) * lineWidth,
                                 maxLineHeight - y - 1 - 110 + sin(bobbing) * 6,
                                 (rayAmount - ray) * lineWidth,
                                 maxLineHeight - y - 110 + sin(bobbing) * 6,
                                 ceilingColor);
        }
        
        //Draw the fake 3d finally
        f32 deltaAngle = playerAngle - rayAngle;
        if (deltaAngle < 0) deltaAngle += 2 * PI;
        if (deltaAngle >= 2 * PI) deltaAngle -= 2 * PI;
        f32 lineHeight = 10;
        if (distance != 727727) distance *= cos(deltaAngle);
        if (distance != 727727) lineHeight = (mapS * maxLineHeight)/distance;
        f32 tYStep = 32.0/(f32)lineHeight;
        f32 tYOffset = 0;
        f32 shade = (1 - distance / fogDist) * (1 - distance / fogDist) * brightness;
        if (shade < 0 || distance >= fogDist) shade = 0;
        
        if (lineHeight > maxLineHeight) { tYOffset = (lineHeight - maxLineHeight) / 2.0; lineHeight = maxLineHeight; }
        f32 lineOffset = (maxLineHeight - lineHeight)/2 - 110 + sin(bobbing) * 3;
        
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
            b32 isTransparent = false;
            int pixel = ((int)textureY*32 + (int)textureX) * 3 + (hMapTexture*32*32*3);
            if (allTextures[pixel] + allTextures[pixel + 1] +  allTextures[pixel + 2] == 765) isTransparent = true;
            int red = allTextures[pixel] * shade;
            int green = allTextures[pixel + 1] * shade;
            int blue = allTextures[pixel + 2] * shade;
            
            wallColor = createRGB(red, green, blue);
            
            if (!isTransparent) DrawRectInPixels((rayAmount - ray - 1) * lineWidth, lineOffset + y, (rayAmount - ray) * lineWidth, lineOffset + y + 1, wallColor);
            textureY += tYStep;
        }
        
        rayAngle += FOV * DR / rayAmount;
        if (rayAngle < 0) rayAngle += 2 * PI;
        if (rayAngle >= 2 * PI) rayAngle -= 2 * PI;
    }
    
    DrawSprites(playerP, playerAngle, fogDist, dt, bobbing, brightness);
    
    if (mainMenuState){
        DrawOnScreen(credits, 358, 64, 20, 520, 1);
        DrawOnScreen(title, 234, 72, 363, 100, 1);
        if ((int)(playerAngle*8)%3) DrawOnScreen(start, 640, 48, 160, 380, 1);
    }
    
    if (hp < 3){
        //DrawRectInPixels(0, 0, 960, 50 * (3 - hp), 0);
        DrawRectInPixels(0, 0, 120 * (3 - hp), 640, 0);
        DrawRectInPixels(960 - 120 * (3 - hp) - 15, 0, 960, 640, 0);
        //DrawRectInPixels(0, 640 - 50 * (3 - hp) - 40, 960, 640, 0);
    }
    
    //int i;
    //for(i = 0; i < hp; i++) DrawRectInPixels(10 + i*40, 10, 40 + i*40, 40, 0xff0000);
};