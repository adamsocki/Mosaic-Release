

void CameraInit_LE()
{
    Camera* cam = &Game->camera;
    cam->currentSpeed = 0;
    cam->targetSpeed = 20.0f;
    cam->targetTurnSpeed = 160.0f;

}

void Mover_LE()
{
	Camera* cam = &Game->camera;


    if (InputHeld(Keyboard, Input_W))
    {
        cam->currentSpeed = cam->targetSpeed;
        ///player->isWalkingForwardOrBackward = true;
    }
    else if (InputHeld(Keyboard, Input_S))
    {
        cam->currentSpeed = -cam->targetSpeed;
        ///player->isWalkingForwardOrBackward = true;
    }
    else
    {
        cam->currentSpeed = 0;
        ///player->isWalkingForwardOrBackward = false;
    }

    if (InputHeld(Keyboard, Input_A))
    {
        cam->currentTurnSpeed = cam->targetTurnSpeed;
    }
    else if (InputHeld(Keyboard, Input_D))
    {
        cam->currentTurnSpeed = -cam->targetTurnSpeed;
    }
    else
    {
        cam->currentTurnSpeed = 0;
    }

    cam->targetRotY += DegToRad(cam->currentTurnSpeed * Game->deltaTime);
    cam->targetPos.x += cam->currentSpeed * Game->deltaTime * (sinf(cam->targetRotY));
    cam->targetPos.z += cam->currentSpeed * Game->deltaTime * (cosf(cam->targetRotY));

    ///cam->targetPos = player->modelRenderData.position;
    ///cam->targetRotY = player->modelRenderData.rotY;
    ///cam->isWalkingForwardOrBackward = player->isWalkingForwardOrBackward;
}


void MouseLogicEntities(DynamicArray<RayEntityColission>* rayEntityColissions)
{
    EntityTypeBuffer* wallBuffer = &Data->em.buffers[EntityType_Wall];
    Wall* wallEntitiesInBuffer = (Wall*)wallBuffer->entities;
    EntityTypeBuffer* postBuffer = &Data->em.buffers[EntityType_Post];
    Post* postEntitiesInBuffer = (Post*)postBuffer->entities;

    if (!Data->mousePicker.isEntitySelected)
    {
        for (int i = 0; i < 2; i++)
        {
            //ModelRenderData modelRenderData = {};
            Post* entity = (Post*)GetEntity(&Data->em, postEntitiesInBuffer[i].handle);
            if (entity != NULL)
            {
                PerformMouseRayTestOnEntity(entity, rayEntityColissions);

            }
        }

        for (int i = 0; i < wallBuffer->count; i++)
        {
            //ModelRenderData modelRenderData = {};
            Wall* entity = (Wall*)GetEntity(&Data->em, wallEntitiesInBuffer[i].handle);
            if (entity != NULL)
            {
                entity->modelRenderData.sprite = Data->sprites.wall1Texture;
                PerformMouseRayTestOnEntity(entity, rayEntityColissions);
            }
        }
        FindNearestMouseOverArray(*rayEntityColissions);
        SelectNearestWithClick(*rayEntityColissions);
    }
    else
    {
        // control selected entity
        switch (Data->mousePicker.selectedEntity.handle.type)
        {
        case EntityType_Wall:
        {
            Wall* entity = (Wall*)GetEntity(&Data->em, Data->mousePicker.selectedEntity.handle);
            ControlSelectedEntity(entity);
            break;
        }
        case EntityType_Post:
        {
            Post* entity = (Post*)GetEntity(&Data->em, Data->mousePicker.selectedEntity.handle);
            ControlSelectedEntity(entity);
            break;
        }
        default:
        {
            break;
        }
        }
        RayEntityColission entityColission = Data->mousePicker.selectedEntity;
        
        PushBack(rayEntityColissions, entityColission);
        
        //if (InputReleased(Mouse, Input_MouseLeft))
        //{
        //    //entity->modelRenderData.aabbColor = V4(1);
        //    DynamicArrayClear(rayEntityColissions);
        //   // AllocateDynamicArray(rayEntityColissions);
        //    Data->mousePicker.isEntitySelected = false;
        //}
    }


}

