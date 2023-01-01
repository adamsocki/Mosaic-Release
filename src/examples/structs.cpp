enum EntityType
{
	EntityType_Terrain,
	
	EntityType_Count,
};

struct Model
{
	OBJMesh mesh;

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

    Sprite sprite;
    Sprite sprite2;

    SoundClip sound;
};







struct Entity
{
	Model model;
	EntityHandle handle;
};





struct Terrain : Entity
{

};
