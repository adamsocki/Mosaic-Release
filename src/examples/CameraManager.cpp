

void InGameCameraInit()
{
    // Game->cameraRotation.x = -DegToRad(8.0f);
    Game->cameraRotation = AxisAngle(V3(1, 0, 0), DegToRad(20.0f));
    //Game->cameraPosition = V3(0, 0, -20);
    Camera* cam = &Game->camera;
    cam->yaw = -90;
    cam->pitch = 0;
    cam->distanceToCFP = 50;
    cam->angleAroundCFP = 0;
    cam->speed = 40.0f;
    real32 FOV = 70;
    real32 NEAR_PLANE = 0.1f;
    real32 FAR_PLANE = 1000;

    cam->pos = V3(0, 0, 10);
    cam->front = V3(0, 0, -1);
    cam->up = V3(0, 1, 0);

    Data->mouse = {};

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
    real32 cameraSpeed = 58.0f;
    real32 rotationSpeed = 0.4f;

    /*if (InputHeld(Keyboard, Input_Z))
    {
        cam->distanceToCFP -= cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_X))
    {
        cam->distanceToCFP += cameraSpeed * Game->deltaTime;
    }


    if (InputHeld(Keyboard, Input_C))
    {
        cam->yaw+= cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_K))
    {
        cam->yaw-= cameraSpeed * Game->deltaTime;
    }


    if (InputHeld(Keyboard, Input_Z))
    {
        cam->angleAroundCFP -= cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_X))
    {
        cam->angleAroundCFP += cameraSpeed * Game->deltaTime;
    }*/
    //mat4 rotPitch = Rotation4(AxisAngle(V3(1, 0, 0), DegToRad(cam->pitch)));
    //cam->pitch = TRS(Game->cameraPosition, AxisAngle(V3(1, 0, 0), DegToRad(cam->pitch)), V3(1));
    
    
  // Game->cameraRotation = AxisAngle(V3(1, 0, 0), DegToRad(cam->pitch));
   // Game->cameraRotation = AxisAngle(V3(0,1, 0), DegToRad(-cam->yaw));
  //  quaternion a = AxisAngle(V3(0, 1, 0), DegToRad(-cam->yaw));
   // LookAt(vec3 camPos, vec3 pt, vec3 Y)
   // Game->cameraRotation = a * b ;
   // UpdateCamera(cam, Game->cameraPosition, Game->cameraRotation);
   // Game->cameraRotation = IdentityQuaternion();
   // real32 horizontalDistance = cam->distanceToCFP * (cosf(DegToRad(cam->pitch)));
   // real32 verticalDistance = cam->distanceToCFP * (sinf(DegToRad(cam->pitch)));

    if (cameraToPlayer)
    {
        real32 theta = cam->angleAroundCFP;
        //real32 theta = player->modelRenderData.rotY + cam->angleAroundCFP;

       // real32 offsetX = horizontalDistance * sinf(DegToRad(theta));
        //real32 offsetZ = horizontalDistance * cosf(DegToRad(theta));
        //Game->cameraPosition.x = player->modelRenderData.position.x - offsetX;
        //Game->cameraPosition.y = player->modelRenderData.position.y + verticalDistance + 20;
        //Game->cameraPosition.z = player->modelRenderData.position.z - offsetZ;
        /////cam->yaw = 180 - (player->modelRenderData.rotY + cam->angleAroundCFP);

    }
    //mat4 rotationMat = Identity4();
     //rotationMat = matrixRotationTest(DegToRad(cam->yaw), V3(0, 1, 0), rotationMat);
  //  rotationMat = matrixRotationTest(DegToRad(cam->pitch), V3(1, 0, 0), rotationMat);

  //  vec3 negCameraPos = V3(-Game->cameraPosition.x, -Game->cameraPosition.y, -Game->cameraPosition.z);
   // Game->cameraRotation = ToQuaternionFromMat4(rotationMat);
    //Game->cameraRotation = ToQuaternionFromMat4(rotationMat);
    /*if (InputHeld(Keyboard, Input_P))
    {
        cam->rotationValue += cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_O))
    {
        cam->rotationValue -= cameraSpeed * Game->deltaTime;
    }*/
    real32 camX = sin(DegToRad(cam->rotationValue)) * 10;
    real32 camZ = cos(DegToRad(cam->rotationValue)) * 10;
    //cam->view = LookAt(V3(camX,0,camZ), V3(0,0,0), V3(0,1,0));
    ////camZ = 3;


    //cam->pos = V3(camX, -10, camZ);
    //vec3 zaxis = Normalize(camPosition - V3(0,0,0));
    //vec3 xaxis = Normalize(Cross(V3(0,1,0), zaxis));
    //vec3 yaxis = Cross(zaxis, xaxis);

    //mat4 translation = Translation4(camPosition);
    //mat4 result = {};
    //result.columns[0] = V4(xaxis.x, yaxis.x, zaxis.x, 0.0f);
    //result.columns[1] = V4(xaxis.y, yaxis.y, zaxis.y, 0.0f);
    //result.columns[2] = V4(xaxis.z, yaxis.z, zaxis.z, 0.0f);
    //result.columns[3] = V4(0.0f, 0.0f, 0.0f, 1.0f);
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
    
  /*  vec3 playerPos = player->modelRenderData.position;
    playerPos.x = playerPos.x;



    if (InputHeld(Keyboard, Input_I))
    {
        cam->pos = cam->pos + (cameraSpeed * Game->deltaTime * cam->front);
    }
    if (InputHeld(Keyboard, Input_K))
    {
        cam->pos = cam->pos - (cameraSpeed * Game->deltaTime * cam->front);

    }


    if (InputHeld(Keyboard, Input_J))
    {
        cam->pos = cam->pos - (Normalize(Cross(cam->front, cam->up)) * Game->deltaTime * cameraSpeed);
    }
    if (InputHeld(Keyboard, Input_L))
    {
        cam->pos = cam->pos + (Normalize(Cross(cam->front, cam->up)) * Game->deltaTime * cameraSpeed);

    }

   
    POINT p;

    if (GetCursorPos(&p))
    {
        Data->mouse.posOnWindow.x = p.x;
        Data->mouse.posOnWindow.y = p.y;

    }

    real32 mouseOffset_X = (p.x - Data->mouse.posOnWindow_prev.x) * 0.3f;
    real32 mouseOffset_Y = (Data->mouse.posOnWindow_prev.y - p.y) * 0.1f;


    Data->mouse.posOnWindow_prev.x = p.x;
    Data->mouse.posOnWindow_prev.y = p.y;

    
    cam->yaw += mouseOffset_X;  
    cam->pitch += mouseOffset_Y;

    if (cam->pitch > 89.0f)
    {
        cam->pitch = 89.0f;
    }
    if (cam->pitch < -89.0f)
    {
        cam->pitch = -89.0f;
    }
    

    vec3 front = {};
    front.x = cosf(DegToRad(cam->yaw)) * cosf(DegToRad(cam->pitch));
    front.y = sinf(DegToRad(cam->pitch));
    front.z = sinf(DegToRad(cam->yaw)) * cosf(DegToRad(cam->pitch));
    
    cam->front = Normalize(front);

*/


   
    
    
    // Game->cameraRotation = ToQuaternionFromMat4(lookAt);
   // Game->cameraPosition = V3(camX, 0, camZ);
  //  cam->view = TranslateT3roMat4(negCameraPos, rotationMat);
   // cam->viewProjection = cam->projection * cam->view;
    //mat4 newMat = Rotation4(AxisAngle(V3(0, 1, 0), DegToRad(cam->yaw))) * rotationMat;
    //cam->view = TRS(Game->cameraPosition, newMat, 1.0f);
    //Game->cameraRotation = FromEulerAngles(V3(0, DegToRad(cam->yaw), 0));
   // Game->cameraRotation = AxisAngle(V3(0, 1, 0), DegToRad(-cam->yaw));
   // Game->cameraRotation = FromEulerAngles(DegToRad(-cam->yaw), 0, 0);
    //UpdateCamera(cam, Game->cameraPosition, Game->cameraRotation);

}