int buttonAmount = 3, buttonSelected = 0;
u32 buttonColor = 0xaa0000;

internal void
MainMenu(Input *input){
    if (Pressed(BUTTON_DOWN)){
        if (buttonSelected < buttonAmount - 1) buttonSelected++;
        else buttonSelected = 0;
    }
    
    if (Pressed(BUTTON_UP)){
        if (buttonSelected > 0) buttonSelected--;
        else buttonSelected = buttonAmount - 1;
    }
    
    if (Pressed(BUTTON_INTERACT) && buttonSelected == 0){
        gameState = true;
        mainMenuState = false;
    }
    
    if (Pressed(BUTTON_ESCAPE)) running = false;
    
    int i;
    for(i = 0; i < buttonAmount; i++){
        if (i == buttonSelected) buttonColor = 0xaa0055;
        else buttonColor = 0xaa0000;
        
        DrawRectInPixels(renderBuffer.width/2 - 200,
                         renderBuffer.height/2 + 100*(i - buttonAmount/2),
                         renderBuffer.width/2 + 200,
                         renderBuffer.height/2 + 100*(i - buttonAmount/2) + 60,
                         buttonColor);
    }
}