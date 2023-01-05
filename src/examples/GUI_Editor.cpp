
void InitializeGUI()
{
    Data->guis.terrainPalatteGUI = {};
    Data->guis.terrainPalatteGUI.position = V2(20,100);
    Data->guis.terrainPalatteGUI.size = V2(100,25);
    Data->guis.terrainPalatteGUI.color = V4(0.2f, 0.4f, 0.2f, 0.85f);
    //Data->guis.terrainPalatteGUI.textPosition = V2(Data->guis.terrainPalatteGUI.position.x + 3, Data->guis.terrainPalatteGUI.position.x + 3);
    Data->guis.terrainPalatteGUI.fmt = "Terrain";
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
}