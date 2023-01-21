MyData_LE* Data = NULL;

#include "EntityManager.cpp"
#include "MouseManager.cpp"
#include "LevelParser.cpp"
#include "LevelManager.cpp"
#include "Palatte_LE.cpp"


void MyInit()
{
	
	Game->myData = malloc(sizeof(MyData_LE));				// INIT GAME DATA	
	memset(Game->myData, 0, sizeof(MyData_LE));
	Data = (MyData_LE*)Game->myData;
	Data->le.currentLevel = 1;


	// TODO - INIT LEVEL EDITOR DATA
	InitializeEntityManager();								// INIT ENTITIES

	InitPalatte_LE();										// INIT PALATTES
	InitMouse();											// INIT MOUSE
	//InitLevel_LE();										// TODO - INIT LEVEL
}

void MyGameUpdate()
{
	UpdateMouseData();										// MOUSE DATA
	
	// *****
	// LOGIC
	// *****

	LogicPalatte_LE();										// UPDATE PALATTES LOGIC

	// ******
	// RENDER
	// ******

	RenderPalatte_LE();										// RENDER PALATTE
	// RENDER MOUSE
	RenderMouse_LE();
	// TODO - RENDER LEVEL SCENE

}