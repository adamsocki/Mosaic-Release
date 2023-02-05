






// LEVEL EDITOR 
void CreateEntityPalatte_LE()
{
	// PALLATE BACKGROUND
	Data->le.ep.box.pos.x = Game->screenWidth * 0.025f;
	Data->le.ep.box.pos.y = Game->screenHeight * 0.05f;
	Data->le.ep.box.size.x = Game->screenWidth * 0.25f;
	Data->le.ep.box.size.y = Game->screenHeight - (Game->screenHeight * 0.05f * 2);
	Data->le.ep.box.color = V4(0.5f, 0.8f, 0.8f, 0.5f);
	Data->le.ep.box.isCollapsed = false;
	Data->le.ep.box.sizeExpanded.x = Game->screenWidth * 0.25f;
	Data->le.ep.box.sizeExpanded.y = Game->screenHeight - (Game->screenHeight * 0.05f * 2);
	Data->le.ep.box.sizeCollapsed.x = Data->le.ep.box.size.x;
	Data->le.ep.box.sizeCollapsed.y = Data->le.ep.box.pos.y - (Data->le.ep.box.size.x * 0.05f) + (Data->le.ep.box.size.x * 0.07f / 3);
	Data->le.ep.box.text = "Entity Editor"; 
	Data->le.ep.box.textPos.x = Data->le.ep.box.pos.x + (Data->le.ep.box.size.x * 0.05f);
	Data->le.ep.box.textPos.y = Data->le.ep.box.pos.y + (Data->le.ep.box.size.y * 0.035f);
	Data->le.ep.box.textSize = Data->le.ep.box.sizeCollapsed.y / 2;
	Data->le.ep.box.textColor = V4(0.1f, 0.1f, 0.1f, 1.0f);

	// BUTTONS - ADD BUTONS TO PALLATE BACKGROUND
		// sizes are conditional on PALLATE BACKGROUND size
	// COLLAPSE WINDOW BUTTON		
	Data->le.ep.collapseButton = {};
	Data->le.ep.collapseButton.size.x = Data->le.ep.box.size.x * 0.05f;
	Data->le.ep.collapseButton.size.y = Data->le.ep.box.size.x * 0.05f;
	Data->le.ep.collapseButton.pos.x = Data->le.ep.box.pos.x + (Data->le.ep.box.size.x * 0.93f);
	Data->le.ep.collapseButton.pos.y = Data->le.ep.box.pos.y + (Data->le.ep.box.size.x * 0.07f) - Data->le.ep.collapseButton.size.y;
	Data->le.ep.collapseButton.posMin.x = Data->le.ep.collapseButton.pos.x;
	Data->le.ep.collapseButton.posMin.y = Data->le.ep.collapseButton.pos.y;
	Data->le.ep.collapseButton.posMax.x = Data->le.ep.collapseButton.pos.x + Data->le.ep.collapseButton.size.x;
	Data->le.ep.collapseButton.posMax.y = Data->le.ep.collapseButton.pos.y + Data->le.ep.collapseButton.size.y;
	Data->le.ep.collapseButton.colorMouse   = V4(0.85f, 0.95f, 0.95f, 0.6f);
	Data->le.ep.collapseButton.colorNoMouse = V4(0.6f, 0.7f, 0.7f, 0.6f);
	Data->le.ep.collapseButton.colorClick   = V4(1.0f, 1.0, 1.0f, 0.6f);
	Data->le.ep.collapseButton.color = {};
	
	
	

	// CHANGE ENTITY BUTTON - LEFT
	Data->le.ep.changeEntityLeftButton = {};
	Data->le.ep.changeEntityLeftButton.pos.x = Data->le.ep.box.pos.x + (Data->le.ep.box.size.x * 0.05f);
	Data->le.ep.changeEntityLeftButton.pos.y = Data->le.ep.box.size.y - (Data->le.ep.box.size.y * 0.85f);
	Data->le.ep.changeEntityLeftButton.size.x = Data->le.ep.box.size.x * 0.1f;
	Data->le.ep.changeEntityLeftButton.size.y = Data->le.ep.box.size.x * 0.1f;
	Data->le.ep.changeEntityLeftButton.posMin.x = Data->le.ep.changeEntityLeftButton.pos.x;
	Data->le.ep.changeEntityLeftButton.posMin.y = Data->le.ep.changeEntityLeftButton.pos.y;
	Data->le.ep.changeEntityLeftButton.posMax.x = Data->le.ep.changeEntityLeftButton.pos.x + Data->le.ep.changeEntityLeftButton.size.x;
	Data->le.ep.changeEntityLeftButton.posMax.y = Data->le.ep.changeEntityLeftButton.pos.y + Data->le.ep.changeEntityLeftButton.size.y;
	Data->le.ep.changeEntityLeftButton.text = "L";
	Data->le.ep.changeEntityLeftButton.textPos.x = Data->le.ep.changeEntityLeftButton.pos.x + (Data->le.ep.changeEntityLeftButton.size.x * 0.2f);
	Data->le.ep.changeEntityLeftButton.textPos.y = Data->le.ep.changeEntityLeftButton.pos.y + (Data->le.ep.changeEntityLeftButton.size.y * 0.8f);
	Data->le.ep.changeEntityLeftButton.textSize = Data->le.ep.changeEntityLeftButton.size.y / 2;
	Data->le.ep.changeEntityLeftButton.textColor = V4(0.1f, 0.1f, 0.1f, 1.0f);
	Data->le.ep.changeEntityLeftButton.colorMouse = V4(0.85f, 0.7f, 0.95f, 0.6f);
	Data->le.ep.changeEntityLeftButton.colorNoMouse = V4(0.5f, 0.7f, 0.95f, 0.6f);
	Data->le.ep.changeEntityLeftButton.colorClick = V4(0.3f, 0.2f, 0.2f, 0.6f);
	Data->le.ep.changeEntityLeftButton.color = V4(0.5f, 0.7f, 0.95f, 0.6f);

	// CHANGE ENTITY BUTTON - RIGHT
	Data->le.ep.changeEntityRightButton = {};
	Data->le.ep.changeEntityRightButton.pos.x = Data->le.ep.box.pos.x + (Data->le.ep.box.size.x * 0.05f);
	Data->le.ep.changeEntityRightButton.pos.y = Data->le.ep.box.size.y - (Data->le.ep.box.size.y * 0.785f);
	Data->le.ep.changeEntityRightButton.size.x = Data->le.ep.box.size.x * 0.1f;
	Data->le.ep.changeEntityRightButton.size.y = Data->le.ep.box.size.x * 0.1f;
	Data->le.ep.changeEntityRightButton.posMin.x = Data->le.ep.changeEntityRightButton.pos.x;
	Data->le.ep.changeEntityRightButton.posMin.y = Data->le.ep.changeEntityRightButton.pos.y;
	Data->le.ep.changeEntityRightButton.posMax.x = Data->le.ep.changeEntityRightButton.pos.x + Data->le.ep.changeEntityRightButton.size.x;
	Data->le.ep.changeEntityRightButton.posMax.y = Data->le.ep.changeEntityRightButton.pos.y + Data->le.ep.changeEntityRightButton.size.y;
	Data->le.ep.changeEntityRightButton.text = "R";
	Data->le.ep.changeEntityRightButton.textPos.x = Data->le.ep.changeEntityRightButton.pos.x + (Data->le.ep.changeEntityRightButton.size.x * 0.2f);
	Data->le.ep.changeEntityRightButton.textPos.y = Data->le.ep.changeEntityRightButton.pos.y + (Data->le.ep.changeEntityRightButton.size.y * 0.8f);
	Data->le.ep.changeEntityRightButton.textSize = Data->le.ep.changeEntityRightButton.size.y / 2;
	Data->le.ep.changeEntityRightButton.textColor = V4(0.1f, 0.1f, 0.1f, 1.0f);
	Data->le.ep.changeEntityRightButton.colorMouse = V4(0.85f, 0.7f, 0.95f, 0.6f);
	Data->le.ep.changeEntityRightButton.colorNoMouse = V4(0.5f, 0.7f, 0.95f, 0.6f);
	Data->le.ep.changeEntityRightButton.colorClick = V4(0.3f, 0.2f, 0.2f, 0.6f);
	Data->le.ep.changeEntityRightButton.color = V4(0.5f, 0.7f, 0.95f, 0.6f);

	// CREATE ENTITY BUTTON
	Data->le.ep.createEntityButton = {};
	Data->le.ep.createEntityButton.pos.x = Data->le.ep.box.pos.x + (Data->le.ep.box.size.x * 0.05f);
	Data->le.ep.createEntityButton.pos.y = Data->le.ep.box.size.y - (Data->le.ep.box.size.y * 0.725f);
	Data->le.ep.createEntityButton.size.x = Data->le.ep.box.size.x * 0.3f;
	Data->le.ep.createEntityButton.size.y = Data->le.ep.box.size.x * 0.08f;
	Data->le.ep.createEntityButton.posMin.x = Data->le.ep.createEntityButton.pos.x;
	Data->le.ep.createEntityButton.posMin.y = Data->le.ep.createEntityButton.pos.y;
	Data->le.ep.createEntityButton.posMax.x = Data->le.ep.createEntityButton.pos.x + Data->le.ep.createEntityButton.size.x;
	Data->le.ep.createEntityButton.posMax.y = Data->le.ep.createEntityButton.pos.y + Data->le.ep.createEntityButton.size.y;
	Data->le.ep.createEntityButton.text = "CREATE";
	Data->le.ep.createEntityButton.textPos.x = Data->le.ep.createEntityButton.pos.x + (Data->le.ep.createEntityButton.size.x * 0.05f);
	Data->le.ep.createEntityButton.textPos.y = Data->le.ep.createEntityButton.pos.y + (Data->le.ep.createEntityButton.size.y * 0.8f);
	Data->le.ep.createEntityButton.textSize = Data->le.ep.createEntityButton.size.y / 2;
	Data->le.ep.createEntityButton.textColor = V4(0.1f, 0.1f, 0.1f, 1.0f);
	Data->le.ep.createEntityButton.colorMouse = V4(0.85f, 0.7f, 0.95f, 0.6f);
	Data->le.ep.createEntityButton.colorNoMouse = V4(0.5f, 0.95f, 0.65f, 0.6f);
	Data->le.ep.createEntityButton.colorClick = V4(0.9f, 0.2f, 0.2f, 0.6f);
	Data->le.ep.createEntityButton.color = V4(0.5f, 0.7f, 0.95f, 0.6f);

	// DELETE ENTITY BUTTON
	Data->le.ep.deleteEntityButton = {};
	Data->le.ep.deleteEntityButton.pos.x = Data->le.ep.box.pos.x + (Data->le.ep.box.size.x * 0.05f);
	Data->le.ep.deleteEntityButton.pos.y = Data->le.ep.box.size.y - (Data->le.ep.box.size.y * 0.675f);
	Data->le.ep.deleteEntityButton.size.x = Data->le.ep.box.size.x * 0.175f;
	Data->le.ep.deleteEntityButton.size.y = Data->le.ep.box.size.x * 0.08f;
	Data->le.ep.deleteEntityButton.posMin.x = Data->le.ep.deleteEntityButton.pos.x;
	Data->le.ep.deleteEntityButton.posMin.y = Data->le.ep.deleteEntityButton.pos.y;
	Data->le.ep.deleteEntityButton.posMax.x = Data->le.ep.deleteEntityButton.pos.x + Data->le.ep.deleteEntityButton.size.x;
	Data->le.ep.deleteEntityButton.posMax.y = Data->le.ep.deleteEntityButton.pos.y + Data->le.ep.deleteEntityButton.size.y;
	Data->le.ep.deleteEntityButton.text = "DEL";
	Data->le.ep.deleteEntityButton.textPos.x = Data->le.ep.deleteEntityButton.pos.x + (Data->le.ep.deleteEntityButton.size.x * 0.075f);
	Data->le.ep.deleteEntityButton.textPos.y = Data->le.ep.deleteEntityButton.pos.y + (Data->le.ep.deleteEntityButton.size.y * 0.8f);
	Data->le.ep.deleteEntityButton.textSize = Data->le.ep.deleteEntityButton.size.y / 2;
	Data->le.ep.deleteEntityButton.textColor = V4(0.1f, 0.1f, 0.1f, 1.0f);
	Data->le.ep.deleteEntityButton.colorMouse = V4(0.85f, 0.7f, 0.95f, 0.6f);
	Data->le.ep.deleteEntityButton.colorNoMouse = V4(0.5f, 0.5f, 0.25f, 0.6f);
	Data->le.ep.deleteEntityButton.colorClick = V4(0.9f, 0.2f, 0.2f, 0.6f);
	Data->le.ep.deleteEntityButton.color = V4(0.5f, 0.7f, 0.95f, 0.6f);



	// ACTIVE ENTITY
	Data->le.ep.activeEntity = 0;
	//Data->le.ep.activeEntityList[] 


	// ACTIVE ENTITY LABEL
	Data->le.ep.activeEntityLabel = {};
	Data->le.ep.activeEntityLabel.textPos.x = Data->le.ep.box.pos.x + (Data->le.ep.box.size.x * 0.25f);
	Data->le.ep.activeEntityLabel.textPos.y = Data->le.ep.box.size.y - (Data->le.ep.box.size.y * 0.8f);
	Data->le.ep.activeEntityLabel.text = entityList[Data->le.ep.activeEntity];
	//Data->le.ep.activeEntityLabel.textPos.x = Data->le.ep.activeEntityLabel.pos.x;
	//Data->le.ep.activeEntityLabel.textPos.y = Data->le.ep.activeEntityLabel.pos.y;
	Data->le.ep.activeEntityLabel.textSize = Data->le.ep.box.size.y * 0.03f;
	Data->le.ep.activeEntityLabel.textColor = V4(0.1f, 0.1f, 0.1f, 1.0f);

	// ACTIVE ENTITY LABEL - POSITION
	char pos_x[5];
	sprintf(pos_x, "%.2f", 9.55f);

	Data->le.ep.activeEntityPosLabel = {};
	Data->le.ep.activeEntityPosLabel.textPos.x = Data->le.ep.box.pos.x + (Data->le.ep.box.size.x * 0.05f);
	Data->le.ep.activeEntityPosLabel.textPos.y = Data->le.ep.box.size.y - (Data->le.ep.box.size.y * 0.59f);
	//Data->le.ep.activeEntityPosLabel.buffer = "Pos: x";
	//strncpy(Data->le.ep.activeEntityPosLabel.buffer, pos_x, sizeof(Data->le.ep.activeEntityPosLabel.buffer);
	Data->le.ep.activeEntityPosLabel.textSize = Data->le.ep.box.size.y * 0.021f;
	Data->le.ep.activeEntityPosLabel.textColor = V4(0.1f, 0.1f, 0.1f, 1.0f);

	// ACTIVE ENTITY LABEL - ROTATION
	Data->le.ep.activeEntityRotLabel = {};
	Data->le.ep.activeEntityRotLabel.textPos.x = Data->le.ep.box.pos.x + (Data->le.ep.box.size.x * 0.05f);
	Data->le.ep.activeEntityRotLabel.textPos.y = Data->le.ep.box.size.y - (Data->le.ep.box.size.y * 0.56f);
	Data->le.ep.activeEntityRotLabel.text = "Rot: x:%.2f y:%.2f z:%.2f", 0.0f, 1.0f, 2.0f;
	Data->le.ep.activeEntityRotLabel.textSize = Data->le.ep.box.size.y * 0.021f;
	Data->le.ep.activeEntityRotLabel.textColor = V4(0.1f, 0.1f, 0.1f, 1.0f);

	// ACTIVE ENTITY LABEL - SCALE
	Data->le.ep.activeEntityScaleLabel = {};
	Data->le.ep.activeEntityScaleLabel.textPos.x = Data->le.ep.box.pos.x + (Data->le.ep.box.size.x * 0.05f);
	Data->le.ep.activeEntityScaleLabel.textPos.y = Data->le.ep.box.size.y - (Data->le.ep.box.size.y * 0.53f);
	Data->le.ep.activeEntityScaleLabel.text = "Scale: x:%.2f y:%.2f z:%.2f", 0.0f, 1.0f, 2.0f;
	Data->le.ep.activeEntityScaleLabel.textSize = Data->le.ep.box.size.y * 0.021f;
	Data->le.ep.activeEntityScaleLabel.textColor = V4(0.1f, 0.1f, 0.1f, 1.0f);
}





