#include <iostream>
#include <fstream>
#include <string>



bool isVertSet(Vertex *vert)
{
	bool isSet = false;
	if (vert->textureIndex != -1 && vert->normalIndex != -1)
	{
		isSet = true;
	}
	return isSet;
}


int32* convertIndicesListToArray(DynamicArray<int32> indices)
{
	int32* indicesArray = (int32*)malloc(indices.count);
	for (int i = 0; i < indices.count; i++)
	{
		indicesArray[i] = indices[i];
	}
	return indicesArray;
}

bool hasSameTextureAndNormal(Vertex vert, int32 textureIndexOther, int32 normalIndexOther)
{
	bool hasSame = false;
	if (vert.textureIndex == textureIndexOther && vert.normalIndex == normalIndexOther)
	{
		hasSame = true;
	}
	return hasSame;
}


//void dealWithAlreadyProcessedVertex(Vertex previousVertex, int32 newTextureIndex, int32 newNormalIndex, DynamicArray<int32> indices, DynamicArray<Vertex> vertices)
//{
//	if (hasSameTextureAndNormal(previousVertex, newTextureIndex, newNormalIndex))
//	{
//		PushBack(&indices, previousVertex.index);
//	}
//	else
//	{
//		Vertex* anotherVertex = (Vertex*)previousVertex.duplicateVertex;
//
//		if (anotherVertex->duplicateVertex != NULL) 
//		{
//			dealWithAlreadyProcessedVertex(anotherVertex, newTextureIndex, newNormalIndex, indices, vertices);
//		}
//		else
//		{
//			Vertex duplicateVertex;
//			duplicateVertex.position = previousVertex->position;
//			duplicateVertex.index = vertices.count;
//			duplicateVertex.textureIndex = newTextureIndex;
//			duplicateVertex.normalIndex = newNormalIndex;
//			
//			//previousVertex->duplicateVertex = (Vertex*)malloc(sizeof(Vertex));
//			//memset(previousVertex->duplicateVertex, 0, sizeof(Vertex));
//			previousVertex.duplicateVertex = &duplicateVertex;
//			PushBack(&vertices, duplicateVertex);
//			PushBack(&indices, duplicateVertex.index);
//		}	
//	}
//}

void dealWithAlreadyProcessedVertex(Vertex* previousVertex, int32 newTextureIndex, int32 newNormalIndex, DynamicArray<int32> indices, DynamicArray<Vertex> vertices)
{
    if (hasSameTextureAndNormal(*previousVertex, newTextureIndex, newNormalIndex))
    {
        PushBack(&indices, previousVertex->index);
    }
    else
    {
        Vertex* anotherVertex = (Vertex*)previousVertex->duplicateVertex;

        if (anotherVertex->duplicateVertex != NULL)
        {
            dealWithAlreadyProcessedVertex(anotherVertex, newTextureIndex, newNormalIndex, indices, vertices);
        }
        else
        {
            Vertex duplicateVertex;
            duplicateVertex.position = previousVertex->position;
            duplicateVertex.index = vertices.count;
            duplicateVertex.textureIndex = newTextureIndex;
            duplicateVertex.normalIndex = newNormalIndex;

            //previousVertex->duplicateVertex = (Vertex*)malloc(sizeof(Vertex));
            //memset(previousVertex->duplicateVertex, 0, sizeof(Vertex));
            previousVertex->duplicateVertex = &duplicateVertex;
            PushBack(&vertices, duplicateVertex);
            PushBack(&indices, duplicateVertex.index);
        }
    }
}
void ProcessVertex_v2(std::string vertex0, std::string vertex1, std::string vertex2, DynamicArray<Vertex> vertices, DynamicArray<int32> indices)
{
	int32 index = (std::stof(vertex0) - 1);
	Vertex *currentVertex = &vertices[index];
	int32 textureIndex = (std::stof(vertex1) - 1);
	int32 normalIndex = (std::stof(vertex2) - 1);
	
	if (!isVertSet(currentVertex))
	{
		currentVertex->textureIndex = textureIndex;
		currentVertex->normalIndex = normalIndex;
		PushBack(&indices, index);	
	}
	else
	{
		dealWithAlreadyProcessedVertex(currentVertex, textureIndex, normalIndex, indices, vertices); 
	}
    
}

