enum EntityType
{
	EntityType_Terrain,
	EntityType_Test,
	
	EntityType_Count,
};

struct Model
{
	OBJMesh mesh;

};

struct Models
{
	Model testStallModel;

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

struct RenderManager
{
	Models models;
};

struct TransformMatrixModelData
{
	vec3 position;
	vec3 scale;
	real32 angle;
	vec4 color;
};


struct Light
{
	vec3 position;
	vec3 color;
};


struct MyData {
    
    GameSprites sprites;

    EntityManager em;

	RenderManager rm;

	Light sunLight;
		

    Sprite sprite;
    Sprite sprite2;
	
  
};





struct Entity
{
	Model model;
	EntityHandle handle;

	vec3 position;
	TransformMatrixModelData transform;
};





struct Terrain : Entity
{

};


struct TestStall : Entity
{

};