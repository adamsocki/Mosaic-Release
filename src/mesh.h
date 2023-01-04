
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

    int32 facesCount; // TODO ADD THIS TO PARSER
};

// @TODO: material, submesh which knows the start and end indices
