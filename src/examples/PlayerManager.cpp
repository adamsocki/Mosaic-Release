
void PlayerJump()
{

}


void PlayerMover(Player *player, Terrain terrain)
{
    Camera* cam = &Game->camera;

    real32 terrainHeight = GetHeightOfTerrain(player->modelRenderData.position, terrain);

    if (InputHeld(Keyboard, Input_W))
    {
        player->currentSpeed = player->runSpeed;
        player->isWalkingForwardOrBackward = true;
    }
    else if (InputHeld(Keyboard, Input_S))
    {
        player->currentSpeed = -player->runSpeed;
        player->isWalkingForwardOrBackward = true;
    }
    else
    {
        player->currentSpeed = 0;
        player->isWalkingForwardOrBackward = false;
    }

    if (InputHeld(Keyboard, Input_A))
    {
        player->currentTurnSpeed = player->turnSpeed;
    }
    else if (InputHeld(Keyboard, Input_D))
    {
        player->currentTurnSpeed = -player->turnSpeed;
    }
    else
    {
        player->currentTurnSpeed = 0;
    }


    if (InputPressed(Keyboard, Input_Space))
    {   // player jump
        if (!player->isInAir)
        {
            player->upwardSpeed = player->jumpPower;
            player->isInAir = true;
        }
    }

    player->upwardSpeed += player->gravity * Game->deltaTime;

    player->modelRenderData.position.y += player->upwardSpeed * Game->deltaTime;

   
    player->modelRenderData.rotY += DegToRad(player->currentTurnSpeed * Game->deltaTime);
    player->modelRenderData.position.x += player->currentSpeed * Game->deltaTime * (sinf(player->modelRenderData.rotY));
    player->modelRenderData.position.z += player->currentSpeed * Game->deltaTime * (cosf(player->modelRenderData.rotY));

    if (player->modelRenderData.position.y <= terrainHeight)
    {   // collission to terrain ground if at zero height
        player->upwardSpeed = 0.01f;
        player->modelRenderData.position.y = terrainHeight;
        player->isInAir = false;
    }

    if (player->modelRenderData.position.y >= terrainHeight && !player->isInAir)
    {
        player->upwardSpeed = 0.01f;
        player->modelRenderData.position.y = terrainHeight;
    }


    cam->targetPos = player->modelRenderData.position;
    cam->targetRotY = player->modelRenderData.rotY;
    cam->isWalkingForwardOrBackward = player->isWalkingForwardOrBackward;
}