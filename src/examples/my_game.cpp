MyData *Data = NULL;
#include "LoadSprites.cpp"
#include "EntityManager.cpp"
#include "RenderManager.cpp"
#include "TerrainManager.cpp"
#include "assimpLoader.cpp"
#include "GUI_Editor.cpp"

#include "MemoryArray.cpp"
#include "LevelManager.cpp"
#include "CameraManager.cpp"
#include "PlayerManager.cpp"
#include "MouseManager.cpp"


#include <iostream>
#include <vector>

OBJMesh fernMesh = {};
OBJMesh stallMesh2 = {};
QuadMesh qMesh = {};

Sprite stallTexture;
real32 rotation = {};

void MyInit() {
    Game->myData = malloc(sizeof(MyData));
    memset(Game->myData, 0, sizeof(MyData));

    Data = (MyData *)Game->myData;

    Data->sunLight.position = V3(1000.0f, 1000.0f, 1000.0f);
    Data->sunLight.color = V3(1.0f, 1.0f, 1.0f);

    LoadSprites();
    InitializeEntityManager();
    InitializeEntityBuffers();

	
    GenerateTerrain("data/cursor_red.png");
    InGameCameraInit();

    LoadSprite(&stallTexture, "data/perlin.png");
    LoadSprite(&Data->sprites.newPlus, "data/newPlus.png");
    LoadSprite(&Data->sprites.newPlusSel, "data/newPlusSel.png");
    LoadSprite(&Data->sprites.fernTexture, "data/fern.png");
    LoadSprite(&Data->sprites.wall1Texture, "data/wall1.png");

    fernMesh = LoadOBJv2("data/fern.obj");
    //InitOBJMesh(&stallMesh);
    GenerateQuadMesh(&qMesh);

    InitOBJMesh(&Game->terrain);
    InitOBJMesh(&fernMesh);

    Data->meshes.stallMesh = LoadOBJv2("data/stall.obj");
    Data->meshes.wall1Mesh = LoadOBJv2("data/wall1.obj");
    Data->meshes.postMesh = LoadOBJv2("data/post1.obj");
    Data->meshes.playerMesh = LoadOBJv2("data/player.obj");
    InitOBJMesh(&Data->meshes.stallMesh);
    InitOBJMesh(&Data->meshes.wall1Mesh);
    AllocateQuad(&Data->meshes.quadMesh);
    InitOBJMesh(&Data->meshes.postMesh);
    InitOBJMesh(&Data->meshes.playerMesh);
    
    BuildGUI("Terrian", 3, true, true, true, 2);

    InititalizeMouse();
    InitMousePicker();

    InitializeStartingEntities();
    InitializeLevelFromCode();
    Data->rm.skyColor = RGB(0.12f, 0.14f, 0.0f);
}

vec2 position = V2(4, 0);

vec2 scale = V2(1, 1);

