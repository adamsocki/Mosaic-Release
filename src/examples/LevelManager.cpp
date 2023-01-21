
void InitializeLevelFromCode()
{
	// create walls
	EntityTypeBuffer* wallBuffer = &Data->em.buffers[EntityType_Wall];
	Wall* wallEntitiesInBuffer = (Wall*)wallBuffer->entities;

	Wall* wallEntity = (Wall*)GetEntity(&Data->em, wallEntitiesInBuffer[0].handle);

	wallEntity->modelRenderData.position = V3(-10, 0, -50);
	wallEntity->modelRenderData.scale = V3(5, 20, 100);
}

void CreateLevelPalatte_LE()
{
	// PALLATE BACKGROUND - TRANSPARENT TOP RIGHT
		// sizes are conditional on screen width/height size
	Data->le.lp.box.pos.x = Game->screenWidth - (Game->screenWidth * 0.25f);
	Data->le.lp.box.pos.y = 0;
	Data->le.lp.box.size.x = Game->screenWidth - (Game->screenWidth * 0.75f);
	Data->le.lp.box.size.y = Game->screenHeight * 0.10f;
	Data->le.lp.box.color = V4(0.5f, 0.4f, 0.8f, 0.5f);

	// BUTTONS - ADD BUTONS TO PALLATE BACKGROUND
		// sizes are conditional on PALLATE BACKGROUND size
	// SAVE BUTTON
	Data->le.lp.saveButton = {};
	Data->le.lp.saveButton.pos.x = Data->le.lp.box.pos.x + (Data->le.lp.box.size.x * 0.75f);
	Data->le.lp.saveButton.pos.y = Data->le.lp.box.size.y - (Data->le.lp.box.size.y * 0.5f);
	Data->le.lp.saveButton.size.x = Data->le.lp.box.size.x * 0.2f;
	Data->le.lp.saveButton.size.y = Data->le.lp.box.size.y * 0.33f;
	Data->le.lp.saveButton.posMin.x = Data->le.lp.saveButton.pos.x;
	Data->le.lp.saveButton.posMin.y = Data->le.lp.saveButton.pos.y;
	Data->le.lp.saveButton.posMax.x = Data->le.lp.saveButton.pos.x + Data->le.lp.saveButton.size.x;
	Data->le.lp.saveButton.posMax.y = Data->le.lp.saveButton.pos.y + Data->le.lp.saveButton.size.y;
	Data->le.lp.saveButton.colorMouse   = V4(0.1f, 1.0f, 0.1f, 0.6f);
	Data->le.lp.saveButton.colorNoMouse = V4(1.0f, 1.0f, 0.5f, 0.6f);
	Data->le.lp.saveButton.colorClick   = V4(0.6f, 0.6f, 0.6f, 0.6f);
	Data->le.lp.saveButton.text = "SAVE";
	Data->le.lp.saveButton.textPos.x = Data->le.lp.saveButton.pos.x + (Data->le.lp.saveButton.size.x * 0.05f);
	Data->le.lp.saveButton.textPos.y = Data->le.lp.saveButton.pos.y + (Data->le.lp.saveButton.size.y * 0.8f);
	Data->le.lp.saveButton.textSize = Data->le.lp.saveButton.size.y / 2;
	Data->le.lp.saveButton.textColor = V4(0.1f, 0.1f, 0.1f, 1.0f);

	// LOAD BUTTON
	Data->le.lp.loadButton = {};
	Data->le.lp.loadButton.pos.x = Data->le.lp.box.pos.x + (Data->le.lp.box.size.x * 0.5f);
	Data->le.lp.loadButton.pos.y = Data->le.lp.box.size.y - (Data->le.lp.box.size.y * 0.5f);
	Data->le.lp.loadButton.size.x = Data->le.lp.box.size.x * 0.2f;
	Data->le.lp.loadButton.size.y = Data->le.lp.box.size.y * 0.33f;
	Data->le.lp.loadButton.posMin.x = Data->le.lp.loadButton.pos.x;
	Data->le.lp.loadButton.posMin.y = Data->le.lp.loadButton.pos.y;
	Data->le.lp.loadButton.posMax.x = Data->le.lp.loadButton.pos.x + Data->le.lp.loadButton.size.x;
	Data->le.lp.loadButton.posMax.y = Data->le.lp.loadButton.pos.y + Data->le.lp.loadButton.size.y;
	Data->le.lp.loadButton.colorMouse = V4(0.1f, 1.0f, 0.1f, 0.6f);
	Data->le.lp.loadButton.colorNoMouse = V4(1.0f, 1.0f, 0.5f, 0.6f);
	Data->le.lp.loadButton.colorClick = V4(0.6f, 0.6f, 0.6f, 0.6f);
	Data->le.lp.loadButton.text = "LOAD";
	Data->le.lp.loadButton.textPos.x = Data->le.lp.loadButton.pos.x + (Data->le.lp.loadButton.size.x * 0.05f);
	Data->le.lp.loadButton.textPos.y = Data->le.lp.loadButton.pos.y + (Data->le.lp.loadButton.size.y * 0.8f);
	Data->le.lp.loadButton.textSize = Data->le.lp.loadButton.size.y / 2;
	Data->le.lp.loadButton.textColor = V4(0.1f, 0.1f, 0.1f, 1.0f);
}

