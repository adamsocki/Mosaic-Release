

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



void TestRender()
{
    EntityTypeBuffer* wallBuffer = &Data->em.buffers[EntityType_Wall];
    Wall* wallEntitiesInBuffer = (Wall*)wallBuffer->entities;
    EntityTypeBuffer* postBuffer = &Data->em.buffers[EntityType_Post];
    Post* postEntitiesInBuffer = (Post*)postBuffer->entities;

    DynamicArray<ModelRenderData> postEntitiesToRender = MakeDynamicArray<ModelRenderData>(&Game->frameMem, 100);
    DynamicArray<ModelRenderData> wallEntitiesToRender = MakeDynamicArray<ModelRenderData>(&Game->frameMem, 100);
     if (Data->le.currentLevel == -1 || Data->le.currentLevel == 0)
     {
         
        for (int i = 0; i < postBuffer->count; i++)
        {
            ModelRenderData modelRenderData = {};
            Post* entity = (Post*)GetEntity(&Data->em, postEntitiesInBuffer[i].handle);
            modelRenderData = entity->modelRenderData;
            PushBack(&postEntitiesToRender, modelRenderData);
        }
        for (int i = 0; i < wallBuffer->count; i++)
        {
            ModelRenderData modelRenderData = {};
            Wall* entity = (Wall*)GetEntity(&Data->em, wallEntitiesInBuffer[i].handle);
            modelRenderData = entity->modelRenderData;
            PushBack(&wallEntitiesToRender, modelRenderData);

        }
        DrawOBJModels(postEntitiesToRender, Data->sunLight, &Game->postMesh, &Data->sprites.wall1Texture, &Game->modelShader, Data->rm.skyColor);



        
        DrawOBJModels(wallEntitiesToRender, Data->sunLight, &Data->meshes.wall1Mesh, &Data->sprites.wall1Texture, &Game->modelShader, Data->rm.skyColor);
    }
    
    DeallocateDynamicArray(&postEntitiesToRender);
    DeallocateDynamicArray(&wallEntitiesToRender);

}


void TestRayMouse()
{
    Camera* cam = &Game->camera;

    real32 distanceForRay = -10.0f;

    EntityTypeBuffer* postBuffer = &Data->em.buffers[EntityType_Post];
    Post* postEntitiesInBuffer = (Post*)postBuffer->entities;

    DynamicArray<ModelRenderData> postEntitiesToRender = MakeDynamicArray<ModelRenderData>(&Game->frameMem, 100);
    for (int i = 0; i < 1; i++)
    {
        ModelRenderData modelRenderData = {};
        Post* entity = (Post*)GetEntity(&Data->em, postEntitiesInBuffer[i].handle);
        vec3 scaledRayPos = V3(Data->mousePicker.mouseRay.x * distanceForRay, Data->mousePicker.mouseRay.y * distanceForRay, Data->mousePicker.mouseRay.z * distanceForRay);


        entity->modelRenderData.position.x = scaledRayPos.x - cam->pos.x;
        entity->modelRenderData.position.y = scaledRayPos.y - cam->pos.y;
        entity->modelRenderData.position.z = scaledRayPos.z - cam->pos.z;

        modelRenderData = entity->modelRenderData;
        PushBack(&postEntitiesToRender, modelRenderData);
 
        DrawTextScreenPixel(&Game->serifFont, V2(500, 100), 9, V4(1, 1, 1, 1), false, "modelPos.x %2f", entity->modelRenderData.position.x);
        DrawTextScreenPixel(&Game->serifFont, V2(500, 130), 9, V4(1, 1, 1, 1), false, "modelPos.y %2f", entity->modelRenderData.position.y);
        DrawTextScreenPixel(&Game->serifFont, V2(500, 160), 9, V4(1, 1, 1, 1), false, "modelPos.z %2f", entity->modelRenderData.position.z);

        DrawTextScreenPixel(&Game->serifFont, V2(300, 100), 10, V4(1, 1, 1, 1), false, "camPos.x %2f",cam->pos.x);
        DrawTextScreenPixel(&Game->serifFont, V2(300, 130), 10, V4(1, 1, 1, 1), false, "camPos.y %2f",cam->pos.y);
        DrawTextScreenPixel(&Game->serifFont, V2(300, 160), 10, V4(1, 1, 1, 1), false, "camPos.z %2f",cam->pos.z);
        DrawTextScreenPixel(&Game->serifFont, V2(300, 300), 8, V4(1, 1, 1, 1), false, "targetPos.x %2f", cam->targetPos.x);
        DrawTextScreenPixel(&Game->serifFont, V2(300, 330), 8, V4(1, 1, 1, 1), false, "targetPos.y %2f", cam->targetPos.y);
        DrawTextScreenPixel(&Game->serifFont, V2(300, 360), 8, V4(1, 1, 1, 1), false, "targetPos.z %2f", cam->targetPos.z);

        //DrawTextScreenPixel(&Game->serifFont, V2(400, 190), 10, V4(1, 1, 1, 1), false, guiElement->label);


    }

    
    DrawOBJModels(postEntitiesToRender, Data->sunLight, &Game->postMesh, &Data->sprites.wall1Texture, &Game->modelShader, Data->rm.skyColor);
    DeallocateDynamicArray(&postEntitiesToRender);

}   