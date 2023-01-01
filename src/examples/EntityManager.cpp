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
}


void InitializeEntityBuffers()
{
	EntityTypeBuffer* terrainBuffer = &Data->em.buffers[EntityType_Terrain];
	terrainBuffer->capacity = 8000;
	terrainBuffer->sizeInBytes = sizeof(Terrain);
	terrainBuffer->count = 0;
	terrainBuffer->entities = (Terrain*)malloc(terrainBuffer->capacity * terrainBuffer->sizeInBytes);
	memset(terrainBuffer->entities, 0, sizeof(Terrain) * terrainBuffer->capacity);
	
}




void InitializeStartingEntities()
{
	
	EntityHandle terrainHandle = AddEntity(&Data->em, EntityType_Terrain);
	Terrain* terrainEntity = (Terrain*)GetEntity(&Data->em, terrainHandle);
	terrainEntity->handle = terrainHandle;
	terrainEntity->position = V3(-0.0f, -0.0f, 0.0f);
	terrainEntity->model = Data->models.terrainModel;
}