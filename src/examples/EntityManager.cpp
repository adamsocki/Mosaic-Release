
int32 freeList[10000];
int32 freeListCount = 0;

void* GetEntity(EntityManager* em, EntityHandle handle) 
{
	if (handle.indexInInfo >= em->entityCapacity) {
		return NULL;
	}

	EntityInfo* info = &Data->em.entities[handle.indexInInfo];

	if (info->generation != handle.generation) {
		return NULL;
	}
	if (info->type != handle.type) {
		return NULL;
	}

	EntityTypeBuffer* buffer = &em->buffers[info->type];

	return ((u8*)buffer->entities + (buffer->sizeInBytes * info->indexInBuffer));
}

void DeleteEntity(EntityManager* em, EntityHandle handle) 
{
	freeList[freeListCount] = handle.indexInInfo;
	freeListCount++;

	EntityTypeBuffer* buffer = &em->buffers[handle.type];
	EntityInfo* info = &em->entities[handle.indexInInfo];
	EntityHandle handleOfSwappedEntity;

	buffer->count--;
}

EntityHandle AddEntity(EntityManager* em, EntityType type) 
{
	int32 nextFreeIdInIndex = em->nextID;

	if (freeListCount > 0) {
		nextFreeIdInIndex = freeList[freeListCount - 1];
		freeListCount--;
	}
	else {
		em->nextID++;
	}

	EntityInfo* info = &em->entities[nextFreeIdInIndex];
	info->type = type;
	info->generation++;

	EntityTypeBuffer* buffer = &em->buffers[type];
	info->indexInBuffer = buffer->count;
	buffer->count++;

	EntityHandle handle = {};
	handle.generation = info->generation;
	handle.indexInInfo = nextFreeIdInIndex;
	handle.type = type;

	return handle;
}

void InitializeEntityManager() 
{	// Entity Manager
	Data->em.entityCapacity = 6000;
	Data->em.entities = (EntityInfo*)malloc(sizeof(EntityInfo) * Data->em.entityCapacity);
	memset(Data->em.entities, 0, sizeof(EntityInfo) * Data->em.entityCapacity);
	Data->em.nextID = 0;


	Data->em.entityTypes[0] = EntityType_Terrain;
	Data->em.entityTypes[1] = EntityType_Test;
	Data->em.entityTypes[2] = EntityType_Fern;
	Data->em.entityTypes[3] = EntityType_Wall;

	// Data->em.entityNames[0] = EntityType_Terrain;
	// Data->em.entityNames[1] = EntityType_Test;
	// Data->em.entityNames[2] = EntityType_Fern;
	// Data->em.entityNames[3] = EntityType_GUI;
}