void LogicEntityPalatte_LE()
{
	// MOUSE COLLISSION - COLLAPSE BUTTON
	Data->le.ep.collapseButton.isMouseOver = TestPointAABB(Data->mouse.positionPixel, Data->le.ep.collapseButton.posMin, Data->le.ep.collapseButton.posMax);
	if (Data->le.ep.collapseButton.isMouseOver)
	{	// MOUSE OVER DETECTION
		Data->le.ep.collapseButton.color = Data->le.ep.collapseButton.colorMouse;
		if (InputHeld(Mouse, Input_MouseLeft))
		{	// CLICK EVENT DETECTION
			Data->le.ep.collapseButton.color = Data->le.ep.collapseButton.colorClick;
		}
		else
		{
			Data->le.ep.collapseButton.color = Data->le.ep.collapseButton.colorMouse;
		}
		if (InputPressed(Mouse, Input_MouseLeft))
		{	// CLICK EVENT DETECTION
			Data->le.ep.box.isCollapsed = !Data->le.ep.box.isCollapsed;
			Data->le.ep.collapseButton.isMouseClick = true;
		}
	}
	else
	{
		Data->le.ep.collapseButton.color = Data->le.ep.collapseButton.colorNoMouse;
	}


	if (Data->le.ep.collapseButton.isMouseClick)
	{	// MINIMIZE WINDOW
		if (Data->le.ep.box.isCollapsed)
		{
			Data->le.ep.box.size = Data->le.ep.box.sizeCollapsed;
		}
		else
		{
			Data->le.ep.box.size = Data->le.ep.box.sizeExpanded;
		}
		Data->le.ep.collapseButton.isMouseClick = false;
	}

	if (!Data->le.ep.box.isCollapsed)
	{
		// MOUSE COLLISSION - CHANGE ENTITY LEFT BUTTON
		Data->le.ep.changeEntityLeftButton.isMouseOver = TestPointAABB(Data->mouse.positionPixel, Data->le.ep.changeEntityLeftButton.posMin, Data->le.ep.changeEntityLeftButton.posMax);
		if (Data->le.ep.changeEntityLeftButton.isMouseOver)
		{	// MOUSE OVER DETECTION
			Data->le.ep.changeEntityLeftButton.color = Data->le.ep.changeEntityLeftButton.colorMouse;
			if (InputHeld(Mouse, Input_MouseLeft))
			{	// CLICK EVENT DETECTION
				Data->le.ep.changeEntityLeftButton.color = Data->le.ep.changeEntityLeftButton.colorClick;
			}
			else
			{
				Data->le.ep.changeEntityLeftButton.color = Data->le.ep.changeEntityLeftButton.colorMouse;
			}
			if (InputPressed(Mouse, Input_MouseLeft))
			{	// CLICK EVENT DETECTION
				Data->le.ep.activeEntity--;
				if (Data->le.ep.activeEntity < 0)
				{
					Data->le.ep.activeEntity = EntityType_Count-1;
				}
			}
		}
		else
		{
			Data->le.ep.changeEntityLeftButton.color = Data->le.ep.changeEntityLeftButton.colorNoMouse;
		}

		// MOUSE COLLISSION - CHANGE ENTITY RIGHT BUTTON
		Data->le.ep.changeEntityRightButton.isMouseOver = TestPointAABB(Data->mouse.positionPixel, Data->le.ep.changeEntityRightButton.posMin, Data->le.ep.changeEntityRightButton.posMax);
		if (Data->le.ep.changeEntityRightButton.isMouseOver)
		{	// MOUSE OVER DETECTION
			Data->le.ep.changeEntityRightButton.color = Data->le.ep.changeEntityRightButton.colorMouse;
			if (InputHeld(Mouse, Input_MouseLeft))
			{	// CLICK EVENT DETECTION
				Data->le.ep.changeEntityRightButton.color = Data->le.ep.changeEntityRightButton.colorClick;
			}
			else
			{
				Data->le.ep.changeEntityRightButton.color = Data->le.ep.changeEntityRightButton.colorMouse;
			}
			if (InputPressed(Mouse, Input_MouseLeft))
			{	// CLICK EVENT DETECTION
				Data->le.ep.activeEntity++;
				if (Data->le.ep.activeEntity > EntityType_Count - 1)
				{
					Data->le.ep.activeEntity = 0;
				}
			}
		}
		else
		{
			Data->le.ep.changeEntityRightButton.color = Data->le.ep.changeEntityRightButton.colorNoMouse;
		}

		// MOUSE COLLISSION - CREAE ENTITY BUTTON
		Data->le.ep.createEntityButton.isMouseOver = TestPointAABB(Data->mouse.positionPixel, Data->le.ep.createEntityButton.posMin, Data->le.ep.createEntityButton.posMax);
		if (Data->le.ep.createEntityButton.isMouseOver)
		{	// MOUSE OVER DETECTION
			Data->le.ep.createEntityButton.color = Data->le.ep.createEntityButton.colorMouse;
			if (InputHeld(Mouse, Input_MouseLeft))
			{	// CLICK EVENT DETECTION
				Data->le.ep.createEntityButton.color = Data->le.ep.createEntityButton.colorClick;
			}
			else
			{
				Data->le.ep.createEntityButton.color = Data->le.ep.createEntityButton.colorMouse;
			}
			if (InputPressed(Mouse, Input_MouseLeft))
			{	// CLICK EVENT DETECTION
				CreateEntityInLE(entityTypes[Data->le.ep.activeEntity]);
			}
		}
		else
		{
			Data->le.ep.createEntityButton.color = Data->le.ep.createEntityButton.colorNoMouse;
		}

		// MOUSE COLLISSION - DELETE ENTITY BUTTON
		Data->le.ep.deleteEntityButton.isMouseOver = TestPointAABB(Data->mouse.positionPixel, Data->le.ep.deleteEntityButton.posMin, Data->le.ep.deleteEntityButton.posMax);
		if (Data->le.ep.deleteEntityButton.isMouseOver)
		{	// MOUSE OVER DETECTION
			Data->le.ep.deleteEntityButton.color = Data->le.ep.deleteEntityButton.colorMouse;
			if (InputHeld(Mouse, Input_MouseLeft))
			{	// CLICK EVENT DETECTION
				Data->le.ep.deleteEntityButton.color = Data->le.ep.deleteEntityButton.colorClick;
			}
			else
			{
				Data->le.ep.deleteEntityButton.color = Data->le.ep.deleteEntityButton.colorMouse;
			}
			if (InputPressed(Mouse, Input_MouseLeft))
			{	// CLICK EVENT DETECTION
				// todo
			}
		}
		else
		{
			Data->le.ep.deleteEntityButton.color = Data->le.ep.deleteEntityButton.colorNoMouse;
		}

		// ENTITY LABEL CHANGE
		Data->le.ep.activeEntityLabel.text = entityList[Data->le.ep.activeEntity];


		Post* entity = (Post*)GetEntity(&Data->em, Data->le.ep.selectedEntityHandle);
		// ENTITY LABEL - POS
		//Data->le.ep.activeEntityPosLabel.text = "Pos: x:%.2f y:%.2f z:%.2f", 9.01f, entity->modelRenderData.position.y, entity->modelRenderData.position.z;
		//Data->le.ep.activeEntityPosLabel.text = "Pos: x:%f y:%.2f z:%.2f", 9.01f, 9.03f, 4.44f;
		// ENTITY LABEL - ROT
		// ENTITY LABEL - SCALE





		if (!Data->le.ep.isCollapsed)
		{

			// Cycle through entity types

				

				// image of entity

				// entity modifiers such as room number, etc.
		}
	}
}

