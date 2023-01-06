enum EntityType
{
	EntityType_Terrain,
	EntityType_Test,
	EntityType_Fern,
	EntityType_GUI,

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
	Sprite fernTexture;
	Sprite cursor_red;

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

	EntityType entityTypes[EntityType_Count]; 
};

struct RenderManager
{
	Models models;
};

struct ModelRenderData
{
	bool hasTransparency;
	bool modifiedLighting;
	
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

struct EntityMesh
{
	Mesh quadMesh;
	OBJMesh stallMesh;
	OBJMesh fernMesh;

};


// struct GUI_BoxInfo
// {
	
// 	const char *fmt;
// 	bool isSub;
// };

// struct GUI_Box
// {
// 	vec2 position;
// 	vec2 size;

// 	vec4 color;
// 	vec4 colorSelect;

// 	Sprite sprite;
// 	FontTable *font; 
// 	vec2 textPosition; 
// 	real32 textSize;
// 	vec4 textColor;
// 	bool textCenter;
// 	const char *fmt;

// 	bool mouseOver;
// 	bool expanded;
// 	bool isSub;

// 	int32 displayOrder;

// 	int32 parentID;

// 	void* elements{ NULL };
// 	int32 elementCount;
// 	int32 elementCapacity;

// 	Rect guiRect = {size};
// };

// struct GUI_Box1 : GUI_Box
// {
	
// };

// GUI
// struct GUI
// {
// 	GUI_Box1* entityPalatteGUI;
// 	GUI_Box1 subPalatteGUI1;
	
	

// 	int32 guiCount;
// };

struct MouseData
{
	Rect rect;
	vec2 positionFromInput;
};




struct MyData {

	EntityMesh meshes;
    
    GameSprites sprites;

	//GUI guis;

    EntityManager em;

	RenderManager rm;

	Light sunLight;
		
	MouseData mouse;

    Sprite sprite;
    Sprite sprite2;
};





struct Entity
{
	Model model;
	EntityHandle handle;

	vec3 position;
	ModelRenderData modelRenderData;
};





struct Terrain : Entity
{

};


struct TestStall : Entity
{

};

struct Fern :Entity
{

};

struct GUI : Entity
{
	const char *label;
	bool isParent;
	EntityHandle parentHandle;
	EntityHandle handleForGUIEntity;
	vec3 entityPosition;
	vec2 position2D;
	vec2 size2D;
	vec4 color;
	vec4 colorSelect;
	EntityType entityType;
	int32 entityTypeID;

	bool mouseOver;
};


struct VertexDuplicate
{
	vec3 position;
	int32 textureIndex{ -1 };
	int32 normalIndex{ -1 };

	int32 index;
	real32 length;

	bool isSet;

};


struct Vertex
{
	vec3 position;
	int32 textureIndex{ -1 };
	int32 normalIndex{ -1 };

	int32 index;
	real32 length;

	bool hasDuplicate;
	void* duplicateVertex{ NULL };

	bool isSet;

};