real32 convertDataToArrays(DynamicArray<Vertex> vertices, DynamicArray<vec2> textures, DynamicArray<vec3> normals, real32* verticesArray, real32* texturesArray, real32* normalsArray) 
{
	real32 furthestPoint = 0;
	for (int i = 0; i < vertices.count; i++)
	{
		Vertex currentVertex = vertices[i];
		if (currentVertex.index > furthestPoint)
		{
			furthestPoint = currentVertex.index;
		}
		vec3 position = currentVertex.position;
		vec2 texcoord = textures[currentVertex.textureIndex];
		vec3 normalVector = normals[currentVertex.normalIndex];
		verticesArray[i * 3] = position.x;
		verticesArray[i * 3 + 1] = position.y;
		verticesArray[i * 3 + 2] = position.z;
		texturesArray[i * 2] = texcoord.x;
		texturesArray[i * 2 + 1] = 1 - texcoord.y;
		normalsArray[i * 3] = normalVector.x;
		normalsArray[i * 3 + 1] = normalVector.y;
		normalsArray[i * 3 + 2] = normalVector.z;	
	}
	return furthestPoint;
}


OBJMesh LoadOBJv2(const char *modelPath)
{
	
	DynamicArray<Vertex> vertices = MakeDynamicArray<Vertex>(&Game->frameMem, 10000);
    DynamicArray<vec2> textures = MakeDynamicArray<vec2>(&Game->frameMem, 10000);
    DynamicArray<vec3> normals  = MakeDynamicArray<vec3>(&Game->frameMem, 10000);
    DynamicArray<int32> indices = MakeDynamicArray<int32>(&Game->frameMem, 10000);
   	
	std::ifstream myFile;
    myFile.open(modelPath);

    std::string myLine;
	
	bool firstF = false;
	
	if (myFile.is_open())
	{
		while (true)
		{
			std::getline(myFile, myLine);
			
			char delim = ' '; 
            int i = 0;
            int j = 0;
		
			if (myLine.substr(0, 2) == "v ")
            {
                vec3 vertex = {};
                std::string arr = {};
                while (myLine[i] != '\0')
                {
                    if (myLine[i] != delim) {
                        arr.push_back(myLine[i]);
                    }
                    else 
                    {
                        switch(j)
                        {
                            case 0:
                            {
                                arr.clear();
                                break;
                            }
                            case 1:
                            {
                                vertex.x = std::stof(arr);
                                arr.clear();
                                break;
                            }
                            case 2:
                            {
                                vertex.y = std::stof(arr);
                                arr.clear();
                                break;
                            }
                            case 3:
                            {
                                vertex.z = std::stof(arr);
                                arr.clear();
                                break;
                            }
                            default:
                            {
                                arr.clear();
                                break;
                            }
                        }
                        j++;
                    }
                    if (myLine[i + 1] == '\0')
                    {
                        vertex.z = std::stof(arr);
                        arr.clear();
                    }
                    i++;
                }
				Vertex vert = {};
				vert.duplicateVertex = (Vertex*)malloc(sizeof(Vertex));
				memset(vert.duplicateVertex, 0, sizeof(Vertex));
				vert.position = vertex;
				vert.index = vertices.count;
                PushBack(&vertices, vert);
            }
            else if (myLine.substr(0, 3) == "vt ")
            {
                vec2 texture = {};
                std::string arr = {};

                while (myLine[i] != '\0')
                {
                    if (myLine[i] != delim) {
                        arr.push_back(myLine[i]);
                    }
                    else
                    {
                        switch (j)
                        {
							case 0:
							{
								arr.clear();
								break;
							}
							case 1:
							{
								texture.x = std::stof(arr);
								arr.clear();
								break;
							}
							case 2:
							{
								texture.y = std::stof(arr);
								arr.clear();
								break;
							}
							default:
							{
								arr.clear();
								break;
							}
                        }
                        j++;
                    }
                    if (myLine[i + 1] == '\0')
                    {
                        texture.y = std::stof(arr);
                        arr.clear();
                    }
                    i++;
                }
                PushBack(&textures, texture);
            }
            else if (myLine.substr(0, 3) == "vn ")
            {
                vec3 normal = {};
                std::string arr = {};


                while (myLine[i] != '\0')
                {
                    if (myLine[i] != delim) {
                        arr.push_back(myLine[i]);
                    }
                    else
                    {
                        switch (j)
                        {
                        case 0:
                        {
                            arr.clear();
                            break;
                        }
                        case 1:
                        {
                            normal.x = std::stof(arr);
                            arr.clear();

                            break;
                        }
                        case 2:
                        {
                            normal.y = std::stof(arr);
                            arr.clear();

                            break;
                        }
                        case 3:
                        {
                            //vertex.z = strtod(arr, NULL);
                            normal.z = std::stof(arr);
                            arr.clear();

                            break;
                        }
                        default:
                        {
                            arr.clear();
                            break;
                        }
                        }
                        j++;
                        // arr[100] = {};
                    }
                    if (myLine[i + 1] == '\0')
                    {
                        normal.z = std::stof(arr);
                        arr.clear();
                    }
                    i++;
                }
                PushBack(&normals, normal);
                //myLine[i];
            }
            else if (myLine.substr(0, 2) == "f ")
            {
               break;
			}
		}
		while (!myFile.eof() && myLine.substr(0, 2) == "f ")
		{
			
			vec3 index = {};
            if (firstF == true)
            {
                std::getline(myFile, myLine);
            }
            firstF = true;
            char delimFace = '/';
            if (myLine.substr(0, 2) != "f ")
            {
                std::getline(myFile, myLine);
                continue;
            }
            int i = 0;
            int j = 0;
            int k = 0;
            char delim = ' ';

            std::string arr0[3] = {};
            std::string arr1[3] = {};
            std::string arr2[3] = {};

            while (myLine[i] != '\0')
            {
                if (myLine[i] == 'f')
                {
                    i++;
                    goto advance;
                }
                if (myLine[i] == '/')
                {
                    k++;
                    goto advance;
                }
                if (myLine[i] != ' ')
                {
                    switch (j)
                    {
                        case 0:
                        {
                            arr0[k].push_back(myLine[i]);
                            break;
                        }
                        case 1:
                        {
                            arr1[k].push_back(myLine[i]);
                            break;
                        }
                        case 2:
                        {
                            arr2[k].push_back(myLine[i]);
                            break;
                        }
                        default:
                        {break; }
                    }
                }
                else
                {
                    j++;
                    k = 0;
                }

                if (myLine[i + 1] == '\0')
                {
                    //arr2[k].push_back(myLine[i]);
                }
            advance:
                i++;
            }
			
			ProcessVertex_v2(arr0[0], arr0[1], arr0[2], vertices, indices);
			ProcessVertex_v2(arr1[0], arr1[1], arr1[2], vertices, indices);
			ProcessVertex_v2(arr2[0], arr2[1], arr2[2], vertices, indices);
			
		}
		
	}
	
	//removeUnusedVertices(vertices);
	for (int i = 0; i < vertices.count; i++)
	{
		if(!isVertSet(&vertices[i]))
	    {
			vertices[i].textureIndex = 0;
			vertices[i].normalIndex = 0;
		}
	}
	OBJMesh objMesh = {};
    objMesh.data = (void*)malloc((sizeof(real32) * vertices.count * 3) + (sizeof(real32) * vertices.count * 2) + (sizeof(real32) * vertices.count * 3));
    objMesh.size = (sizeof(real32) * vertices.count * 3) + (sizeof(real32) * vertices.count * 2) + (sizeof(real32) * vertices.count * 3);
	//objMesh.verts = (real32*)malloc(vertices.count * 3);
    objMesh.verts = (real32*)objMesh.data;
   // objMesh.texcoords = (real32*)malloc(vertices.count * 2);
	objMesh.texcoords = (real32*)((uint8*)objMesh.data + (sizeof(real32) * vertices.count * 3));
   // objMesh.normals = (real32*)malloc(vertices.count * 3);
	objMesh.normals = (real32*)((uint8*)objMesh.data + (sizeof(real32) * vertices.count * 3) + (sizeof(real32) * vertices.count * 2));
    real32 furthest = convertDataToArrays(vertices, textures, normals, objMesh.verts, objMesh.texcoords, objMesh.normals);
	objMesh.indices = (int32*)malloc(indices.count);
    objMesh.indexCount = indices.count;
    objMesh.vertCount = vertices.count * 3;
    objMesh.texcoordsCount = vertices.count * 23;
    objMesh.normalsCount = vertices.count * 3;
	objMesh.indices = convertIndicesListToArray(indices);
	objMesh.furthestPoint = furthest;
    objMesh.indexCount = furthest;
	return objMesh;


}