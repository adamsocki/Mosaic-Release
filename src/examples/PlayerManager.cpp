
void PlayerJump()
{

}


void PlayerMover(Player *player)
{
    real32 terrainHeight = 0;

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
    if (player->modelRenderData.position.y < terrainHeight)
    {   // collission to terrain ground if at zero height
        player->upwardSpeed = 0;
        player->modelRenderData.position.y = terrainHeight;
        player->isInAir = false;
    }

    player->modelRenderData.rotY += DegToRad(player->currentTurnSpeed * Game->deltaTime);
    player->modelRenderData.position.x += player->currentSpeed * Game->deltaTime * (sinf(player->modelRenderData.rotY));
    player->modelRenderData.position.z += player->currentSpeed * Game->deltaTime * (cosf(player->modelRenderData.rotY));
}