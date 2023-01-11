

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

void FirstPersonCameraController()
{

    Camera* cam = &Game->camera;
    real32 cameraSpeed = 58.0f;
    real32 rotationSpeed = 0.4f;


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


void ThirdPersonCameraController(Player* player)
{
    Camera* cam = &Game->camera;
    real32 cameraSpeed = 58.0f;
    real32 rotationSpeed = 0.4f;

    cam->pos.x = -player->modelRenderData.position.x; 
    cam->pos.y = -player->modelRenderData.position.y; 
    cam->pos.z = -player->modelRenderData.position.z; 

    // TODO: Create orbit controller
    if (InputHeld(Keyboard, Input_O))
    {
        cam->angleAroundCFP += cameraSpeed * Game->deltaTime;
        
    }
    if (InputHeld(Keyboard, Input_P))
    {
        cam->angleAroundCFP -= cameraSpeed * Game->deltaTime;
    }
    
    if (InputHeld(Keyboard, Input_U))
    {
        cam->pitch -= cameraSpeed * Game->deltaTime;
    }
     if (InputHeld(Keyboard, Input_I))
    {
        cam->pitch += cameraSpeed * Game->deltaTime;
    }


    cam->yaw = 180 - (cam->angleAroundCFP + player->modelRenderData.rotY);

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


    //FirstPersonCameraController();

    ThirdPersonCameraController(player);

}