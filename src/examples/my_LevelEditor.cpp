MyData_LE* Data = NULL;

#include "EntityManager.cpp"
#include "CameraManager.cpp"
///#include "CameraManager_LE.cpp"
#include "MouseManager.cpp"
#include "LevelParser.cpp"
#include "TerrainManager.cpp"
#include "LevelManager.cpp"
#include "Palatte_LE.cpp"
#include "LoadSprites.cpp"
#include "RenderManager.cpp"
#include "LevelManager_LE.cpp"	

#include "LevelEditor.cpp"



void MyInit()
{
	
	Game->myData = malloc(sizeof(MyData_LE));				// INIT GAME DATA	
	memset(Game->myData, 0, sizeof(MyData_LE));
	Data = (MyData_LE*)Game->myData;
	Data->le.currentLevel = -1;
	Data->engineMode = LevelEditorMode;

	Data->sunLight.position = V3(1000.0f, 1000.0f, 1000.0f);
	Data->sunLight.color = V3(1.0f, 1.0f, 1.0f);
	LoadSprites();
	// TODO - INIT LEVEL EDITOR DATA
	InitializeEntityManager();								// INIT ENTITIES
	InitializeEntityBuffers();

	GenerateTerrain("data/cursor_red.png");
	InitOBJMesh(&Game->terrain);

	InGameCameraInit();
	InitPalatte_LE();										// INIT PALATTES
	CameraInit_LE();
	InitMouse();											// INIT MOUSE
	//InitLevel_LE();										// TODO - INIT LEVEL

	InitializeStartingEntities();

	Data->meshes.wall1Mesh = LoadOBJv2("data/wall1.obj");
	InitOBJMesh(&Data->meshes.wall1Mesh);
	InitializeLevelFromCode();
	Data->rm.skyColor = RGB(0.12f, 0.14f, 0.0f);

}

void MyGameUpdate()
{
	ClearColor(V4(0.4f, 0.4f, 0.4f, 1.0f));

	UpdateMouseData();										// MOUSE DATA
	
	

	// *****
	// LOGIC
	// *****
	// LogicEditMode();
	LogicPalatte_LE();										// UPDATE PALATTES LOGIC
	Mover_LE();
	InGameCameraUpdate();
	// ******
	// RENDER
	// ******

	// RENDER MOUSE
	RenderMouse_LE();
	// TODO - RENDER LEVEL SCENE

	// TESTING


	
	TestRender();
	RenderPalatte_LE();										// RENDER PALATTE

	//RenderLevel_LE(wallEntitiesToRender);

}