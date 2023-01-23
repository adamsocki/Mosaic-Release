
MyData *Data = NULL;

#include "LoadSprites.cpp"
#include "EntityManager.cpp"
#include "RenderManager.cpp"
#include "TerrainManager.cpp"
#include "GUI_Editor.cpp"

#include "MemoryArray.cpp"
#include "LevelManager.cpp"
#include "CameraManager.cpp"
#include "PlayerManager.cpp"
#include "MouseManager.cpp"

#include <iostream>
#include <vector>


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
    InitOBJMesh(&Game->terrain);

    InGameCameraInit();

    ///InitOBJMesh(&stallMesh);
    ///GenerateQuadMesh(&Data->meshes.quadMesh);

    
 
    ///BuildGUI("Terrian", 3, true, true, true, 2);

    InitMouse();
    InitMousePicker();

    InitializeStartingEntities();
    InitializeLevelFromCode();
    Data->rm.skyColor = RGB(0.12f, 0.14f, 0.0f);
}

vec2 position = V2(4, 0);

vec2 scale = V2(1, 1);

void MyGameUpdate() {


    // SWITCH GAME MODES
    // SWITCH TO LEVEL EDITOR
    


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
    UpdateMousePicker(terrainEntity);
    PlayerMover(playerEntity, *terrainEntity);

    // INPUT LOGIC FOR CAMERA MOVEMENT
    InGameCameraUpdate();


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
   
    DrawOBJModels(terrainEntitiesToRender, Data->sunLight, &Game->terrain, &Data->sprites.stallTexture, &Game->terrainShader, Data->rm.skyColor);
    DrawOBJModels(fernEntitiesToRender, Data->sunLight, &Game->fernMesh, &Data->sprites.fernTexture, &Game->modelShader, Data->rm.skyColor);
    DrawOBJModels(wallEntitiesToRender, Data->sunLight, &Game->wall1Mesh, &Data->sprites.wall1Texture, &Game->modelShader, Data->rm.skyColor);
    DrawOBJModels(postEntitiesToRender, Data->sunLight, &Game->postMesh, &Data->sprites.wall1Texture, &Game->modelShader, Data->rm.skyColor);
    DrawOBJModels(playerEntitiesToRender, Data->sunLight, &Game->playerMesh, &Data->sprites.wall1Texture, &Game->modelShader, Data->rm.skyColor);
    
   /// RenderGUI(*guiBuffer, guiEntitiesInBuffer);

    DeallocateDynamicArray(&entitiesToRender);
    DeallocateDynamicArray(&testStallEntitiesToRender);
    DeallocateDynamicArray(&terrainEntitiesToRender);
    DeallocateDynamicArray(&fernEntitiesToRender);
    DeallocateDynamicArray(&wallEntitiesToRender);
    DeallocateDynamicArray(&postEntitiesToRender);
    DeallocateDynamicArray(&playerEntitiesToRender);
}