void RenderSelection(DynamicArray<RayEntityColission>* rayEntityColissions)
{
    // render moused entity
    if (rayEntityColissions->count > 0)
    {

        
        switch (Data->mousePicker.mouseOverEntity.handle.type)
        {
            case EntityType_Wall:
            {
                Wall* entity = (Wall*)GetEntity(&Data->em, Data->mousePicker.mouseOverEntity.handle);
                RenderSelectedEntityElements(entity);
                break;
            }
            case EntityType_Post:
            {
                Post* entity = (Post*)GetEntity(&Data->em, Data->mousePicker.mouseOverEntity.handle);
                RenderSelectedEntityElements(entity);
                break;
            }
            default:
            {
                break;
            }
        }

        DynamicArrayClear(rayEntityColissions);

        
    }

    
}

void RenderEntities()
{

    EntityTypeBuffer* wallBuffer = &Data->em.buffers[EntityType_Wall];
    Wall* wallEntitiesInBuffer = (Wall*)wallBuffer->entities;
    EntityTypeBuffer* postBuffer = &Data->em.buffers[EntityType_Post];
    Post* postEntitiesInBuffer = (Post*)postBuffer->entities;

    DynamicArray<ModelRenderData> postEntitiesToRender = MakeDynamicArray<ModelRenderData>(&Game->frameMem, 100);
    DynamicArray<ModelRenderData> wallEntitiesToRender = MakeDynamicArray<ModelRenderData>(&Game->frameMem, 100);

    for (int i = 0; i < 2; i++)
    {
        ModelRenderData modelRenderData = {};
        Post* entity = (Post*)GetEntity(&Data->em, postEntitiesInBuffer[i].handle);

        if (entity != NULL)
        {
            modelRenderData = entity->modelRenderData;
        }

        // TODO - WORKING ON NOW if more than one selected, only interact with the closest;
        PushBack(&postEntitiesToRender, modelRenderData);
    }
    for (int i = 0; i < wallBuffer->count; i++)
    {
        ModelRenderData modelRenderData = {};
        Wall* entity = (Wall*)GetEntity(&Data->em, wallEntitiesInBuffer[i].handle);
        if (entity != NULL)
        {
            modelRenderData = entity->modelRenderData;
        }
        PushBack(&wallEntitiesToRender, modelRenderData);

    }

    DrawOBJModels(postEntitiesToRender, Data->sunLight, &Game->postMesh, &Game->modelShader, Data->rm.skyColor, true);
    DrawOBJModels(wallEntitiesToRender, Data->sunLight, &Data->meshes.wall1Mesh, &Game->modelShader, Data->rm.skyColor);
}

