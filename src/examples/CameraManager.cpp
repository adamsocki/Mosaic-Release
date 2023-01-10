

void InGameCameraInit()
{
    // Game->cameraRotation.x = -DegToRad(8.0f);
    Game->cameraRotation = AxisAngle(V3(1, 0, 0), DegToRad(20.0f));
    //Game->cameraPosition = V3(0, 0, -20);
    Camera* cam = &Game->camera;
    cam->yaw = 180;
    cam->pitch = 20;
    cam->distanceToCFP = 50;
    cam->angleAroundCFP = 0;

    real32 FOV = 70;
    real32 NEAR_PLANE = 0.1f;
    real32 FAR_PLANE = 1000;
    //cam->projection = Identity4();
    //float aspectRatio = Game->screenWidth / Game->screenHeight;
    //float y_scale = (1.0f / tanf(DegToRad( FOV / 2.0f)) * aspectRatio);
    //float x_scale = y_scale / aspectRatio;
    //float frustum_length = FAR_PLANE - NEAR_PLANE;

    ////projectionMatrix = new Matrix4f();
    //cam->projection.m00 = x_scale;
    //cam->projection.m11 = y_scale;
    //cam->projection.m22 = -((FAR_PLANE + NEAR_PLANE) / frustum_length);
    //cam->projection.m23 = -1;
    //cam->projection.m32 = -((2 * NEAR_PLANE * FAR_PLANE) / frustum_length);
    //cam->projection.m33 = 0;


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
        cam->yaw+= cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_K))
    {
        cam->yaw-= cameraSpeed * Game->deltaTime;
    }


    if (InputHeld(Keyboard, Input_I))
    {
        cam->pitch -= cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_O))
    {
        cam->pitch += cameraSpeed * Game->deltaTime;
    }
    //mat4 rotPitch = Rotation4(AxisAngle(V3(1, 0, 0), DegToRad(cam->pitch)));
    //cam->pitch = TRS(Game->cameraPosition, AxisAngle(V3(1, 0, 0), DegToRad(cam->pitch)), V3(1));
    
    
  // Game->cameraRotation = AxisAngle(V3(1, 0, 0), DegToRad(cam->pitch));
   // Game->cameraRotation = AxisAngle(V3(0,1, 0), DegToRad(-cam->yaw));
    quaternion a = AxisAngle(V3(0, 1, 0), DegToRad(-cam->yaw));
   // LookAt(vec3 camPos, vec3 pt, vec3 Y)
   // Game->cameraRotation = a * b ;
   // UpdateCamera(cam, Game->cameraPosition, Game->cameraRotation);
   // Game->cameraRotation = IdentityQuaternion();
   real32 horizontalDistance = cam->distanceToCFP * (cosf(DegToRad(cam->pitch)));
    real32 verticalDistance = cam->distanceToCFP * (sinf(DegToRad(cam->pitch)));

    if (cameraToPlayer)
    {
        real32 theta = player->modelRenderData.rotY + cam->angleAroundCFP;

        real32 offsetX = horizontalDistance * sinf(DegToRad(theta));
        real32 offsetZ = horizontalDistance * cosf(DegToRad(theta));
        Game->cameraPosition.x = player->modelRenderData.position.x - offsetX;
        Game->cameraPosition.y = player->modelRenderData.position.y + verticalDistance + 20;
        Game->cameraPosition.z = player->modelRenderData.position.z - offsetZ;
        cam->yaw = 180 - (player->modelRenderData.rotY + cam->angleAroundCFP);

    }
    mat4 rotationMat = Identity4();
     //rotationMat = matrixRotationTest(DegToRad(cam->yaw), V3(0, 1, 0), rotationMat);
    rotationMat = matrixRotationTest(DegToRad(cam->pitch), V3(1, 0, 0), rotationMat);

    vec3 negCameraPos = V3(-Game->cameraPosition.x, -Game->cameraPosition.y, -Game->cameraPosition.z);
    Game->cameraRotation = ToQuaternionFromMat4(rotationMat);
  //  cam->view = TranslateToMat4(negCameraPos, rotationMat);
   // cam->viewProjection = cam->projection * cam->view;
    //mat4 newMat = Rotation4(AxisAngle(V3(0, 1, 0), DegToRad(cam->yaw))) * rotationMat;
    //cam->view = TRS(Game->cameraPosition, newMat, 1.0f);
    //Game->cameraRotation = FromEulerAngles(V3(0, DegToRad(cam->yaw), 0));
   // Game->cameraRotation = AxisAngle(V3(0, 1, 0), DegToRad(-cam->yaw));
   // Game->cameraRotation = FromEulerAngles(DegToRad(-cam->yaw), 0, 0);
    //UpdateCamera(cam, Game->cameraPosition, Game->cameraRotation);

}