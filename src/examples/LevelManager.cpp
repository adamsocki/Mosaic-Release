



void InitializeLevelFromCode()
{

	// create walls
	EntityTypeBuffer* wallBuffer = &Data->em.buffers[EntityType_Wall];
	Wall* wallEntitiesInBuffer = (Wall*)wallBuffer->entities;

	Wall* wallEntity = (Wall*)GetEntity(&Data->em, wallEntitiesInBuffer[0].handle);

	wallEntity->modelRenderData.position = V3(0, 0, -50);
	wallEntity->modelRenderData.scale = V3(5, 20, 100);




}