void InitializeEntityBuffers()
{
	EntityTypeBuffer* terrainBuffer = &Data->em.buffers[EntityType_Terrain];
	terrainBuffer->capacity = 8000;
	terrainBuffer->sizeInBytes = sizeof(Terrain);
	terrainBuffer->count = 0;
	terrainBuffer->entities = (Terrain*)malloc(terrainBuffer->capacity * terrainBuffer->sizeInBytes);
	memset(terrainBuffer->entities, 0, sizeof(Terrain) * terrainBuffer->capacity);
	
	EntityTypeBuffer* testStallBuffer = &Data->em.buffers[EntityType_Test];
	testStallBuffer->capacity = 8000;
	testStallBuffer->sizeInBytes = sizeof(TestStall);
	testStallBuffer->count = 0;
	testStallBuffer->entities = (TestStall*)malloc(testStallBuffer->capacity * testStallBuffer->sizeInBytes);
	memset(testStallBuffer->entities, 0, sizeof(TestStall) * testStallBuffer->capacity);

	EntityTypeBuffer* fernBuffer = &Data->em.buffers[EntityType_Fern];
	fernBuffer->capacity = 8000;
	fernBuffer->sizeInBytes = sizeof(Fern);
	fernBuffer->count = 0;
	fernBuffer->entities = (Fern*)malloc(fernBuffer->capacity * fernBuffer->sizeInBytes);
	memset(fernBuffer->entities, 0, sizeof(Fern) * fernBuffer->capacity);
	
	EntityTypeBuffer* guiBuffer = &Data->em.buffers[EntityType_GUI];
	guiBuffer->capacity = 8000;
	guiBuffer->sizeInBytes = sizeof(GUI);
	guiBuffer->count = 0;
	guiBuffer->entities = (GUI*)malloc(guiBuffer->capacity * guiBuffer->sizeInBytes);
	memset(guiBuffer->entities, 0, sizeof(GUI) * guiBuffer->capacity);
	
	EntityTypeBuffer* wallBuffer = &Data->em.buffers[EntityType_Wall];
	wallBuffer->capacity = 8000;
	wallBuffer->sizeInBytes = sizeof(Wall);
	wallBuffer->count = 0;
	wallBuffer->entities = (Wall*)malloc(wallBuffer->capacity * wallBuffer->sizeInBytes);
	memset(wallBuffer->entities, 0, sizeof(Wall) * wallBuffer->capacity);

	EntityTypeBuffer* postBuffer = &Data->em.buffers[EntityType_Post];
	postBuffer->capacity = 8000;
	postBuffer->sizeInBytes = sizeof(Post);
	postBuffer->count = 0;
	postBuffer->entities = (Post*)malloc(postBuffer->capacity * postBuffer->sizeInBytes);
	memset(postBuffer->entities, 0, sizeof(Post) * postBuffer->capacity);


	EntityTypeBuffer* playerBuffer = &Data->em.buffers[EntityType_Player];
	playerBuffer->capacity = 1;
	playerBuffer->sizeInBytes = sizeof(Player);
	playerBuffer->count = 0;
	playerBuffer->entities = (Player*)malloc(playerBuffer->capacity * playerBuffer->sizeInBytes);
	memset(playerBuffer->entities, 0, sizeof(Player) * playerBuffer->capacity);

}

