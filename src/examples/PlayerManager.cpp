



void PlayerMover(Player *player)
{


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

    




    player->modelRenderData.rotY += DegToRad(player->currentTurnSpeed * Game->deltaTime);
    player->modelRenderData.position.x += player->currentSpeed * Game->deltaTime * (sinf(player->modelRenderData.rotY));
    player->modelRenderData.position.z += player->currentSpeed * Game->deltaTime * (cosf(player->modelRenderData.rotY));


}