

void InGameCameraInit()
{
    // Game->cameraRotation.x = -DegToRad(8.0f);
    Game->cameraRotation = AxisAngle(V3(1, 0, 0), 0.0f);

}


void InGameCameraUpdate()
{
    Camera* cam = &Game->camera;
    real32 cameraSpeed = 28.0f;
    real32 rotationSpeed = 0.4f;

    if (InputHeld(Keyboard, Input_W))
    {
        Game->cameraPosition.z += cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_S))
    {
        Game->cameraPosition.z -= cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_A))
    {
        Game->cameraPosition.x += cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_D))
    {
        Game->cameraPosition.x -= cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_UpArrow)) {
        Game->cameraPosition.y += cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_DownArrow)) {
        Game->cameraPosition.y -= cameraSpeed * Game->deltaTime;
    }




    if (InputPressed(Keyboard, Input_I))
    {
        cam->distanceToCFP -= cameraSpeed * Game->deltaTime;
    }
    if (InputPressed(Keyboard, Input_O))
    {
        cam->distanceToCFP += cameraSpeed * Game->deltaTime;
    }

}