void InitializeStartingEntities()
{
	// TERRAIN
	EntityHandle terrainHandle = AddEntity(&Data->em, EntityType_Terrain);
	Terrain* terrainEntity = (Terrain*)GetEntity(&Data->em, terrainHandle);
	terrainEntity->handle = terrainHandle;
	terrainEntity->modelRenderData.position = V3(-8.0f, -0.0f, 0.0f);
	terrainEntity->modelRenderData.scale = V3(1.0f, 1.0f, 1.0f);
	terrainEntity->mesh = Game->terrain;
	terrainEntity->model = Data->rm.models.terrainModel;

	// PLAYER
	EntityHandle playerHandle = AddEntity(&Data->em, EntityType_Player);
	Player* playerEntity = (Player*)GetEntity(&Data->em, playerHandle);
	playerEntity->handle = playerHandle;
	playerEntity->modelRenderData.position = V3(-0.0f, -0.0f, 0.0f);
	playerEntity->modelRenderData.scale = V3(3.0f, 3.0f, 3.0f);
	playerEntity->modelRenderData.modifiedLighting = true;
	playerEntity->runSpeed = 20.0f;
	playerEntity->turnSpeed = 160.0f;
	playerEntity->currentSpeed = 0.0f;
	playerEntity->gravity = -50.0f;
	playerEntity->upwardSpeed = 0.0f;	
	playerEntity->jumpPower = 30.0f;
	playerEntity->isInAir = false;
	playerEntity->model = Data->rm.models.playerModel;

	// TEST
	for (int i = 0; i < 5; i++)
	{
		EntityHandle testStallHandle = AddEntity(&Data->em, EntityType_Test);
		TestStall* testStallEntity = (TestStall*)GetEntity(&Data->em, testStallHandle);
		testStallEntity->handle = testStallHandle;
		testStallEntity->modelRenderData.position = V3(-0.0f, (i * 3.0f) * 10.0f, i* 10.0f);
		testStallEntity->modelRenderData.scale = V3(10.0f, 10.0f, 10.0f);
		testStallEntity->model = Data->rm.models.testStallModel;
	}

	for (int i = 0; i < 40; i++)
	{
		EntityHandle fernHandle = AddEntity(&Data->em, EntityType_Fern);
		Fern* fernEntity = (Fern*)GetEntity(&Data->em, fernHandle);
		fernEntity->handle = fernHandle;
		fernEntity->modelRenderData.position = V3(RandfRange(0, 40) * 1.0f, 0.0f, RandfRange(0, 100));
		fernEntity->modelRenderData.scale = V3(10.0f, 10.0f, 10.0f);
		fernEntity->model = Data->rm.models.testStallModel;
	}


	for (int i = 0; i < 40; i++)
	{
		EntityHandle wallHandle = AddEntity(&Data->em, EntityType_Wall);
		Wall* wallEntity = (Wall*)GetEntity(&Data->em, wallHandle);
		wallEntity->handle = wallHandle;
		//fernEntity->modelRenderData.position = V3(RandfRange(0, 40) * 1.0f, 0.0f, RandfRange(0, 100));
		//fernEntity->modelRenderData.scale = V3(10.0f, 10.0f, 10.0f);
		wallEntity->model = Data->rm.models.wall1Model;
	}

	for (int i = 0; i < 40; i++)
	{
		EntityHandle postHandle = AddEntity(&Data->em, EntityType_Post);
		Post* postEntity = (Post*)GetEntity(&Data->em, postHandle);
		postEntity->handle = postHandle;
		postEntity->modelRenderData.position = V3(RandfRange(0, 40) * 1.0f, 0.0f, RandfRange(0, 100));
		postEntity->modelRenderData.scale = V3(3.0f, 3.0f, 3.0f);
		//postEntity->model = Data->rm.models.postModel;
	}
}

