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

enum EngineMode
{
	GameMode,
	LevelEditorMode,
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
	Sprite stallTexture;
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

	Sprite sprite;

	real32 shineDamper; // TODO ADD THIS
	real32 reflectivity; // TODO ADD THIS
	
	vec3 position;
	vec3 scale;
	real32 rotY;

	vec4 color;

	bool isMouseOver;
	bool isSelected;

	vec4 aabbColor;
	vec3 aabb_min;
	vec3 aabbSize;
};

struct Light
{
	vec3 position;
	vec3 color;
};

struct EntityMesh
{
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

	vec2 positionPixel;
	vec2 positionPixel_prev;
	vec2 positionPixel_delta;
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

	EngineMode engineMode;

    Sprite sprite;
    Sprite sprite2;
};

enum EditorMode
{
	fixed_Mode,

	xPos_Mode,
	yPos_Mode,
	zPos_Mode,
};

struct Entity
{
	Model model;
	EntityHandle handle;

	vec3 position;
	ModelRenderData modelRenderData;

	bool isMouseOver;
	bool isSelected;
	EditorMode editorMode;


	Rect boundingBox;

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

enum TokenTypeForLevel
{
	TokenType_LeftParen,
	TokenType_RightParen,
	TokenType_AmpSymb,
	TokenType_PoundSymb,
	TokenType_Comma,

	TokenType_Integer,
	TokenType_PeriodSymb,
	TokenType_Identifier,
	TokenType_DollarSymb,
	TokenType_Count,
};

struct CameraTarget
{
	vec3 pos;
	real32 speed;
};

struct TokenVal
{
	TokenTypeForLevel type;
	char* start;
	int32 length;
};

struct Box
{
	vec2 size;
	vec2 pos;
	vec4 color;	
	
	bool isOpen;
};



struct Button : Box
{
	const char* text;
	vec2 textPos;
	real32 textSize;
	vec4 textColor;

	bool isMouseOver;
	vec4 colorMouse;
	vec4 colorNoMouse;
	vec4 colorClick;

	bool isMouseClick;
	vec2 posMin;
	vec2 posMax;
};

struct PalatteBackground : Box
{
	const char* text; 
	vec2 textPos;
	real32 textSize;
	vec4 textColor;
};

struct PalatteBackgroundEntity : PalatteBackground
{
	bool isCollapsed;

	vec2 sizeCollapsed;
	vec2 sizeExpanded;
};

struct LevelPalatte
{
	PalatteBackground box;
	Button saveButton;
	Button loadButton;
};

struct EntityPalatte
{
	PalatteBackgroundEntity box;
	Button collapseButton;
};


struct LevelEditor
{
	LevelPalatte lp;
	EntityPalatte ep;

	int32 currentLevel;
};

struct MyData_LE : MyData
{
	LevelEditor le;
};