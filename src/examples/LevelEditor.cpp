MyData_LE* Data = NULL;

#include "EntityManager.cpp"
#include "LevelManager.cpp"
#include "Palatte_LE.cpp"
#include "MouseManager.cpp"


void MyInit()
{
	// INIT GAME DATA
	Game->myData = malloc(sizeof(MyData_LE));
	memset(Game->myData, 0, sizeof(MyData_LE));
	Data = (MyData_LE*)Game->myData;

	// TODO - INIT LEVEL EDITOR DATA
	
	// INIT - 
	InitializeEntityManager();

	InitPalatte_LE();			// INIT PALATTE
	InitMouse_LE();				// INIT MOUSE
	//InitLevel_LE();				// TODO - INIT LEVEL
}


void MyGameUpdate()
{
	// *****
	// LOGIC
	// *****

	// TODO - UPDATE PALATTE LOGIC
	LogicPalatte_LE();
	// TODO - MOUSE SELECTION LOGIC
	LogicMouse_LE();

	// ******
	// RENDER
	// ******

	// TODO - RENDER PALATTE
	RenderPalatte_LE();
	// TODO - RENDER MOUSE
	RenderMouse_LE();
	// TODO - RENDER LEVEL SCENE


}