// LEVEL EDITOR 
//void CreateEntityPalatte_LE()
//{
//	// PALLATE BACKGROUND
//	Data->le.ep.box.pos.x = Game->screenWidth * 0.025f;
//	Data->le.ep.box.pos.y = Game->screenHeight * 0.05f;
//	Data->le.ep.box.size.x = Game->screenWidth * 0.25f;
//	Data->le.ep.box.size.y = Game->screenHeight - (Game->screenHeight * 0.05f * 2);
//	Data->le.ep.box.color = V4(0.5f, 0.8f, 0.8f, 0.5f);
//	Data->le.ep.box.isCollapsed = false;
//	Data->le.ep.box.sizeExpanded.x = Game->screenWidth * 0.25f;
//	Data->le.ep.box.sizeExpanded.y = Game->screenHeight - (Game->screenHeight * 0.05f * 2);
//	Data->le.ep.box.sizeCollapsed.x = Data->le.ep.box.size.x;
//	Data->le.ep.box.sizeCollapsed.y = Data->le.ep.box.pos.y - (Data->le.ep.box.size.x * 0.05f) + (Data->le.ep.box.size.x * 0.07f / 3);
//	Data->le.ep.box.text = "Entity Editor"; 
//	Data->le.ep.box.textPos.x = Data->le.ep.box.pos.x + (Data->le.ep.box.size.x * 0.05f);
//	Data->le.ep.box.textPos.y = Data->le.ep.box.pos.y + (Data->le.ep.box.size.y * 0.035f);
//	Data->le.ep.box.textSize = Data->le.ep.box.sizeCollapsed.y / 2;
//	Data->le.ep.box.textColor = V4(0.1f, 0.1f, 0.1f, 1.0f);
//
//	// BUTTONS - ADD BUTONS TO PALLATE BACKGROUND
//		// sizes are conditional on PALLATE BACKGROUND size
//	// COLLAPSE WINDOW BUTTON		
//	Data->le.ep.collapseButton = {};
//	Data->le.ep.collapseButton.size.x = Data->le.ep.box.size.x * 0.05f;
//	Data->le.ep.collapseButton.size.y = Data->le.ep.box.size.x * 0.05f;
//	Data->le.ep.collapseButton.pos.x = Data->le.ep.box.pos.x + (Data->le.ep.box.size.x * 0.93f);
//	Data->le.ep.collapseButton.pos.y = Data->le.ep.box.pos.y + (Data->le.ep.box.size.x * 0.07f) - Data->le.ep.collapseButton.size.y;
//	Data->le.ep.collapseButton.posMin.x = Data->le.ep.collapseButton.pos.x;
//	Data->le.ep.collapseButton.posMin.y = Data->le.ep.collapseButton.pos.y;
//	Data->le.ep.collapseButton.posMax.x = Data->le.ep.collapseButton.pos.x + Data->le.ep.collapseButton.size.x;
//	Data->le.ep.collapseButton.posMax.y = Data->le.ep.collapseButton.pos.y + Data->le.ep.collapseButton.size.y;
//	Data->le.ep.collapseButton.colorMouse   = V4(0.85f, 0.95f, 0.95f, 0.6f);
//	Data->le.ep.collapseButton.colorNoMouse = V4(0.6f, 0.7f, 0.7f, 0.6f);
//	Data->le.ep.collapseButton.colorClick   = V4(1.0f, 1.0, 1.0f, 0.6f);
//}
//
//void LogicEntityPalatte_LE()
//{
//	// MOUSE COLLISSION
//	Data->le.ep.collapseButton.isMouseOver = TestPointAABB(Data->mouse.positionPixel, Data->le.ep.collapseButton.posMin, Data->le.ep.collapseButton.posMax);
//	if (Data->le.ep.collapseButton.isMouseOver)
//	{	// MOUSE OVER DETECTION
//		Data->le.ep.collapseButton.color = Data->le.ep.collapseButton.colorMouse;
//		if (InputHeld(Mouse, Input_MouseLeft))
//		{	// CLICK EVENT DETECTION
//			Data->le.ep.collapseButton.color = Data->le.ep.collapseButton.colorClick;
//		}
//		else
//		{
//			Data->le.ep.collapseButton.color = Data->le.ep.collapseButton.colorMouse;
//		}
//		if (InputPressed(Mouse, Input_MouseLeft))
//		{	// CLICK EVENT DETECTION
//			Data->le.ep.box.isCollapsed = !Data->le.ep.box.isCollapsed;
//			Data->le.ep.collapseButton.isMouseClick = true;
//		}
//	}
//	else
//	{
//		Data->le.ep.collapseButton.color = Data->le.ep.collapseButton.colorNoMouse;
//	}
//
//	if (Data->le.ep.collapseButton.isMouseClick)
//	{	// TODO - CLICK EVENT TRIGGER
//		if (Data->le.ep.box.isCollapsed)
//		{
//			Data->le.ep.box.size = Data->le.ep.box.sizeCollapsed;
//		}
//		else
//		{
//			Data->le.ep.box.size = Data->le.ep.box.sizeExpanded;
//		}
//		Data->le.ep.collapseButton.isMouseClick = false;
//	}
//}
//
//void RenderEntityPalatte_LE()
//{
//	DrawRectScreen(Data->le.ep.box.pos, Data->le.ep.box.size, Data->le.ep.box.color);
//	DrawTextScreenPixel(&Game->serifFont, Data->le.ep.box.textPos, Data->le.ep.box.textSize, Data->le.ep.box.textColor, false, Data->le.ep.box.text);
//	DrawRectScreen(Data->le.ep.collapseButton.pos, Data->le.ep.collapseButton.size, Data->le.ep.collapseButton.color);
//
//}
