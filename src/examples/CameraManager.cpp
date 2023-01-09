

void InGameCameraInit()
{
    // Game->cameraRotation.x = -DegToRad(8.0f);
    Game->cameraRotation = AxisAngle(V3(1, 0, 0), DegToRad(20.0f));
    Camera* cam = &Game->camera;
    cam->yaw = 0;
    cam->distanceToCFP = 50;
    cam->angleAroundCFP = 0;
}


void calculateCameraPosition()
{

}


//real32 calculateHorizontalDistance()
//{
//    return cam
//}


void InGameCameraUpdate(Player* player, bool cameraToPlayer)
{
    Camera* cam = &Game->camera;
    real32 cameraSpeed = 28.0f;
    real32 rotationSpeed = 0.4f;

    if (InputHeld(Keyboard, Input_Z))
    {
        cam->distanceToCFP -= cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_X))
    {
        cam->distanceToCFP += cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_J))
    {
        cam->angleAroundCFP += cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_K))
    {
        cam->angleAroundCFP -= cameraSpeed * Game->deltaTime;
    }


    if (InputHeld(Keyboard, Input_I))
    {
        cam->pitch -= cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_O))
    {
        cam->pitch += cameraSpeed * Game->deltaTime;
    }

    //Game->cameraRotation = AxisAngle(V3(1, 0, 0), DegToRad(cam->pitch));
    real32 horizontalDistance = cam->distanceToCFP * (cosf(DegToRad(cam->pitch)));
    real32 verticalDistance = cam->distanceToCFP * (sinf(DegToRad(cam->pitch)));

    if (cameraToPlayer)
    {
        real32 theta = player->modelRenderData.rotY + cam->angleAroundCFP;

        real32 offsetX = horizontalDistance * sinf(DegToRad(theta));
        real32 offsetZ = horizontalDistance * cosf(DegToRad(theta));
        Game->cameraPosition.x = player->modelRenderData.position.x - offsetX;
        Game->cameraPosition.y = player->modelRenderData.position.y + verticalDistance;
        Game->cameraPosition.z = player->modelRenderData.position.z - offsetZ;
        cam->yaw = 180 - (player->modelRenderData.rotY + cam->angleAroundCFP);

    }
    //Game->cameraRotation = FromEulerAngles(V3(0, DegToRad(cam->yaw), 0));
    Game->cameraRotation = AxisAngle(V3(0, 1, 0), DegToRad(-cam->yaw));

}