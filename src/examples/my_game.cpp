




#include "structs.cpp"

MyData *Data = NULL;
#include "LoadSprites.cpp"
#include "EntityManager.cpp"
#include "RenderManager.cpp"
#include "TerrainManager.cpp"
#include "assimpLoader.cpp"


Sprite lemonSprite;
OBJMesh stallMesh = {};
OBJMesh fernMesh = {};
OBJMesh stallMesh2 = {};


Sprite stallTexture;
real32 rotation = {};

void MyInit() {
    Game->myData = malloc(sizeof(MyData));
    memset(Game->myData, 0, sizeof(MyData));

    Data = (MyData *)Game->myData;

    Data->sunLight.position = V3(0, 30.0f, 0);
    Data->sunLight.color = V3(0.8f, 0.8f, 1.0f);

    LoadSprites();
    InitializeEntityManager();
    InitializeEntityBuffers();

    InitializeStartingEntities();

    GenerateTerrain();
    // All sprites must be png files
    // You provide the path to the png like "directory/to/my/file/file_name.png"
    // In this case I have put the pngs inside the "data" directory.
    LoadSprite(&Data->sprite, "data/galaga_ship.png");
    LoadSprite(&Data->sprite2, "data/van_gogh.png");
    LoadSprite(&stallTexture, "data/stallTexture.png");

    LoadSprite(&lemonSprite, "data/bad_lemon.png");
    LoadSprite(&Data->sprites.fernTexture, "data/fern.png");

   // LoadSoundClip("data/sfx/flute_breathy_c4.wav", &Data->sound);

    //TinyObject();
    stallMesh = LoadOBJv2("data/stall.obj");
    fernMesh = LoadOBJv2("data/fern.obj");
    InitOBJMesh(&stallMesh);
    InitOBJMesh(&Game->terrain);
    InitOBJMesh(&fernMesh);

    stallMesh2 = LoadOBJv2("data/stall.obj");
    InitOBJMesh(&stallMesh2);

}


vec2 position = V2(4, 0);

vec2 scale = V2(1, 1);

void MyGameUpdate() {
    // This sets the background color. 
    ClearColor(RGB(0.0f, 0.14f, 0.0f));

    DynamicArray<EntityHandle> entitiesToRender = MakeDynamicArray<EntityHandle>(&Game->frameMem, 100);

    DynamicArray<ModelRenderData> testStallEntitiesToRender = MakeDynamicArray<ModelRenderData>(&Game->frameMem, 100);
    DynamicArray<ModelRenderData> terrainEntitiesToRender = MakeDynamicArray<ModelRenderData>(&Game->frameMem, 100);
    DynamicArray<ModelRenderData> fernEntitiesToRender = MakeDynamicArray<ModelRenderData>(&Game->frameMem, 100);

    // LOGIC

    EntityTypeBuffer* testStallBuffer = &Data->em.buffers[EntityType_Test];
    EntityTypeBuffer* terrainBuffer = &Data->em.buffers[EntityType_Terrain];
    EntityTypeBuffer* fernBuffer = &Data->em.buffers[EntityType_Fern];

    TestStall* testStallEntitiesInBuffer = (TestStall*)testStallBuffer->entities;
    Terrain* terrainEntitiesInBuffer = (Terrain*)terrainBuffer->entities;
    Fern* fernEntitiesInBuffer = (Fern*)fernBuffer->entities;

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
    HashTable<Models, DynamicArray<EntityHandle> > hash;

    AllocateHashTable(&hash, 100, &Game->frameMem);

    // INPUT LOGIC FOR CAMERA MOVEMENT
    Camera* cam = &Game->camera;
    real32 cameraSpeed = 28.0f;
    real32 rotationSpeed = 0.4f;

    if (InputHeld(Keyboard, Input_W))
    {
        Game->cameraPosition.z += cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_S))
    {
        Game->cameraPosition.z -= cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_A))
    {
        Game->cameraPosition.x += cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_D))
    {
        Game->cameraPosition.x -= cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_UpArrow)) {
        Game->cameraPosition.y += cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_DownArrow)) {
        Game->cameraPosition.y -= cameraSpeed * Game->deltaTime;
    }

    

    rotation += (0.2f) * Game->deltaTime;

    //  RENDER


    //DrawOBJModel(&stallMesh2, V3(0), V3(10.0f, 10.0f, 10.0f), rotation, RGB(1.0f, 0.3f, 0.3f), &stallTexture);
    DrawOBJModels(terrainEntitiesToRender, Data->sunLight, &Game->terrain, &stallTexture, &Game->terrainShader);
    DrawOBJModels(fernEntitiesToRender, Data->sunLight, &fernMesh, &Data->sprites.fernTexture, &Game->modelShader);
    DrawOBJModels(testStallEntitiesToRender, Data->sunLight, &stallMesh2, &stallTexture, &Game->modelShader);
}
