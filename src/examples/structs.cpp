enum EntityType
{
	EntityType_Terrain,
	
	EntityType_Count,
};

struct Model
{
	OBJMesh mesh;

};

struct Models
{
	Model terrainModel;
};


struct GameSprites
{
    Sprite testSprite;
};

struct EntityHandle {
	int32 generation;
	int32 indexInInfo;
	EntityType type;
};


struct EntityInfo {
	int32 generation;
	int32 indexInBuffer;

	EntityType type;
};

struct EntityTypeBuffer {
	int32 count;
	int32 capacity;
	int32 sizeInBytes;

	void* entities;
};


struct EntityManager {
	EntityTypeBuffer buffers[EntityType_Count];
	EntityInfo* entities;
	int32 entityCapacity;

	int32 nextID;
};

struct MyData {
    
    GameSprites sprites;

    EntityManager em;
	
	Models models;

    Sprite sprite;
    Sprite sprite2;
	
  
};







struct Entity
{
	Model model;
	EntityHandle handle;

	vec3 position;
};





struct Terrain : Entity
{

};
