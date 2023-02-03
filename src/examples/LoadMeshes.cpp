


void LoadMeshes()
{
    AllocateAABB(&Game->AABBMesh);
    InitMesh(&Game->AABBMesh);


	Game->fernMesh   = LoadOBJv2("data/fern.obj");
    Game->stallMesh  = LoadOBJv2("data/stall.obj");
    Game->wall1Mesh  = LoadOBJv2("data/wall1.obj");
    Game->postMesh   = LoadOBJv2("data/post2.obj");
    Game->playerMesh = LoadOBJv2("data/player.obj");
    InitOBJMesh(&Game->stallMesh);
    InitOBJMesh(&Game->wall1Mesh);
    AllocateQuad(&Game->quadMesh);
    InitOBJMesh(&Game->postMesh);
    InitOBJMesh(&Game->playerMesh); 
    InitOBJMesh(&Game->fernMesh);
}