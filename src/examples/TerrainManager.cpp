#include <iostream>
#include <vector>

bool load_image(std::vector<unsigned char>& image, const std::string& filename, int& x, int& y)
{			// source of function is https://cplusplus.com/forum/beginner/267364/
	int n;
	unsigned char* data = stbi_load(filename.c_str(), &x, &y, &n, 3);
	if (data != nullptr)
	{
		image = std::vector<unsigned char>(data, data + x * y * 3);
	}
	stbi_image_free(data);
	return (data != nullptr);
}


real32 GetHeightOfTerrain(vec3 worldPos, Terrain terrain)
{
	real32 terrainPosX = worldPos.x - terrain.modelRenderData.position.x;
	real32 terrainPosZ = worldPos.z - terrain.modelRenderData.position.z;
	real32 gridSquareSize = terrain.mesh.SIZE / (terrain.mesh.VERTEX_COUNT - 1);
	int32 gridX = Floorf(terrainPosX / gridSquareSize);
	int32 gridZ = Floorf(terrainPosZ / gridSquareSize);
	if (gridX >= terrain.mesh.VERTEX_COUNT - 1 || gridZ >= terrain.mesh.VERTEX_COUNT - 1 || gridX < 0 || gridZ < 0)
	{	// is object on the terrain?
		return 0.0f;
	}
	real32 xCoord = Modf(terrainPosX,gridSquareSize) / gridSquareSize;
	real32 zCoord = Modf(terrainPosZ,gridSquareSize) / gridSquareSize;
	real32 heightReturn;
	if (xCoord <= 1 - zCoord)
	{
		heightReturn = barryCentric(V3(0.0f, terrain.mesh.terrainHeight[gridX][gridZ], 0.0f), 
									V3(1.0f, terrain.mesh.terrainHeight[gridX + 1][gridZ], 0.0f), 
									V3(0.0f, terrain.mesh.terrainHeight[gridX][gridZ + 1], 1.0f), 
									V2(xCoord, zCoord));
	}
	else
	{
		heightReturn = barryCentric(V3(1, terrain.mesh.terrainHeight[gridX + 1][gridZ], 0), 
									V3(1, terrain.mesh.terrainHeight[gridX + 1][gridZ + 1], 1),
									V3(0, terrain.mesh.terrainHeight[gridX][gridZ + 1], 1), 
									V2(xCoord, zCoord));
	}
	return heightReturn;
}

void GenerateTerrain(char *pathForHeightMap)
{
	OBJMesh* terrainMesh = &Game->terrain;

	int width, height;
	std::vector<unsigned char> image;
	bool success = load_image(image, pathForHeightMap, width, height);

	std::cout << "Image width = " << width << '\n';
	std::cout << "Image height = " << height << '\n';

	const size_t RGBA = 3;

	int x = 2;
	int y = 2;
	size_t index = RGBA * (y * width + x);

	Print("%d", image[index + 0]);
	Print("%d", image[index + 1]);
	Print("%d", image[index + 2]);
	

	terrainMesh->VERTEX_COUNT = 10;
	terrainMesh->SIZE = 1000;
	int32 count = terrainMesh->VERTEX_COUNT * terrainMesh->VERTEX_COUNT;

	terrainMesh->rowCount_Terrain = terrainMesh->VERTEX_COUNT;
	terrainMesh->columnCount_Terrain = terrainMesh->VERTEX_COUNT;

	terrainMesh->terrainHeight = new real32 * [terrainMesh->rowCount_Terrain];
	//terrainMesh->terrainHeight(real32**)malloc(terrainMesh->rowCount_Terrain * sizeof(real32));
	//memset(terrainMesh->terrainHeight[i], 0, sizeof(real32) * terrainMesh->columnCount_Terrain);
	for (int i = 0; i < terrainMesh->rowCount_Terrain; i++)
	{
		terrainMesh->terrainHeight[i] = new real32[terrainMesh->columnCount_Terrain];
		memset(terrainMesh->terrainHeight[i], 0, sizeof(real32) * terrainMesh->columnCount_Terrain);
	}


	terrainMesh->vertCount = count * 3;
	terrainMesh->normalsCount = count * 3;
	terrainMesh->texcoordsCount = count * 2;
	terrainMesh->indexCount = 6 * (terrainMesh->VERTEX_COUNT - 1) * (terrainMesh->VERTEX_COUNT - 1);

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
	for (int i = 0; i < terrainMesh->VERTEX_COUNT; i++) {
		for (int j = 0; j < terrainMesh->VERTEX_COUNT; j++) {
			terrainMesh->verts[vertexPointer * 3] = (real32)(j / ((real32)terrainMesh->VERTEX_COUNT - 1) * terrainMesh->SIZE);
			real32 value = (real32)(j / ((real32)terrainMesh->VERTEX_COUNT - 1) * terrainMesh->SIZE);
			real32 height = RandfRange(-20, 20);
			terrainMesh->verts[vertexPointer * 3 + 1] = height;
			terrainMesh->terrainHeight[j][i] = height;
			terrainMesh->verts[vertexPointer * 3 + 2] = (real32)(i / ((real32)terrainMesh->VERTEX_COUNT - 1) * terrainMesh->SIZE);
			terrainMesh->normals[vertexPointer * 3] = 0;
			terrainMesh->normals[vertexPointer * 3 + 1] = 1;
			terrainMesh->normals[vertexPointer * 3 + 2] = 0;
			terrainMesh->texcoords[vertexPointer * 2] = (real32)(j / ((real32)terrainMesh->VERTEX_COUNT - 1));
			terrainMesh->texcoords[vertexPointer * 2 + 1] = (real32)(i / ((real32)terrainMesh->VERTEX_COUNT - 1));
			if (terrainMesh->terrainWidth < value)
			{
				terrainMesh->terrainWidth = value;
			}
			vertexPointer++;
		}
	}

	int pointer = 0;
	for (int gz = 0; gz < terrainMesh->VERTEX_COUNT - 1; gz++) {
		for (int gx = 0; gx < terrainMesh->VERTEX_COUNT - 1; gx++) {
			int topLeft = (gz * terrainMesh->VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * terrainMesh->VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			terrainMesh->indices[pointer++] = topLeft;
			terrainMesh->indices[pointer++] = bottomLeft;
			terrainMesh->indices[pointer++] = topRight;
			terrainMesh->indices[pointer++] = topRight;
			terrainMesh->indices[pointer++] = bottomLeft;
			terrainMesh->indices[pointer++] = bottomRight;
		}
	}
}