void RenderEntityPalatte_LE()
{
	DrawRectScreen(Data->le.ep.box.pos, Data->le.ep.box.size, Data->le.ep.box.color);
	DrawTextScreenPixel(&Game->serifFont, Data->le.ep.box.textPos, Data->le.ep.box.textSize, Data->le.ep.box.textColor, false, Data->le.ep.box.text);
	DrawRectScreen(Data->le.ep.collapseButton.pos, Data->le.ep.collapseButton.size, Data->le.ep.collapseButton.color);


	if (!Data->le.ep.box.isCollapsed)
	{
		// CHANGE ENTITY - LEFT BUTTON
		DrawRectScreen(Data->le.ep.changeEntityLeftButton.pos, Data->le.ep.changeEntityLeftButton.size, Data->le.ep.changeEntityLeftButton.color);
		DrawTextScreenPixel(&Game->serifFont, Data->le.ep.changeEntityLeftButton.textPos, Data->le.ep.changeEntityLeftButton.textSize, Data->le.ep.changeEntityLeftButton.textColor, false, Data->le.ep.changeEntityLeftButton.text);

		// CHANGE ENTITY - RIGHT BUTTON
		DrawRectScreen(Data->le.ep.changeEntityRightButton.pos, Data->le.ep.changeEntityRightButton.size, Data->le.ep.changeEntityRightButton.color);
		DrawTextScreenPixel(&Game->serifFont, Data->le.ep.changeEntityRightButton.textPos, Data->le.ep.changeEntityRightButton.textSize, Data->le.ep.changeEntityRightButton.textColor, false, Data->le.ep.changeEntityRightButton.text);
		
		// CREATE ENTITY BUTTON
		DrawRectScreen(Data->le.ep.createEntityButton.pos, Data->le.ep.createEntityButton.size, Data->le.ep.createEntityButton.color);
		DrawTextScreenPixel(&Game->serifFont, Data->le.ep.createEntityButton.textPos, Data->le.ep.createEntityButton.textSize, Data->le.ep.createEntityButton.textColor, false, Data->le.ep.createEntityButton.text);

		// DELETE DELETE BUTTON
		DrawRectScreen(Data->le.ep.deleteEntityButton.pos, Data->le.ep.deleteEntityButton.size, Data->le.ep.deleteEntityButton.color);
		DrawTextScreenPixel(&Game->serifFont, Data->le.ep.deleteEntityButton.textPos, Data->le.ep.deleteEntityButton.textSize, Data->le.ep.deleteEntityButton.textColor, false, Data->le.ep.deleteEntityButton.text);

		// ACTIVE ENTITY LABEL
		DrawTextScreenPixel(&Game->serifFont, Data->le.ep.activeEntityLabel.textPos, Data->le.ep.activeEntityLabel.textSize, Data->le.ep.activeEntityLabel.textColor, false, Data->le.ep.activeEntityLabel.text);
	
		// ACTIVE ENTITY LABEL - POSITION
		real32 posX;
		real32 posY;
		real32 posZ;
		//DrawTextScreenPixel(&Game->serifFont, Data->le.ep.activeEntityPosLabel.textPos, Data->le.ep.activeEntityPosLabel.textSize, Data->le.ep.activeEntityPosLabel.textColor, false, Data->le.ep.activeEntityPosLabel.text);
		// ACTIVE ENTITY LABEL - ROTATION
		//DrawTextScreenPixel(&Game->serifFont, Data->le.ep.activeEntityRotLabel.textPos, Data->le.ep.activeEntityRotLabel.textSize, Data->le.ep.activeEntityRotLabel.textColor, false, Data->le.ep.activeEntityRotLabel.text);
		// ACTIVE ENTITY LABEL - SCALE
		//DrawTextScreenPixel(&Game->serifFont, Data->le.ep.activeEntityScaleLabel.textPos, Data->le.ep.activeEntityScaleLabel.textSize, Data->le.ep.activeEntityScaleLabel.textColor, false, Data->le.ep.activeEntityScaleLabel.text);


	}
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

	// CURRENT LEVEL BUTTON
	Data->le.lp.currentLevel = {};
	Data->le.lp.currentLevel.pos.x = Data->le.lp.box.pos.x + (Data->le.lp.box.size.x * 0.2f);
	Data->le.lp.currentLevel.pos.y = Data->le.lp.box.size.y - (Data->le.lp.box.size.y * 0.8f);
	Data->le.lp.currentLevel.size.x = Data->le.lp.box.size.x * 0.4f;
	Data->le.lp.currentLevel.size.y = Data->le.lp.box.size.y * 0.3f;
	Data->le.lp.currentLevel.posMin.x = Data->le.lp.currentLevel.pos.x;
	Data->le.lp.currentLevel.posMin.y = Data->le.lp.currentLevel.pos.y;
	Data->le.lp.currentLevel.posMax.x = Data->le.lp.currentLevel.pos.x + Data->le.lp.currentLevel.size.x;
	Data->le.lp.currentLevel.posMax.y = Data->le.lp.currentLevel.pos.y + Data->le.lp.currentLevel.size.y;
	//Data->le.lp.currentLevel.colorMouse = V4(0.1f, 1.0f, 0.1f, 0.6f);
	Data->le.lp.currentLevel.colorNoMouse = V4(0.8f, 0.8, 0.5f, 0.6f);
	Data->le.lp.currentLevel.colorClick = V4(0.8f, 0.8, 0.5f, 0.6f);
	//Data->le.lp.currentLevel.text = "CURRENT LEVEL: %d", Data->le.currentLevel;
	Data->le.lp.currentLevel.textPos.x = Data->le.lp.currentLevel.pos.x + (Data->le.lp.currentLevel.size.x * 0.05f);
	Data->le.lp.currentLevel.textPos.y = Data->le.lp.currentLevel.pos.y + (Data->le.lp.currentLevel.size.y * 0.8f);
	Data->le.lp.currentLevel.textSize = Data->le.lp.currentLevel.size.y / 2;
	Data->le.lp.currentLevel.textColor = V4(0.1f, 0.1f, 0.1f, 1.0f);
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
		SaveAndWriteLevel();
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
		Data->le.currentLevel++;
		LoadLevelParse(Data->le.currentLevel);
		Data->le.lp.loadButton.isMouseClick = false;
	}

	// CURRENT LEVEL
	//Data->le.lp.currentLevel.text = &Data->le.currentLevel;

}

