


// LEVEL EDITOR



void CameraInit_LE()
{

}

void TopDownCameraController(Camera *cam)
{
    cam->pos.x = -cam->target.x;
    cam->pos.y = -cam->target.y;
    cam->pos.z = -cam->target.z;


   // cam->pitch = 90.0f;
    
    //real32 offsetX = cam->distanceToCFP * sinf(DegToRad(cam->yaw)) * cosf(DegToRad(cam->pitch));
    //real32 offsetY = cam->distanceToCFP * sinf(DegToRad(cam->pitch));
    //real32 offsetZ = cam->distanceToCFP * cosf(DegToRad(cam->yaw)) * cosf(DegToRad(cam->pitch));

  //  cam->pos.x -= offsetX;
   // cam->pos.y -= offsetY;
    cam->pos.z -=  - 20;

    cam->view = lookAtv2(cam->pos, -cam->target, V3(0, 1, 0));

}

void CameraUpdate_LE()
{
    Camera* cam = &Game->camera;

    

    if (InputHeld(Keyboard, Input_Control) && InputPressed(Keyboard, Input_P) ||
        InputPressed(Keyboard, Input_Control) && InputHeld(Keyboard, Input_P))
    {
        switch (cam->controllerType)
        {
             case ControllerType_ThirdPerson:
             {
                 break;
             }
             case ControllerType_TopDown:
             {
                 TopDownCameraController(cam);
                 break;
             }
             default:
             {
                 break;
             }
        }
        
    }

    switch (cam->controllerType)
    {
        case ControllerType_FirstPerson:
        {
            TopDownCameraController(cam);
            //ThirdPersonCameraController(player, cam);
            break;
        }
        case ControllerType_TopDown:
        {
            TopDownCameraController(cam);
            break;
        }
        default:
        {
            break;
        }
    }


}