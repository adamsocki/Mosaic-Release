
struct Mesh {
    uint32 size;
    void *data;
    
    uint32 vertCount;
    vec3 *verts;
    vec3 *normals;

    uint32 indexCount;
    uint32 *indices;

    uint32 texcoordsCount;
    vec2 *texcoords;

    int32 vertBufferID;
    int32 indexBufferID;
};

struct QuadMesh
{
    int32 vertCount;
    real32* verts;

    int32 texcoordsCount;
    real32* texcoords;

    int32 vaoID;
    int32 vertBufferID;
};


struct OBJMesh
{
    uint32 size;
    void* data;

    int32 vertCount;
    real32* verts;

    uint32 vertSize;

    int32 normalsCount;
    real32* normals;
    real32* normals2;

    int32 indexCount;
    int32* indices;

    int32 texcoordsCount;
    real32* texcoords;
    real32* texcoords2;
    uint32 texcoordsSize;

    int32 vertBufferID;
    int32 indexBufferID;
    int32 texturesBufferID;

    real32 furthestPoint;

    bool hasTransparency;
    bool modifiedLighting;

    int32 vaoID;

    real32** terrainHeight;
    int32 rowCount_Terrain;
    int32 columnCount_Terrain;

    int32 VERTEX_COUNT;
    int32 SIZE;

    vec3 currentTerrainPointOnMouse;

    real32 terrainWidth;

    vec3 maxAABB;
    vec3 minAABB;
    

    int32 facesCount; // TODO ADD THIS TO PARSER
};

// @TODO: material, submesh which knows the start and end indices
