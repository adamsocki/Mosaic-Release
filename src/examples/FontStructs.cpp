

struct Character 
{
	int32 id;
	real32 xTextureCoord;
	real32 yTextureCoord;
	real32 xMaxTextureCoord;
	real32 yMaxTextureCoord;
	real32 xOffset;
	real32 yOffset;
	real32 sizeX;
	real32 sizeY;
	real32 xAdvance;
};

struct Word
{
	Character* characters;
	int32 characterCapacity;
	int32 characterCount;

	real32 width;
	real32 fontSize;
};

struct FontType
{
	int32 textureAtlas;
};

struct GUIText
{
	const char* textString;
	real32 fontSize;

	int32 textMeshVao;
	int32 vertexCount;
	vec3 color;

	vec2 position;
	real32 lineMaxSize;
	int32 numOfLines;

		
	FontType font;

	bool centerText;
};