


void GenerateTerrain(char *pathForHeightMap)
{
	OBJMesh* terrainMesh = &Game->terrain;

	int32 VERTEX_COUNT = 100;
	real32 SIZE = 3000;
	int32 count = VERTEX_COUNT * VERTEX_COUNT;

	terrainMesh->vertCount = count * 3;
	terrainMesh->normalsCount = count * 3;
	terrainMesh->texcoordsCount = count * 2;
	terrainMesh->indexCount = 6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1);

	terrainMesh->data = (void*)malloc((sizeof(real32) * terrainMesh->vertCount) + (sizeof(real32) * terrainMesh->texcoordsCount) + (sizeof(real32) * terrainMesh->normalsCount));
	terrainMesh->size = (sizeof(real32) * terrainMesh->vertCount) + (sizeof(real32) * terrainMesh->texcoordsCount) + (sizeof(real32) * terrainMesh->normalsCount);

	terrainMesh->verts = (real32*)malloc(sizeof(real32) * terrainMesh->vertCount);
	terrainMesh->verts = (real32*)terrainMesh->data;

	terrainMesh->texcoords = (real32*)malloc(sizeof(real32) * terrainMesh->texcoordsCount);
	terrainMesh->texcoords = (real32*)((uint8*)terrainMesh->data + (sizeof(real32) * terrainMesh->vertCount));

	terrainMesh->normals = (real32*)malloc(sizeof(real32) * terrainMesh->normalsCount);
	terrainMesh->normals = (real32*)((uint8*)terrainMesh->data + (sizeof(real32) * terrainMesh->vertCount) + (sizeof(real32) * terrainMesh->texcoordsCount));

	terrainMesh->indices= (int32*)malloc(sizeof(int32) * terrainMesh->indexCount);

	int32 vertexPointer = 0;
	for (int i = 0; i < VERTEX_COUNT; i++) {
		for (int j = 0; j < VERTEX_COUNT; j++) {
			terrainMesh->verts[vertexPointer * 3] = (real32)(j / ((real32)VERTEX_COUNT - 1) * SIZE);
			terrainMesh->verts[vertexPointer * 3 + 1] = RandfRange(-20,20);
			terrainMesh->verts[vertexPointer * 3 + 2] = (real32)(i / ((real32)VERTEX_COUNT - 1) * SIZE);
			terrainMesh->normals[vertexPointer * 3] = 0;
			terrainMesh->normals[vertexPointer * 3 + 1] = 1;
			terrainMesh->normals[vertexPointer * 3 + 2] = 0;
			terrainMesh->texcoords[vertexPointer * 2] = (real32)(j / ((real32)VERTEX_COUNT - 1));
			terrainMesh->texcoords[vertexPointer * 2 + 1] = (real32)(i / ((real32)VERTEX_COUNT - 1));
			vertexPointer++;
		}
	}

	int pointer = 0;
	for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
		for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
			int topLeft = (gz * VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			terrainMesh->indices[pointer++] = topLeft;
			terrainMesh->indices[pointer++] = bottomLeft;
			terrainMesh->indices[pointer++] = topRight;
			terrainMesh->indices[pointer++] = topRight;
			terrainMesh->indices[pointer++] = bottomLeft;
			terrainMesh->indices[pointer++] = bottomRight;
		}
	}

	
	//Mesh mesh;


	//EntityHandle terrainHandle = AddEntity(&Data->em, EntityType_Terrain);
	//Terrain* terrainEntity = (Terrain*)GetEntity(&Data->em, terrainHandle);
	//terrainEntity->handle = terrainHandle;
	////terrainEntity->transform.position = V3(-0.0f, -0.0f, 0.0f);
	////terrainEntity->transform.scale = V3(1.0f, 1.0f, 1.0f);
	//terrainEntity->model = Data->rm.models.terrainModel; 
	//return loader.loadToVAO(vertices, textureCoords, normals, indices);*/
}