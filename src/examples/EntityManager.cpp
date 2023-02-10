
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

	EntityTypeBuffer* doorBuffer = &Data->em.buffers[EntityType_Door];
	doorBuffer->capacity = 1;
	doorBuffer->sizeInBytes = sizeof(Door);
	doorBuffer->count = 0;
	doorBuffer->entities = (Door*)malloc(doorBuffer->capacity * doorBuffer->sizeInBytes);
	memset(doorBuffer->entities, 0, sizeof(Door) * doorBuffer->capacity);

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
	playerEntity->modelRenderData.rotation = IdentityQuaternion();
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
		testStallEntity->modelRenderData.rotation = IdentityQuaternion();
		testStallEntity->model = Data->rm.models.testStallModel;
	}

	for (int i = 0; i < 40; i++)
	{
		EntityHandle fernHandle = AddEntity(&Data->em, EntityType_Fern);
		Fern* fernEntity = (Fern*)GetEntity(&Data->em, fernHandle);
		fernEntity->handle = fernHandle;
		fernEntity->modelRenderData.position = V3(RandfRange(0, 40) * 1.0f, 0.0f, RandfRange(0, 100));
		fernEntity->modelRenderData.scale = V3(10.0f, 10.0f, 10.0f);
		fernEntity->modelRenderData.rotation = IdentityQuaternion();
		fernEntity->model = Data->rm.models.testStallModel;
	}


	for (int i = 0; i < 1; i++)
	{
		EntityHandle wallHandle = AddEntity(&Data->em, EntityType_Wall);
		Wall* wallEntity = (Wall*)GetEntity(&Data->em, wallHandle);
		wallEntity->handle = wallHandle;
		wallEntity->modelRenderData.position = V3(-10, 0, -50);
		wallEntity->modelRenderData.scale = V3(5, 20, 100);
		wallEntity->modelRenderData.rotation = IdentityQuaternion();
		wallEntity->model = Data->rm.models.wall1Model;
		wallEntity->mesh = Game->wall1Mesh;
		wallEntity->editorMode = fixed_EditorMode;
		wallEntity->modelRenderData.isSelected = false;
		wallEntity->modelRenderData.isMouseOver = false;
		wallEntity->modelRenderData.sprite = Data->sprites.wall1Texture;


	}

	for (int i = 0; i < 40; i++)
	{
		EntityHandle postHandle = AddEntity(&Data->em, EntityType_Post);
		Post* postEntity = (Post*)GetEntity(&Data->em, postHandle);
		postEntity->handle = postHandle;
		postEntity->modelRenderData.position = V3(RandfRange(0, 40) * 1.0f, 0.0f, RandfRange(0, 100));
		postEntity->modelRenderData.scale = V3(3.0f, 3.0f, 3.0f);
		postEntity->modelRenderData.rotation = IdentityQuaternion();
		postEntity->isMouseOver = false;
		postEntity->mesh = Game->postMesh;
		postEntity->modelRenderData.isSelected = false;
		postEntity->modelRenderData.isMouseOver = false;
		postEntity->editorMode = fixed_EditorMode;
		postEntity->modelRenderData.sprite = Data->sprites.wall1Texture;
	}
}