void MyGameUpdate() {
    // This sets the background color.
    Camera* cam = &Game->camera;
    ClearColor(Data->rm.skyColor);

    DynamicArray<EntityHandle> entitiesToRender = MakeDynamicArray<EntityHandle>(&Game->frameMem, 100);

    DynamicArray<ModelRenderData> testStallEntitiesToRender = MakeDynamicArray<ModelRenderData>(&Game->frameMem, 100);
    DynamicArray<ModelRenderData> terrainEntitiesToRender = MakeDynamicArray<ModelRenderData>(&Game->frameMem, 100);
    DynamicArray<ModelRenderData> fernEntitiesToRender = MakeDynamicArray<ModelRenderData>(&Game->frameMem, 100);
    DynamicArray<ModelRenderData> wallEntitiesToRender = MakeDynamicArray<ModelRenderData>(&Game->frameMem, 100);
    DynamicArray<ModelRenderData> postEntitiesToRender = MakeDynamicArray<ModelRenderData>(&Game->frameMem, 100);
    DynamicArray<ModelRenderData> playerEntitiesToRender = MakeDynamicArray<ModelRenderData>(&Game->frameMem, 10);

    // LOGIC
    EntityTypeBuffer* testStallBuffer = &Data->em.buffers[EntityType_Test];
    EntityTypeBuffer* terrainBuffer = &Data->em.buffers[EntityType_Terrain];
    EntityTypeBuffer* fernBuffer = &Data->em.buffers[EntityType_Fern];
    EntityTypeBuffer* guiBuffer = &Data->em.buffers[EntityType_GUI];
    EntityTypeBuffer* wallBuffer = &Data->em.buffers[EntityType_Wall];
    EntityTypeBuffer* postBuffer = &Data->em.buffers[EntityType_Post];
    EntityTypeBuffer* playerBuffer = &Data->em.buffers[EntityType_Player];

    TestStall* testStallEntitiesInBuffer = (TestStall*)testStallBuffer->entities;
    Terrain* terrainEntitiesInBuffer = (Terrain*)terrainBuffer->entities;
    Fern* fernEntitiesInBuffer = (Fern*)fernBuffer->entities;
    GUI* guiEntitiesInBuffer = (GUI*)guiBuffer->entities;
    Wall* wallEntitiesInBuffer = (Wall*)wallBuffer->entities;
    Post* postEntitiesInBuffer = (Post*)postBuffer->entities;
    Player* playerEntitiesInBuffer = (Player*)playerBuffer->entities;

    // Generate Certain Entities
    Player* playerEntity = (Player*)GetEntity(&Data->em, playerEntitiesInBuffer[0].handle);
    Terrain* terrainEntity = (Terrain*)GetEntity(&Data->em, terrainEntitiesInBuffer[0].handle);

    UpdateMouseData();
    MouseOverGUI(*guiBuffer, guiEntitiesInBuffer);
    UpdateMousePicker();
    PlayerMover(playerEntity, *terrainEntity);

    // INPUT LOGIC FOR CAMERA MOVEMENT
    InGameCameraUpdate(playerEntity, true);

    //rotation += (0.2f) * Game->deltaTime;

    //  RENDER

    // set which to render
    for (int i = 0; i < testStallBuffer->count; i++)
    {
        ModelRenderData modelRenderData = {};
        TestStall* entity = (TestStall*)GetEntity(&Data->em, testStallEntitiesInBuffer[i].handle);
        modelRenderData = entity->modelRenderData;
        PushBack(&testStallEntitiesToRender, modelRenderData);
    }
    for (int i = 0; i < 1; i++)
    {
        ModelRenderData modelRenderData = {};
        Terrain* entity = (Terrain*)GetEntity(&Data->em, terrainEntitiesInBuffer[i].handle);
        modelRenderData = entity->modelRenderData;
        PushBack(&terrainEntitiesToRender, modelRenderData);
    }
    for (int i = 0; i < 1; i++)
    {
        ModelRenderData modelRenderData = {};
        Fern* entity = (Fern*)GetEntity(&Data->em, fernEntitiesInBuffer[i].handle);
        modelRenderData = entity->modelRenderData;
        PushBack(&fernEntitiesToRender, modelRenderData);

    }
    for (int i = 0; i < 1; i++)
    {
        ModelRenderData modelRenderData = {};
        Wall* entity = (Wall*)GetEntity(&Data->em, wallEntitiesInBuffer[i].handle);
        modelRenderData = entity->modelRenderData;
        PushBack(&wallEntitiesToRender, modelRenderData);

    }

    for (int i = 0; i < 40; i++)
    {
        ModelRenderData modelRenderData = {};
        Post* entity = (Post*)GetEntity(&Data->em, postEntitiesInBuffer[i].handle);
        modelRenderData = entity->modelRenderData;
        PushBack(&postEntitiesToRender, modelRenderData);

    }
    for (int i = 0; i < 1; i++)
    {
        ModelRenderData modelRenderData = {};
        Player* entity = (Player*)GetEntity(&Data->em, playerEntitiesInBuffer[i].handle);
        modelRenderData = entity->modelRenderData;
        PushBack(&playerEntitiesToRender, modelRenderData);

    }
    //DrawOBJModel(&stallMesh2, V3(0), V3(10.0f, 10.0f, 10.0f), rotation, RGB(1.0f, 0.3f, 0.3f), &stallTexture);
    DrawOBJModels(terrainEntitiesToRender, Data->sunLight, &Game->terrain, &stallTexture, &Game->terrainShader);
    DrawOBJModels(fernEntitiesToRender, Data->sunLight, &fernMesh, &Data->sprites.fernTexture, &Game->modelShader);
   // DrawOBJModels(testStallEntitiesToRender, Data->sunLight, &Data->meshes.stallMesh, &stallTexture, &Game->modelShader);
    DrawOBJModels(wallEntitiesToRender, Data->sunLight, &Data->meshes.wall1Mesh, &Data->sprites.wall1Texture, &Game->modelShader);
    DrawOBJModels(postEntitiesToRender, Data->sunLight, &Data->meshes.postMesh, &Data->sprites.wall1Texture, &Game->modelShader);
    
    
    if (cam->controllerType == ControllerType_ThirdPerson)
    {
        DrawOBJModels(playerEntitiesToRender, Data->sunLight, &Data->meshes.playerMesh, &Data->sprites.wall1Texture, &Game->modelShader);
    }

    RenderGUI(*guiBuffer, guiEntitiesInBuffer);
}