void TestRender(DynamicArray<RayEntityColission> *rayEntityColissions)
{
    EntityTypeBuffer* wallBuffer = &Data->em.buffers[EntityType_Wall];
    Wall* wallEntitiesInBuffer = (Wall*)wallBuffer->entities;
    EntityTypeBuffer* postBuffer = &Data->em.buffers[EntityType_Post];
    Post* postEntitiesInBuffer = (Post*)postBuffer->entities;

    DynamicArray<ModelRenderData> postEntitiesToRender = MakeDynamicArray<ModelRenderData>(&Game->frameMem, 100);
    DynamicArray<ModelRenderData> wallEntitiesToRender = MakeDynamicArray<ModelRenderData>(&Game->frameMem, 100);
    

    
  
    bool anEntityIsSelected = false;
    
    if (true)
     {
         
        for (int i = 0; i < 2; i++)
        {
            ModelRenderData modelRenderData = {};
            Post* entity = (Post*)GetEntity(&Data->em, postEntitiesInBuffer[i].handle);         
            
            
            if (entity != NULL)
            {


               // MouseToObjectCollision(entity);
            
                
                
                
                
                modelRenderData = entity->modelRenderData;
            
            
            
            
            }

            // TODO - WORKING ON NOW if more than one selected, only interact with the closest;
            PushBack(&postEntitiesToRender, modelRenderData);
        }
        for (int i = 0; i < wallBuffer->count; i++)
        {
            ModelRenderData modelRenderData = {};
            Wall* entity = (Wall*)GetEntity(&Data->em, wallEntitiesInBuffer[i].handle);
            if (entity != NULL)
            {
               // PerformMouseRayTestOnEntity(entity, rayEntityColissions);

                
                //MouseToObjectCollision(entity);

                modelRenderData = entity->modelRenderData;
            }
            PushBack(&wallEntitiesToRender, modelRenderData);

        }
        DrawOBJModels(postEntitiesToRender, Data->sunLight, &Game->postMesh, &Game->modelShader, Data->rm.skyColor, true);
        DrawOBJModels(wallEntitiesToRender, Data->sunLight, &Data->meshes.wall1Mesh, &Game->modelShader, Data->rm.skyColor);
    }

    FindNearestMouseOverArray(*rayEntityColissions);

    // control selected entity
    if (rayEntityColissions->count > 0)
    {
        switch (Data->mousePicker.mouseOverEntity.handle.type)
        {
            case EntityType_Wall:
            {
                Wall* entity = (Wall*)GetEntity(&Data->em, Data->mousePicker.mouseOverEntity.handle);
                //ControlSelectedEntity(entity);
                break;
            }
            case EntityType_Post:
            {
                Post* entity = (Post*)GetEntity(&Data->em, Data->mousePicker.mouseOverEntity.handle);
                ControlSelectedEntity(entity);
                break;
            }
            default:
            {
                break;
            }
        }
    }

    // render selected entity
    if (rayEntityColissions->count > 0)
    {
        switch (Data->mousePicker.selectedEntity.handle.type)
        {
            case EntityType_Wall:
            {
                Wall* entity = (Wall*)GetEntity(&Data->em, Data->mousePicker.selectedEntity.handle);
                RenderSelectedEntityElements(entity);
                break;
            }
            case EntityType_Post:
            {
                Post* entity = (Post*)GetEntity(&Data->em, Data->mousePicker.selectedEntity.handle);
                RenderSelectedEntityElements(entity);
                break;
            }
            default:
            {
                break;
            }
        }
    }
    
    DeallocateDynamicArray(&postEntitiesToRender);
    DeallocateDynamicArray(&wallEntitiesToRender);
}

