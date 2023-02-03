

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

   // vec3 aabb_min = V3(-1.0f, -1.0f, -1.0f);
   // vec3 aabb_max = V3(1.0f, 1.0f, 1.0f);

    DynamicArray<ModelRenderData> postEntitiesToRender = MakeDynamicArray<ModelRenderData>(&Game->frameMem, 100);
    DynamicArray<ModelRenderData> wallEntitiesToRender = MakeDynamicArray<ModelRenderData>(&Game->frameMem, 100);
     if (Data->le.currentLevel == -1 || Data->le.currentLevel == 0)
     {
         
        for (int i = 0; i < 2; i++)
        {
            ModelRenderData modelRenderData = {};
            Post* entity = (Post*)GetEntity(&Data->em, postEntitiesInBuffer[i].handle);         
            
            real32 distanceForRay = -500.0f;

            real32 intersection_distance;
            mat4 ModelMatrix = TRS(entity->modelRenderData.position, Identity4(), entity->modelRenderData.scale.x);
            vec3 scaledRayPos = V3(Data->mousePicker.mouseRay.x * distanceForRay, Data->mousePicker.mouseRay.y * distanceForRay, Data->mousePicker.mouseRay.z * distanceForRay);
            
            vec3 aabb_max = {};
            aabb_max.x = entity->modelRenderData.position.x + (entity->mesh.maxAABB.x * entity->modelRenderData.scale.x);
            aabb_max.y = entity->modelRenderData.position.y + (entity->mesh.maxAABB.y * entity->modelRenderData.scale.y);
            aabb_max.z = entity->modelRenderData.position.z + (entity->mesh.maxAABB.z * entity->modelRenderData.scale.z);

            vec3 aabb_min = {};
            aabb_min.x = entity->modelRenderData.position.x + (entity->mesh.minAABB.x * entity->modelRenderData.scale.x);
            aabb_min.y = entity->modelRenderData.position.y + (entity->mesh.minAABB.y * entity->modelRenderData.scale.y);
            aabb_min.z = entity->modelRenderData.position.z + (entity->mesh.minAABB.z * entity->modelRenderData.scale.z);

            vec3 aabbSize = {};
            aabbSize = aabb_max - aabb_min;
            entity->modelRenderData.aabb_min = aabb_min;
            entity->modelRenderData.aabbSize = aabbSize;

            // TODO if more than one selected, only interact with the closest;
            if (TestRayOBBIntersection(-Game->camera.pos, scaledRayPos, aabb_min, aabb_max, Identity4(), &intersection_distance))
            {
                real32 distanceToEntity = Distance(-Game->camera.pos, entity->modelRenderData.position);
                DrawAABB(entity->modelRenderData.position, IdentityQuaternion(), V3(0.25f, 0.25f, 0.25f), V3(0.5f, 0.5f, 0.25f, 1.0), true)
                entity->editorMode = fixed_Mode;
                entity->modelRenderData.isMouseOver = true;
                //bool xMode = false;

                if (InputHeld(Mouse, Input_MouseLeft))
                {
                    entity->modelRenderData.isSelected = true;
                    entity->modelRenderData.aabbColor = V4(0.0f, 1.0f, 0.0f, 1.0f);
                    // TODO: Calculate distance from mouseRay.origin to object Position
                    // entity->modelRenderData.position = 
                }
                else
                {
                    entity->modelRenderData.aabbColor = V4(1);
                    entity->modelRenderData.isSelected = false;
                }


                if (entity->modelRenderData.isSelected)
                {
                    if (InputHeld(Keyboard, Input_X))
                    {
                        entity->editorMode = xPos_Mode;
                    }
                    if (InputHeld(Keyboard, Input_Y))
                    {
                        entity->editorMode = yPos_Mode;
                    }
                    if (InputHeld(Keyboard, Input_Z))
                    {
                        entity->editorMode = zPos_Mode;
                    }
                }


                switch (entity->editorMode)
                {
                    case fixed_Mode:
                    {
                        break;
                    }
                    case xPos_Mode:
                    {
                        entity->modelRenderData.position.x = -Data->mouse.positionPixel_delta.x;
                        DrawLine(V3(-10000.0f, entity->modelRenderData.position.y, entity->modelRenderData.position.z), V3(20000.0f, 0.05f, 0.05f), V4(1.0f, 0.0f, 0.0f, 1.0f));
                        break;
                    }
                    case yPos_Mode:
                    {
                        DrawLine(V3(entity->modelRenderData.position.x, -10000.0f, entity->modelRenderData.position.z), V3(0.05f, 20000.0f, 0.05f), V4(0.0f, 1.0f, 0.0f, 1.0f));
                        break;
                    }
                    case zPos_Mode:
                    {
                        DrawLine(V3(entity->modelRenderData.position.x, entity->modelRenderData.position.y, -10000.0f), V3(0.05f, 0.05f, 20000.0f), V4(0.0f, 0.0f, 1.0f, 1.0f));
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }

                

                DrawAABB(aabb_min, IdentityQuaternion(), aabbSize, entity->modelRenderData.aabbColor, true);
                entity->modelRenderData.sprite = Data->sprites.wall1Texture;
            } 
            else
            {
                entity->modelRenderData.isMouseOver = true;
                entity->modelRenderData.sprite = Data->sprites.fernTexture;
            }

             
            modelRenderData = entity->modelRenderData;

            PushBack(&postEntitiesToRender, modelRenderData);
        }
        for (int i = 0; i < wallBuffer->count; i++)
        {
            ModelRenderData modelRenderData = {};
            Wall* entity = (Wall*)GetEntity(&Data->em, wallEntitiesInBuffer[i].handle);
            entity->modelRenderData.sprite = Data->sprites.wall1Texture;
            modelRenderData = entity->modelRenderData;
            PushBack(&wallEntitiesToRender, modelRenderData);

        }
        DrawOBJModels(postEntitiesToRender, Data->sunLight, &Game->postMesh, &Game->modelShader, Data->rm.skyColor, true);
        DrawOBJModels(wallEntitiesToRender, Data->sunLight, &Data->meshes.wall1Mesh, &Game->modelShader, Data->rm.skyColor);
    }
    
    DeallocateDynamicArray(&postEntitiesToRender);
    DeallocateDynamicArray(&wallEntitiesToRender);
}


