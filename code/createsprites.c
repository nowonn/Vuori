int depth[120];//120 = rayAmount
int mapX = 128, mapY = 128, mapS = 64;
int hp = 3, items = 0;

internal void
CreateSprites(){
    int sprite = 0;
    int spriteX, spriteY;
    int floor;
    
    for (floor = 0; floor < mapX*mapY; floor++){
        if(mapTrees[floor%(32*128)] == 1){
            spriteX = (floor%128);
            spriteY = mapY - (int)(floor/128);
            
            sp[sprite].type = 1; sp[sprite].texture = 0;
            sp[sprite].x = spriteX * mapS + 32; sp[sprite].y = spriteY * mapS - 32;
            sp[sprite].z = 20; sp[sprite].size = 32;
            
            if (mapFloor[floor + 1] < 2) {
                sp[sprite].exists = 1;
            }
            else {
                sp[sprite].exists = 0;
            }
            
            sprite++;
        }
    }
}