void TestRayMouse()
{
    //Camera* cam = &Game->camera;

    //real32 distanceForRay = -500.0f;

    //EntityTypeBuffer* postBuffer = &Data->em.buffers[EntityType_Post];
    //Post* postEntitiesInBuffer = (Post*)postBuffer->entities;
    //vec3 scaledRayPos = V3(Data->mousePicker.mouseRay.x * distanceForRay, Data->mousePicker.mouseRay.y * distanceForRay, Data->mousePicker.mouseRay.z * distanceForRay);

    //Plane testFloorPlane = MakePlane(V3(0), V3(0, 1, 0));

    //Ray rayMouse = {};
    //rayMouse.origin = -cam->pos;
    //rayMouse.direction = scaledRayPos;

    //real32 val = {};
    //bool raycastToPlane =  RaycastPlane(V3(0), V3(0, 1, 0), rayMouse, &val);

    //if (raycastToPlane)
    //{
    //   // Print("Val: %2f", val);
    //}
    //real32 val2 = {};


    //bool rayAABBHit = false;
    //rayAABBHit = RaycastAABB(V2(0), V2(1, 1), rayMouse, &val2);

    //if (rayAABBHit)
    //{
    //    Print("Val2: %2f", val2);
    //}
    //real32 intersection_distance;

    //
    //if (TestRayOBBIntersection(-Game->camera.pos, scaledRayPos, V3(0,0,0), V3(10,10,10), Identity4(), &intersection_distance))
    //{
    //    DrawTextScreenPixel(&Game->serifFont, V2(500, 100), 9, V4(1, 1, 1, 1), false, "modelPos.x %2f", intersection_distance);
    //    DrawTextScreenPixel(&Game->serifFont, V2(500, 130), 9, V4(1, 1, 1, 1), false, "modelPos.y %2f", intersection_distance);
    //    DrawTextScreenPixel(&Game->serifFont, V2(500, 160), 9, V4(1, 1, 1, 1), false, "modelPos.z %2f", intersection_distance);
    //}
    //else
    //{
    //    //entity->modelRenderData.sprite = Data->sprites.fernTexture;
    //}


    //DynamicArray<ModelRenderData> postEntitiesToRender = MakeDynamicArray<ModelRenderData>(&Game->frameMem, 100);
    //for (int i = 0; i < 1; i++)
    //{
    //    ModelRenderData modelRenderData = {};
    //    Post* entity = (Post*)GetEntity(&Data->em, postEntitiesInBuffer[i].handle);
    //    if (entity != NULL)
    //    {

    //        entity->modelRenderData.position.x = scaledRayPos.x - cam->pos.x;
    //        entity->modelRenderData.position.y = scaledRayPos.y - cam->pos.y;
    //        entity->modelRenderData.position.z = scaledRayPos.z - cam->pos.z;
    //        entity->modelRenderData.sprite = Data->sprites.wall1Texture;

    //        modelRenderData = entity->modelRenderData;

    //    }

    //    PushBack(&postEntitiesToRender, modelRenderData);




 
    //   /* DrawTextScreenPixel(&Game->serifFont, V2(500, 100), 9, V4(1, 1, 1, 1), false, "modelPos.x %2f", entity->modelRenderData.position.x);
    //    DrawTextScreenPixel(&Game->serifFont, V2(500, 130), 9, V4(1, 1, 1, 1), false, "modelPos.y %2f", entity->modelRenderData.position.y);
    //    DrawTextScreenPixel(&Game->serifFont, V2(500, 160), 9, V4(1, 1, 1, 1), false, "modelPos.z %2f", entity->modelRenderData.position.z);*/

    //    DrawTextScreenPixel(&Game->serifFont, V2(300, 100), 10, V4(1, 1, 1, 1), false, "camPos.x %2f",cam->pos.x);
    //    DrawTextScreenPixel(&Game->serifFont, V2(300, 130), 10, V4(1, 1, 1, 1), false, "camPos.y %2f",cam->pos.y);
    //    DrawTextScreenPixel(&Game->serifFont, V2(300, 160), 10, V4(1, 1, 1, 1), false, "camPos.z %2f",cam->pos.z);
    //    DrawTextScreenPixel(&Game->serifFont, V2(300, 300), 8, V4(1, 1, 1, 1), false, "targetPos.x %2f", cam->targetPos.x);
    //    DrawTextScreenPixel(&Game->serifFont, V2(300, 330), 8, V4(1, 1, 1, 1), false, "targetPos.y %2f", cam->targetPos.y);
    //    DrawTextScreenPixel(&Game->serifFont, V2(300, 360), 8, V4(1, 1, 1, 1), false, "targetPos.z %2f", cam->targetPos.z);

    //    //DrawTextScreenPixel(&Game->serifFont, V2(400, 190), 10, V4(1, 1, 1, 1), false, guiElement->label);
    //                    

    //}

    //
    //DrawOBJModels(postEntitiesToRender, Data->sunLight, &Game->postMesh, &Game->modelShader, Data->rm.skyColor);
    //DeallocateDynamicArray(&postEntitiesToRender);

}   




void LoadLevel_LE()
{

}

void SaveLevel_LE()
{

}