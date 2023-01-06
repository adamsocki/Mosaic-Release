
void InitGUI()
{

}

void BuildGUI(const char* str, int32 elementCapacity, bool isParent, bool position, bool size, int32 subCounter1)
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
    guiEntity->hasTransform = true;
    
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
    mousePos.x = (mousePos.x + 1.0f) * Game->screenWidth / 2;
    mousePos.y = (-mousePos.y + 1.0f) * Game->screenHeight / 2;
    Data->mouse.positionFromInput = mousePos;
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
   
}






void RenderGUI(EntityTypeBuffer guiBuffer, GUI* guiEntitiesInBuffer)
{
    for (int i = 0; i < guiBuffer.count; i++)
    {

        GUI* guiElement = (GUI*)GetEntity(&Data->em, guiEntitiesInBuffer[i].handle);

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
            case EntityType_Wall:
            {
                guiElement->label = "Wall";
            } break;
            default:
            {
                guiElement->label = "GUI/NULL";
                break;
            }
        }

        DrawTextScreenPixel(&Game->serifFont, V2(guiElement->position2D.x + 5, guiElement->position2D.y - 5), guiElement->size2D.y / 2, V4(1,1,1,0.3f), false, guiElement->label);

        DrawSpriteScreen(V2(guiElement->position2D.x, guiElement->position2D.y + 30), V2(20, 2o), 0, &Data->sprites.newPlus);

            //DrawSpriteScreen(mousePos, V2(20, 20), 0, &Data->sprites.cursor_red);
        
        if (guiElement->hasTransform)
        {
            // render GUI_Transform
        }
        if (guiElement->hasScale)
        {
            // render GUI_Scale
        }

    }
}