

void InGameCameraInit()
{
    // Game->cameraRotation.x = -DegToRad(8.0f);
    Game->cameraRotation = AxisAngle(V3(1, 0, 0), DegToRad(20.0f));
    //Game->cameraPosition = V3(0, 0, -20);
    Camera* cam = &Game->camera;
    cam->yaw = -90;
    cam->pitch = 0;
    cam->distanceToCFP = 30;
    cam->angleAroundCFP = 0;
    cam->speed = 40.0f;
    real32 FOV = 70;
    real32 NEAR_PLANE = 0.1f;
    real32 FAR_PLANE = 1000;

    cam->cameraSpeed = 58.0f;
    cam->rotationSpeed = 0.4f;
    cam->cameraSpeedThirdPerson = 20.0f;

    cam->controllerType = ControllerType_ThirdPerson;

    cam->pos = V3(0, 0, 10);
    cam->front = V3(0, 0, -1);
    cam->up = V3(0, 1, 0);

    Data->mouse = {};

}

void FirstPersonCameraController(Camera* cam)
{

    if (InputHeld(Keyboard, Input_I))
    {
        cam->pos = cam->pos + (cam->speed * cam->front * Game->deltaTime);
    }
    if (InputHeld(Keyboard, Input_K))
    {
        cam->pos = cam->pos - (cam->speed * cam->front * Game->deltaTime);
    }
    if (InputHeld(Keyboard, Input_J))
    {
        cam->pos = cam->pos - (Normalize(Cross(cam->front, cam->up)) * cam->speed * Game->deltaTime);
    }
    if (InputHeld(Keyboard, Input_L))
    {
        cam->pos = cam->pos + (Normalize(Cross(cam->front, cam->up)) * cam->speed * Game->deltaTime);
    }

    if (InputHeld(Keyboard, Input_G))
    {
        cam->pitch += cam->speed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_N))
    {
        cam->yaw += cam->speed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_B))
    {
        cam->pitch -= cam->speed * Game->deltaTime;

    }
    if (InputHeld(Keyboard, Input_V))
    {
        cam->yaw -= cam->speed * Game->deltaTime;
    }

    if (cam->pitch > 89.0f)
    {
        cam->pitch = 89.0f;
    }
    if (cam->pitch < -89.0f)
    {
        cam->pitch = -89.0f;
    }

    cam->front.x = cosf(DegToRad(cam->yaw)) * cosf(DegToRad(cam->pitch));
    cam->front.y = sinf(DegToRad(cam->pitch));
    cam->front.z = sinf(DegToRad(cam->yaw)) * cosf(DegToRad(cam->pitch));
    cam->front = Normalize(cam->front);

    cam->view = lookAtv2(cam->pos, (cam->pos + cam->front), V3(0, 1, 0));
}


void ThirdPersonCameraController(Player* player, Camera* cam)
{    
    cam->pos.x = -player->modelRenderData.position.x; 
    cam->pos.y = -player->modelRenderData.position.y; 
    cam->pos.z = -player->modelRenderData.position.z; 


    if (Input->mouseScroll > 0)
    {
        cam->distanceToCFP += 3;
        Input->mouseScroll = 0;
    }
    if (Input->mouseScroll < 0)
    {
        cam->distanceToCFP -= 3;
        Input->mouseScroll = 0;
    }

    if (InputHeld(Keyboard, Input_Q))
    {            
        vec2 mousePosition_delta = Data->mouse.positionFromInput_delta;
        
        cam->angleAroundCFP += mousePosition_delta.x * cam->cameraSpeedThirdPerson * Game->deltaTime;
        cam->pitch += mousePosition_delta.y * cam->cameraSpeedThirdPerson * Game->deltaTime;
    }
    
    cam->yaw = 180 - (cam->angleAroundCFP + player->modelRenderData.rotY);
    
    if (cam->pitch > 89.0f)
    {
        cam->pitch = 89.0f;
    }
    if (cam->pitch < -89.0f)
    {
        cam->pitch = -89.0f;
    }

    real32 offsetX = cam->distanceToCFP * sinf(DegToRad(cam->yaw)) * cosf(DegToRad(cam->pitch));
    real32 offsetY = cam->distanceToCFP * sinf(DegToRad(cam->pitch));
    real32 offsetZ = cam->distanceToCFP * cosf(DegToRad(cam->yaw)) * cosf(DegToRad(cam->pitch));

    cam->pos.x -= offsetX;
    cam->pos.y -= offsetY;
    cam->pos.z -= offsetZ;

    cam->view = lookAtv2(cam->pos, -player->modelRenderData.position, V3(0, 1, 0));   
}

void InGameCameraUpdate(Player* player, bool cameraToPlayer)
{
    Camera* cam = &Game->camera;

    if (InputHeld(Keyboard, Input_Control) && InputPressed(Keyboard, Input_P) || 
        InputPressed(Keyboard, Input_Control) && InputHeld(Keyboard, Input_P))
    {
        switch (cam->controllerType)
        {
            case ControllerType_FirstPerson:
            {
                cam->controllerType = ControllerType_ThirdPerson;
                break;
            }
            case ControllerType_ThirdPerson:
            {
                cam->controllerType = ControllerType_FirstPerson;
                break;
            }
            default:
            {
                ThirdPersonCameraController(player, cam);
                break;
            }
        }
    }

    switch(cam->controllerType)
    {
        case ControllerType_FirstPerson:
        {
            FirstPersonCameraController(cam);
            break;
        }
        case ControllerType_ThirdPerson:
        {
            ThirdPersonCameraController(player, cam);
            break;
        }
        default:
        {
            ThirdPersonCameraController(player, cam);
            break;
        }
    }
}