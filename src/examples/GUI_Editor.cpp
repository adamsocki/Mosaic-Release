
void InitializeGUI()
{
    Data->guis.terrainPalatteGUI = (GUI_Box1*)malloc(sizeof(GUI_Box1) * 4);
    Data->guis.guiCount = 0;

    Data->guis.terrainPalatteGUI[0] = {};
    Data->guis.terrainPalatteGUI[0].position = V2(20,100);
    Data->guis.terrainPalatteGUI[0].size = V2(100,25);
    Data->guis.terrainPalatteGUI[0].color = V4(0.2f, 0.4f, 0.2f, 0.45f);
    Data->guis.terrainPalatteGUI[0].colorSelect = V4(0.2f, 0.4f, 0.2f, 0.85f);

    //Data->guis.terrainPalatteGUI.textPosition = V2(Data->guis.terrainPalatteGUI.position.x + 3, Data->guis.terrainPalatteGUI.position.x + 3);
    Data->guis.terrainPalatteGUI[0].fmt = "Terrain";
    Data->guis.terrainPalatteGUI[0].mouseOver = false;
    Data->guis.terrainPalatteGUI[0].elementCount = 3;
    Data->guis.terrainPalatteGUI[0].elements = (GUI_Box1*)malloc(sizeof(GUI_Box1) * Data->guis.terrainPalatteGUI[0].elementCount);
    memset(Data->guis.terrainPalatteGUI[0].elements, 0, sizeof(GUI_Box1));
    Data->guis.guiCount++;

   
}

void InititalizeMouse()
{
    Data->mouse.positionFromInput =  Input->mousePosNormSigned;
    Data->mouse.rect.max = V2(0.125f, 0.125f);
    Data->mouse.rect.min = -V2(0.125f, 0.125f);
}


void UpdateMouseData()
{
    vec2 mousePos = Input->mousePosNormSigned;
    //mousePos.x = (mousePos.x) + Game->screenWidth / 2;
    mousePos.x = (mousePos.x + 1.0f) * Game->screenWidth / 2;
    mousePos.y = (-mousePos.y + 1.0f) * Game->screenHeight / 2;
    Data->mouse.positionFromInput = mousePos;
    //mousePos.y = -(mousePos.y * Game->screenHeight / 2) + Game->screenHeight / 2;
    //mousePos.z = Game->cameraPosition.x
////    DrawSprite(mousePos, V2(1), 0 ,&Data->sprite);
    // DrawTextScreenPixel(&Game->serifFont, V2(300, 300), 20, V4(1), " %.2f", mousePos.y);
    // DrawTextScreenPixel(&Game->serifFont, V2(300, 330), 20, V4(1), " %.2f", Input->mousePosNormSigned.y);
    DrawSpriteScreen(mousePos, V2(20,20), 0 ,&Data->sprites.cursor_red);

}

void MouseOverGUI()
{
    for (int i = 0; i < Data->guis.guiCount; i++)
    {
        bool test1 = PointToSizeTestPixel2D(Data->guis.terrainPalatteGUI[i].size, Data->guis.terrainPalatteGUI[i].position, Data->mouse.positionFromInput);
        if (test1)
        {
            Data->guis.terrainPalatteGUI[i].mouseOver = true;
        }
        else
        {
            Data->guis.terrainPalatteGUI[i].mouseOver = false;
        }
    
        if (InputPressed(Mouse, Input_MouseLeft) && Data->guis.terrainPalatteGUI[i].mouseOver)
        {
            Data->guis.terrainPalatteGUI[i].expanded = !Data->guis.terrainPalatteGUI[i].expanded;
        }
    
    
    
    
    
    }




}


void DrawGUIScreen(GUI_Box guiElement)
{
    if (guiElement.mouseOver)
    {
        DrawRectScreen(guiElement.position, guiElement.size, guiElement.colorSelect);
    }
    else
    {
        DrawRectScreen(guiElement.position, guiElement.size, guiElement.color);
    }

    
    DrawTextScreenPixel(&Game->serifFont, V2(guiElement.position.x + 5, guiElement.position.y - 5), guiElement.size.y / 2, V4(1,1,1,0.3f), false, guiElement.fmt);
}



void RenderGUI()
{
    for (int i = 0; i < Data->guis.guiCount; i++)
    {
        DrawGUIScreen(Data->guis.terrainPalatteGUI[i]);
        if (Data->guis.terrainPalatteGUI[i].expanded)
        {  
            for (int j = 0; j < Data->guis.terrainPalatteGUI[i].elementCount; j++)
            {
                GUI_Box1 *box = Data->guis.terrainPalatteGUI[i].elements[sizeof(GUI_Box1) * j];
                DrawGUIScreen(&box);
            }
        }
    }
}