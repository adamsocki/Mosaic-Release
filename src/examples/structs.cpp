enum EntityType
{
	EntityType_Terrain,
	EntityType_Test,
	EntityType_Fern,
	EntityType_GUI,
	EntityType_Post,
	EntityType_Wall,
	EntityType_Player,

	EntityType_Count,
};

typedef enum LodePNGColorType {
  LCT_GREY = 0, /*grayscale: 1,2,4,8,16 bit*/
  LCT_RGB = 2, /*RGB: 8,16 bit*/
  LCT_PALETTE = 3, /*palette: 1,2,4,8 bit*/
  LCT_GREY_ALPHA = 4, /*grayscale with alpha: 8,16 bit*/
  LCT_RGBA = 6, /*RGB with alpha: 8,16 bit*/
  /*LCT_MAX_OCTET_VALUE lets the compiler allow this enum to represent any invalid
  byte value from 0 to 255 that could be present in an invalid PNG file header. Do
  not use, compare with or set the name LCT_MAX_OCTET_VALUE, instead either use
  the valid color type names above, or numeric values like 1 or 7 when checking for
  particular disallowed color type byte values, or cast to integer to print it.*/
  LCT_MAX_OCTET_VALUE = 255
} LodePNGColorType;

struct Model
{
	OBJMesh mesh;

};

struct Models
{
	Model testStallModel;

	Model terrainModel;
	Model wall1Model;
	Model playerModel;
};


struct GameSprites
{
    Sprite testSprite;
	Sprite fernTexture;
	Sprite cursor_red;
	Sprite newPlus;
	Sprite newPlusSel;
	Sprite wall1Texture;
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
	vec4 skyColor;
	Models models;
};

struct ModelRenderData
{
	bool hasTransparency;
	bool modifiedLighting;
	
	vec3 position;
	vec3 scale;
	real32 rotY;

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
	OBJMesh wall1Mesh;
	OBJMesh postMesh;
	OBJMesh playerMesh;

};



struct MouseData
{
	Rect rect;

	vec2 posOnWindow;
	vec3 posOnWindow_prev;

	vec2 positionFromInput;
};



struct CameraManager
{

};




struct MyData {

	EntityMesh meshes;
    
    GameSprites sprites;

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

	bool mouseOver;

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

struct Player :Entity
{
	real32 runSpeed;
	real32 turnSpeed;
	real32 currentSpeed;
	real32 currentTurnSpeed;
};

struct Wall : Entity
{

};
struct Post : Entity
{

};

struct GUI_Sub1 : Entity
{
	
};



struct GUI_Transform : GUI_Sub1
{

};

struct GUI_Scale: GUI_Sub1
{

};

struct GUI_New : GUI_Sub1
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

	//GUI_Transform transformSub1;
	bool hasTransform;
	bool hasScale;

	int32 subElements1_Count;

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



