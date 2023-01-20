



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

	// BOX - TRANSPARENT TOP RIGHT
	Data->le.lp.box.size = V2(Game->screenWidth - (Game->screenWidth * 0.75f), Game->screenHeight * 0.10f);
	Data->le.lp.box.pos = V2(Game->screenWidth - (Game->screenWidth * 0.25f), Game->screenHeight * 0.10f);
	Data->le.lp.box.color = V4(0.5f, 0.4f, 0.8f, 0.5f);
	// TODO - ADD BUTONS TO BOX
	Data->le.lp.saveButton = {};
	Data->le.lp.saveButton.size = V2(Data->le.lp.box.size.x * 0.275f, Data->le.lp.box.size.y * 0.33f);
	Data->le.lp.saveButton.pos = V2(Game->screenWidth - (Data->le.lp.box.size.x * 0.33f), Data->le.lp.box.size.y - (Data->le.lp.box.size.y * 0.2f));
	Data->le.lp.saveButton.color = V4(1.0f, 1.0f, 1.0f, 0.6f);
	Data->le.lp.saveButton.text = "SAVE";


}