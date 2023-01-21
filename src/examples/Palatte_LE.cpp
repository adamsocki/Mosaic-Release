
void InitPalatte_LE()
{
	CreateEntityPalatte_LE();				// CREATE ENTITY PALATTE
	CreateLevelPalatte_LE();				// CREATE LEVEL PALATTE
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
	// TODO - HANDLE LEVEL LOAD
	// TODO - HANDLE LEVEL SAVE
	// TODO - HANDLE MOUSE DETECTION
}

void RenderPalatte_LE()
{
	RenderEntityPalatte_LE();				// DISPLAY ENTITY PALATTE
	RenderLevelPalatte_LE();				// DISPLAY LEVEL PALATTE
}