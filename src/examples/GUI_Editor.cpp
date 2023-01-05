
void InitializeGUI()
{
    Data->guis.terrainPalatteGUI = {};
    Data->guis.terrainPalatteGUI.position = V2(20,100);
    Data->guis.terrainPalatteGUI.size = V2(100,20);
    Data->guis.terrainPalatteGUI.color = V4(0.2f, 0.2f, 0.2f, 0.5f);
}

void InititalizeMouse()
{
    Data->mouse.positionFromInput =  Input->mousePosNormSigned;
    Data->mouse.rect.max = V2(0.125f, 0.125f);
    Data->mouse.rect.min = -V2(0.125f, 0.125f);
}


void UpdateMouseData()
{
    Data->mouse.positionFromInput = Input->mousePosNormSigned;
}

void MouseOverGUI()
{

    

}


void RenderGUI()
{
    DrawGUIScreen(Data->guis.terrainPalatteGUI);
    DrawRectScreen(V2(100.0f, 50.0f),V2(100.0f, 50.0f),V4(0.8f, 0.8f, 0.8f, 0.5f));
    //DrawSpriteScreen(guis, V2(100.0f, 50.0f), 0, &Data->sprites.fernTexture);
}