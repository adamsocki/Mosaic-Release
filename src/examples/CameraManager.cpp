

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
    cam->speed = 20.0f;
    real32 FOV = 70;
    real32 NEAR_PLANE = 0.1f;
    real32 FAR_PLANE = 1000;

    cam->cameraSpeed = 38.0f;
    cam->rotationSpeed = 0.4f;
    cam->cameraSpeedThirdPerson = 20.0f;

    cam->controllerType = ControllerType_FirstPerson;

    cam->pos = V3(0, 0, 10);
    cam->front = V3(0, 0, -1);
    cam->up = V3(0, 1, 0);

    Data->mouse = {};

}

void FirstPersonCameraController(Camera* cam)
{
    cam->yaw = -90 - RadToDeg(cam->targetRotY);
    vec3 camDelta = cam->pos;
    cam->pos = -cam->targetPos - (Normalize(Cross(cam->front, cam->up)) * cam->speed * 0.01f) * sinf(cam->walkingModTime * 6) * 0.6f; // horiz walk sim
    cam->pos =  -cam->targetPos - (cam->up * cam->speed * 0.01f) * sinf(cam->walkingModTime * 12) * 1.0f;  // vert walk sim
    cam->pos.y -= 5;
    cam->resetWalk = false;
    
    cam->pitch = 0;
     
    if (cam->isWalkingForwardOrBackward)
    {
        cam->walkingModTime += Game->deltaTime;
    }

    cam->front.x = cosf(DegToRad(cam->yaw)) * cosf(DegToRad(cam->pitch));
    cam->front.y = sinf(DegToRad(cam->pitch));
    cam->front.z = sinf(DegToRad(cam->yaw)) * cosf(DegToRad(cam->pitch));
    cam->front = Normalize(cam->front);

    cam->view = lookAtv2(cam->pos, cam->pos + cam->front, V3(0, 1, 0));
}


void ThirdPersonCameraController(Camera* cam)
{    
    cam->pos.x = -cam->targetPos.x; 
    cam->pos.y = -cam->targetPos.y; 
    cam->pos.z = -cam->targetPos.z; 


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
        vec2 mousePosition_delta = Data->mouse.positionPixel_delta;
        
        cam->angleAroundCFP += mousePosition_delta.x * cam->cameraSpeedThirdPerson * Game->deltaTime;
        cam->pitch += mousePosition_delta.y * cam->cameraSpeedThirdPerson * Game->deltaTime;
    }
    
    cam->yaw = 180 - (cam->angleAroundCFP + cam->targetRotY);
    
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

    cam->view = lookAtv2(cam->pos, -cam->targetPos, V3(0, 1, 0));
     
}

void TopDownCameraController(Camera* cam)
{
    cam->pos.x = -cam->targetPos.x;
    cam->pos.y = -cam->targetPos.y;
    cam->pos.z = -cam->targetPos.z;

    cam->yaw = 180 - (cam->angleAroundCFP + cam->targetRotY);

    cam->pitch = 90.0f;

    real32 offsetX = cam->distanceToCFP * sinf(DegToRad(cam->yaw)) * cosf(DegToRad(cam->pitch));
    real32 offsetY = cam->distanceToCFP * sinf(DegToRad(cam->pitch));
    real32 offsetZ = cam->distanceToCFP * cosf(DegToRad(cam->yaw)) * cosf(DegToRad(cam->pitch));

    cam->pos.x -= offsetX;
    cam->pos.y -= offsetY;
    cam->pos.z -= offsetZ;

    cam->view = lookAtv2(cam->pos, -cam->targetPos, V3(0, 1, 0));
}

void InGameCameraUpdate()
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
                //cam->type = CameraType_Orthographic;
                cam->controllerType = ControllerType_TopDown;
                break;
            }
            case ControllerType_TopDown:
            {
                cam->controllerType = ControllerType_FirstPerson;
                break;
            }
            default:
            {
                ThirdPersonCameraController(cam);
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
            ThirdPersonCameraController(cam);
            break;
        }
        case ControllerType_TopDown:
        {
            TopDownCameraController(cam);
        }
        default:
        {
            ThirdPersonCameraController(cam);
            break;
        }
    }
}