
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

    real32* normals;

    int32 indexCount;
    int32* indices;

    int32 texcoordsCount;
    real32* texcoords;
    uint32 texcoordsSize;

    int32 vertBufferID;
    int32 indexBufferID;
    int32 texturesBufferID;


    int32 vaoID;

    int32 facesCount; // TODO ADD THIS TO PARSER
};

// @TODO: material, submesh which knows the start and end indices