void LogicLevelPalatte_LE()
{
	// SAVE BUTTON
	// MOUSE COLLISSION
	Data->le.lp.saveButton.isMouseOver = TestPointAABB(Data->mouse.positionPixel, Data->le.lp.saveButton.posMin, Data->le.lp.saveButton.posMax);
	if (Data->le.lp.saveButton.isMouseOver)
	{	// MOUSE OVER DETECTION
		Data->le.lp.saveButton.color = Data->le.lp.saveButton.colorMouse;
		if (InputHeld(Mouse, Input_MouseLeft))
		{	// CLICK EVENT DETECTION
			Data->le.lp.saveButton.color = Data->le.lp.saveButton.colorClick;
		}
		else
		{
			Data->le.lp.saveButton.color = Data->le.lp.saveButton.colorMouse;
		}
		if (InputPressed(Mouse, Input_MouseLeft))
		{	// CLICK EVENT DETECTION
			Data->le.lp.saveButton.isMouseClick = true;
		}
	}
	else
	{
		Data->le.lp.saveButton.color = Data->le.lp.saveButton.colorNoMouse;
	}
	
	if (Data->le.lp.saveButton.isMouseClick)
	{	// TODO - CLICK EVENT TRIGGER

		Data->le.lp.saveButton.isMouseClick = false;
	}

	// LOAD BUTTON
	// MOUSE COLLISSION
	Data->le.lp.loadButton.isMouseOver = TestPointAABB(Data->mouse.positionPixel, Data->le.lp.loadButton.posMin, Data->le.lp.loadButton.posMax);
	if (Data->le.lp.loadButton.isMouseOver)
	{	// MOUSE OVER DETECTION
		Data->le.lp.loadButton.color = Data->le.lp.loadButton.colorMouse;
		if (InputHeld(Mouse, Input_MouseLeft))
		{	// CLICK EVENT DETECTION
			Data->le.lp.loadButton.color = Data->le.lp.loadButton.colorClick;
		}
		else
		{
			Data->le.lp.loadButton.color = Data->le.lp.loadButton.colorMouse;
		}
		if (InputPressed(Mouse, Input_MouseLeft))
		{	// CLICK EVENT DETECTION
			Data->le.lp.loadButton.isMouseClick = true;
		}
	}
	else
	{
		Data->le.lp.loadButton.color = Data->le.lp.loadButton.colorNoMouse;
	}

	if (Data->le.lp.loadButton.isMouseClick)
	{	// TODO - CLICK EVENT TRIGGER
		LoadLevelParse(Data->le.currentLevel);
		Data->le.lp.loadButton.isMouseClick = false;
	}
}

void RenderLevelPalatte_LE()
{
	DrawRectScreen(Data->le.lp.box.pos, Data->le.lp.box.size, Data->le.lp.box.color);

	DrawRectScreen(Data->le.lp.saveButton.pos, Data->le.lp.saveButton.size, Data->le.lp.saveButton.color);
	DrawTextScreenPixel(&Game->serifFont, Data->le.lp.saveButton.textPos, Data->le.lp.saveButton.textSize, Data->le.lp.saveButton.textColor, false, Data->le.lp.saveButton.text);

	DrawRectScreen(Data->le.lp.loadButton.pos, Data->le.lp.loadButton.size, Data->le.lp.loadButton.color);
	DrawTextScreenPixel(&Game->serifFont, Data->le.lp.loadButton.textPos, Data->le.lp.loadButton.textSize, Data->le.lp.loadButton.textColor, false, Data->le.lp.loadButton.text);

}