void RenderLevelPalatte_LE()
{
	DrawRectScreen(Data->le.lp.box.pos, Data->le.lp.box.size, Data->le.lp.box.color);

	DrawRectScreen(Data->le.lp.saveButton.pos, Data->le.lp.saveButton.size, Data->le.lp.saveButton.color);
	DrawTextScreenPixel(&Game->serifFont, Data->le.lp.saveButton.textPos, Data->le.lp.saveButton.textSize, Data->le.lp.saveButton.textColor, false, Data->le.lp.saveButton.text);

	DrawRectScreen(Data->le.lp.loadButton.pos, Data->le.lp.loadButton.size, Data->le.lp.loadButton.color);
	DrawTextScreenPixel(&Game->serifFont, Data->le.lp.loadButton.textPos, Data->le.lp.loadButton.textSize, Data->le.lp.loadButton.textColor, false, Data->le.lp.loadButton.text);

	DrawRectScreen(Data->le.lp.currentLevel.pos, Data->le.lp.currentLevel.size, Data->le.lp.currentLevel.color);
	
	int32 level = Data->le.currentLevel;
	DrawTextScreenPixel(&Game->serifFont, Data->le.lp.currentLevel.textPos, Data->le.lp.currentLevel.textSize, Data->le.lp.currentLevel.textColor, false, "LEVEL: %d", level);

}