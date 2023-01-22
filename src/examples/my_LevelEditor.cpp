MyData_LE* Data = NULL;

#include "EntityManager.cpp"
#include "CameraManager_LE.cpp"
#include "MouseManager.cpp"
#include "LevelParser.cpp"
#include "LevelManager.cpp"
#include "Palatte_LE.cpp"
#include "LoadSprites.cpp"
#include "RenderManager.cpp"
#include "assimpLoader.cpp"
#include "LevelManager_LE.cpp"	


void MyInit()
{
	
	Game->myData = malloc(sizeof(MyData_LE));				// INIT GAME DATA	
	memset(Game->myData, 0, sizeof(MyData_LE));
	Data = (MyData_LE*)Game->myData;
	Data->le.currentLevel = -1;
	Data->engineMode = LevelEditorMode;
	Data->sunLight.position = V3(1000.0f, 1000.0f, 1000.0f);
	Data->sunLight.color = V3(1.0f, 1.0f, 1.0f);

	// TODO - INIT LEVEL EDITOR DATA
	InitializeEntityManager();								// INIT ENTITIES
	InitializeEntityBuffers();
	CameraInit_LE();
	InitPalatte_LE();										// INIT PALATTES
	InitMouse();											// INIT MOUSE
	//InitLevel_LE();										// TODO - INIT LEVEL


	Data->meshes.wall1Mesh = LoadOBJv2("data/wall1.obj");
	InitOBJMesh(&Data->meshes.wall1Mesh);

}

void MyGameUpdate()
{
	ClearColor(V4(0.4f, 0.4f, 0.4f, 1.0f));

	UpdateMouseData();										// MOUSE DATA
	DynamicArray<ModelRenderData> wallEntitiesToRender = MakeDynamicArray<ModelRenderData>(&Game->frameMem, 100);
	EntityTypeBuffer* wallBuffer = &Data->em.buffers[EntityType_Wall];
	Wall* wallEntitiesInBuffer = (Wall*)wallBuffer->entities;

	// *****
	// LOGIC
	// *****
	// LogicEditMode();
	LogicPalatte_LE();										// UPDATE PALATTES LOGIC
	CameraUpdate_LE();
	// ******
	// RENDER
	// ******

	// RENDER MOUSE
	RenderMouse_LE();
	// TODO - RENDER LEVEL SCENE
	if (Data->le.currentLevel == 0)
	{
		for (int i = 0; i < 1; i++)
		{
			ModelRenderData modelRenderData = {};
			Wall* entity = (Wall*)GetEntity(&Data->em, wallEntitiesInBuffer[i].handle);
			modelRenderData = entity->modelRenderData;
			PushBack(&wallEntitiesToRender, modelRenderData);

		}
		DrawOBJModels(wallEntitiesToRender, Data->sunLight, &Data->meshes.wall1Mesh, &Data->sprites.wall1Texture, &Game->modelShader);
	}
	
	RenderPalatte_LE();										// RENDER PALATTE

	RenderLevel_LE(wallEntitiesToRender);

	DeallocateDynamicArray(&wallEntitiesToRender);
}