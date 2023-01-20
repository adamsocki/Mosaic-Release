
void InitPalatte_LE()
{
	// TODO - CREATE ENTITY PALATTE
	CreateLevelPalatte_LE();// TODO - CREATE LEVEL PALATTE
}


void LogicPalatte_LE()
{
	// ************************
	// LOGIC FOR ENTITY PALATTE
	// ************************
	// TODO - HANDLE MOUSE DETECTION
	// TODO - HANDLE ENTITY REFERENCE
	// TODO - HANDLE ENTITY CREATION
	// TODO - HANDLE ENTITY EDIT
	// TODO - HANDLE ENTITY DELETE

	// ***********************
	// LOGIC FOR LEVEL PALATTE
	// ***********************
	// TODO - HANDLE LEVEL CHANGE
	// TODO - HANDLE LEVEL SAVE
	// TODO - HANDLE MOUSE DETECTION

}




void RenderPalatte_LE()
{
	// TODO - DISPLAY ENTITY PALATTE

	// TODO - DISPLAY LEVEL PALATTE

	DrawRectScreen(Data->le.lp.box.pos, Data->le.lp.box.size, Data->le.lp.box.color);
	DrawRectScreen(Data->le.lp.saveButton.pos, Data->le.lp.saveButton.size, Data->le.lp.saveButton.color);

}