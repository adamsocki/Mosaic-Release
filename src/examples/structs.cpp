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

	int32 numberOfTextureRows;
	int32 textureIndex;

	real32 shineDamper; // TODO ADD THIS
	real32 reflectivity; // TODO ADD THIS
	
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
	vec2 positionFromInput_prev;
	vec2 positionFromInput_delta;
};

struct MousePicker
{
	MouseData mouseData;
	
	vec3 mouseRay;
	mat4 projectionMatrix;
	mat4 viewMatrix;
	Camera* cam;
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
	MousePicker mousePicker;

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

	OBJMesh mesh;

	real32 gravity;
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
	real32 jumpPower;
	real32 upwardSpeed;
	bool isInAir;

	bool isWalkingForwardOrBackward;
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



//	LEVEL EDITOR STRUCTS

struct Box
{
	vec2 size;
	vec2 pos;
	vec4 color;
};

struct Button : Box
{
	const char* text;
	bool isMouseOver;
	vec4 colorMouse;
};

struct Palatte : Box
{
	const char* text;
};

struct LevelPalatte
{
	Palatte box;
	Button saveButton;
};

struct EntityPalatte
{
	Palatte box;

};


struct LevelEditor
{
	LevelPalatte lp;
	EntityPalatte ep;
};

struct MyData_LE : MyData
{
	LevelEditor le;
};