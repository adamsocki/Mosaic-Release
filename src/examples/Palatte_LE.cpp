
void InitPalatte_LE()
{
	// TODO - CREATE ENTITY PALATTE
	CreateEntityPalatte_LE();
	CreateLevelPalatte_LE();// TODO - CREATE LEVEL PALATTE
}


void LogicPalatte_LE()
{
	// ************************
	// LOGIC FOR ENTITY PALATTE
	// ************************
	LogicEntityPalatte_LE();
	// TODO - HANDLE MOUSE DETECTION
	// TODO - HANDLE ENTITY REFERENCE
	// TODO - HANDLE ENTITY CREATION
	// TODO - HANDLE ENTITY EDIT
	// TODO - HANDLE ENTITY DELETE

	// ***********************
	// LOGIC FOR LEVEL PALATTE
	// ***********************
	LogicLevelPalatte_LE();
	// TODO - HANDLE LEVEL CHANGE
	// TODO - HANDLE LEVEL SAVE
	// TODO - HANDLE MOUSE DETECTION

}




void RenderPalatte_LE()
{
	// TODO - DISPLAY ENTITY PALATTE
	RenderEntityPalatte_LE();
	// TODO - DISPLAY LEVEL PALATTE
	RenderLevelPalatte_LE();
}