void TestRayMouse()
{
    Camera* cam = &Game->camera;

    real32 distanceForRay = -500.0f;

    EntityTypeBuffer* postBuffer = &Data->em.buffers[EntityType_Post];
    Post* postEntitiesInBuffer = (Post*)postBuffer->entities;
    vec3 scaledRayPos = V3(Data->mousePicker.mouseRay.x * distanceForRay, Data->mousePicker.mouseRay.y * distanceForRay, Data->mousePicker.mouseRay.z * distanceForRay);

    Plane testFloorPlane = MakePlane(V3(0), V3(0, 1, 0));

    Ray rayMouse = {};
    rayMouse.origin = -cam->pos;
    rayMouse.direction = scaledRayPos;

    real32 val = {};
    bool raycastToPlane =  RaycastPlane(V3(0), V3(0, 1, 0), rayMouse, &val);

    if (raycastToPlane)
    {
       // Print("Val: %2f", val);
    }
    real32 val2 = {};


    bool rayAABBHit = false;
    rayAABBHit = RaycastAABB(V2(0), V2(1, 1), rayMouse, &val2);

    if (rayAABBHit)
    {
        Print("Val2: %2f", val2);
    }
    real32 intersection_distance;

    
    if (TestRayOBBIntersection(-Game->camera.pos, scaledRayPos, V3(0,0,0), V3(10,10,10), Identity4(), &intersection_distance))
    {
        DrawTextScreenPixel(&Game->serifFont, V2(500, 100), 9, V4(1, 1, 1, 1), false, "modelPos.x %2f", intersection_distance);
        DrawTextScreenPixel(&Game->serifFont, V2(500, 130), 9, V4(1, 1, 1, 1), false, "modelPos.y %2f", intersection_distance);
        DrawTextScreenPixel(&Game->serifFont, V2(500, 160), 9, V4(1, 1, 1, 1), false, "modelPos.z %2f", intersection_distance);
    }
    else
    {
        //entity->modelRenderData.sprite = Data->sprites.fernTexture;
    }


    DynamicArray<ModelRenderData> postEntitiesToRender = MakeDynamicArray<ModelRenderData>(&Game->frameMem, 100);
    for (int i = 0; i < 1; i++)
    {
        ModelRenderData modelRenderData = {};
        Post* entity = (Post*)GetEntity(&Data->em, postEntitiesInBuffer[i].handle);

        entity->modelRenderData.position.x = scaledRayPos.x - cam->pos.x;
        entity->modelRenderData.position.y = scaledRayPos.y - cam->pos.y;
        entity->modelRenderData.position.z = scaledRayPos.z - cam->pos.z;
        entity->modelRenderData.sprite = Data->sprites.wall1Texture;

        modelRenderData = entity->modelRenderData;


        PushBack(&postEntitiesToRender, modelRenderData);




 
       /* DrawTextScreenPixel(&Game->serifFont, V2(500, 100), 9, V4(1, 1, 1, 1), false, "modelPos.x %2f", entity->modelRenderData.position.x);
        DrawTextScreenPixel(&Game->serifFont, V2(500, 130), 9, V4(1, 1, 1, 1), false, "modelPos.y %2f", entity->modelRenderData.position.y);
        DrawTextScreenPixel(&Game->serifFont, V2(500, 160), 9, V4(1, 1, 1, 1), false, "modelPos.z %2f", entity->modelRenderData.position.z);*/

        DrawTextScreenPixel(&Game->serifFont, V2(300, 100), 10, V4(1, 1, 1, 1), false, "camPos.x %2f",cam->pos.x);
        DrawTextScreenPixel(&Game->serifFont, V2(300, 130), 10, V4(1, 1, 1, 1), false, "camPos.y %2f",cam->pos.y);
        DrawTextScreenPixel(&Game->serifFont, V2(300, 160), 10, V4(1, 1, 1, 1), false, "camPos.z %2f",cam->pos.z);
        DrawTextScreenPixel(&Game->serifFont, V2(300, 300), 8, V4(1, 1, 1, 1), false, "targetPos.x %2f", cam->targetPos.x);
        DrawTextScreenPixel(&Game->serifFont, V2(300, 330), 8, V4(1, 1, 1, 1), false, "targetPos.y %2f", cam->targetPos.y);
        DrawTextScreenPixel(&Game->serifFont, V2(300, 360), 8, V4(1, 1, 1, 1), false, "targetPos.z %2f", cam->targetPos.z);

        //DrawTextScreenPixel(&Game->serifFont, V2(400, 190), 10, V4(1, 1, 1, 1), false, guiElement->label);
                        

    }

    
    DrawOBJModels(postEntitiesToRender, Data->sunLight, &Game->postMesh, &Game->modelShader, Data->rm.skyColor);
    DeallocateDynamicArray(&postEntitiesToRender);

}   