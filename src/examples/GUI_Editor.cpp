
void InitGUI()
{
    // Data->guis.entityPalatteGUI = {};
    // Data->guis.entityPalatteGUI = (GUI_Box1*)malloc(sizeof(GUI_Box1) * 40);
}

void BuildGUI(const char *str, int32 elementCapacity, bool isParent)
{
    
    EntityHandle guiHandle = AddEntity(&Data->em, EntityType_GUI);
	GUI* guiEntity = (GUI*)GetEntity(&Data->em, guiHandle);
    guiEntity->handle = guiHandle;
    guiEntity->isParent = true;
    guiEntity->entityType = EntityType_Terrain;
    guiEntity->label = str;
    guiEntity->size2D = V2(100,25);;
    guiEntity->position2D = V2(20,100);
    guiEntity->color = V4(0.2f, 0.4f, 0.2f, 0.45f);
    guiEntity->colorSelect = V4(0.2f, 0.4f, 0.2f, 0.85f);
    guiEntity->entityTypeID = 0;




    // Data->guis.entityPalatteGUI[Data->guis.guiCount].position = V2(20,100);
    
    // Data->guis.entityPalatteGUI[Data->guis.guiCount].size = V2(100,25);
    // Data->guis.entityPalatteGUI[Data->guis.guiCount].color = V4(0.2f, 0.4f, 0.2f, 0.45f);
    // Data->guis.entityPalatteGUI[Data->guis.guiCount].colorSelect = V4(0.2f, 0.4f, 0.2f, 0.85f);
    // Data->guis.entityPalatteGUI[Data->guis.guiCount].fmt = str;
    // Data->guis.entityPalatteGUI[Data->guis.guiCount].mouseOver = false;
    // Data->guis.entityPalatteGUI[Data->guis.guiCount].elementCapacity = elementCapacity;  
    // Data->guis.entityPalatteGUI[Data->guis.guiCount].displayOrder = 0;
    // Data->guis.entityPalatteGUI[Data->guis.guiCount].parentID = parentID;
    // Data->guis.entityPalatteGUI[Data->guis.guiCount].isSub = isSub;

    // Data->guis.guiCount++;
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


void ReOrderGUIs(int32 numberToChange, int32 startingWith)
{

}




void MouseOverGUI(EntityTypeBuffer guiBuffer, GUI* guiEntitiesInBuffer)
{
    for (int i = 0; i < guiBuffer.count; i++)
    {
        GUI* guiEntity = (GUI*)GetEntity(&Data->em, guiEntitiesInBuffer[i].handle);
        bool test1 = PointToSizeTestPixel2D(guiEntity->size2D, guiEntity->position2D, Data->mouse.positionFromInput);
        if (test1)
        {   
            guiEntity->mouseOver = true;
        }
        else
        {
            guiEntity->mouseOver = false;
        }
    
        if (InputPressed(Mouse, Input_MouseLeft) && guiEntity->mouseOver)
        {
            guiEntity->entityTypeID++;
            if (guiEntity->entityTypeID >= EntityType_Count)
            {
                guiEntity->entityTypeID = 0;
            }
            guiEntity->entityType = Data->em.entityTypes[guiEntity->entityTypeID];
        }
    
    
    
    
    
    }




}


void DrawGUIScreen(GUI guiElement)
{

    // order positionMod
//    guiElement.position.y += (guiElement.displayOrder + 30);

   
}






void RenderGUI(EntityTypeBuffer guiBuffer, GUI* guiEntitiesInBuffer)
{
    for (int i = 0; i < guiBuffer.count; i++)
    {

        GUI* guiElement = (GUI*)GetEntity(&Data->em, guiEntitiesInBuffer[i].handle);
        //DrawGUIScreen((GUI*)GetEntity(&Data->em, guiEntitiesInBuffer[i].handle));

        if (guiElement->mouseOver)
        {
            DrawRectScreen(guiElement->position2D, guiElement->size2D, guiElement->colorSelect);
        }
        else
        {
            DrawRectScreen(guiElement->position2D, guiElement->size2D, guiElement->color);
        }

        switch(guiElement->entityType)
        {
            case EntityType_Terrain:
            {
                guiElement->label = "Terrain";
            } break;
            case EntityType_Test:
            {
                guiElement->label = "Stall";
            } break;
            case EntityType_Fern:
            {
                guiElement->label = "Fern";
            } break;
            default:
            {
                guiElement->label = "GUI/NULL";
                break;
            }
        }

        
        DrawTextScreenPixel(&Game->serifFont, V2(guiElement->position2D.x + 5, guiElement->position2D.y - 5), guiElement->size2D.y / 2, V4(1,1,1,0.3f), false, guiElement->label);
        
    }
}