

void InGameCameraInit()
{
    // Game->cameraRotation.x = -DegToRad(8.0f);
    Game->cameraRotation = AxisAngle(V3(1, 0, 0), DegToRad(20.0f));
    Camera* cam = &Game->camera;
    cam->distanceToCFP = 50;
}


void calculateCameraPosition()
{

}


//real32 calculateHorizontalDistance()
//{
//    return cam
//}


void InGameCameraUpdate()
{
    Camera* cam = &Game->camera;
    real32 cameraSpeed = 28.0f;
    real32 rotationSpeed = 0.4f;

    if (InputHeld(Keyboard, Input_Z))
    {
        Game->cameraPosition.z += cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_X))
    {
        Game->cameraPosition.z -= cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_C))
    {
        Game->cameraPosition.x += cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_V))
    {
        Game->cameraPosition.x -= cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_UpArrow)) {
        Game->cameraPosition.y += cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_DownArrow)) {
        Game->cameraPosition.y -= cameraSpeed * Game->deltaTime;
    }




    if (InputHeld(Keyboard, Input_I))
    {
        cam->pitch += cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_O))
    {
        cam->pitch -= cameraSpeed * Game->deltaTime;
    }

    Game->cameraRotation = AxisAngle(V3(1, 0, 0), DegToRad(cam->pitch));
    //real32 horizontalDistance = cam->distanceToCFP * (cosf()



}