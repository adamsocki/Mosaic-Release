#include <iostream>
#include <fstream>
#include <string>



bool isVertSet(Vertex vert)
{
    bool isSet = false;
    if (vert.textureIndex != -1 && vert.normalIndex != -1)
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

void dealWithAlreadyProcessedVertex(Vertex* previousVertex, int32 newTextureIndex, int32 newNormalIndex, DynamicArray<int32>* indices, DynamicArray<Vertex>* vertices)
{
    if (hasSameTextureAndNormal(*previousVertex, newTextureIndex, newNormalIndex))
    {
        PushBack(indices, previousVertex->index);
    }
    else
    {
        Vertex* anotherVertex = (Vertex*)previousVertex->duplicateVertex;

        if (anotherVertex->hasDuplicate != false)
        {
            dealWithAlreadyProcessedVertex(anotherVertex, newTextureIndex, newNormalIndex, indices, vertices);
        }
        else
        {
            Vertex duplicateVertex;
            duplicateVertex.position = previousVertex->position;
            duplicateVertex.index = vertices->count;
            duplicateVertex.textureIndex = newTextureIndex;
            duplicateVertex.normalIndex = newNormalIndex;
            duplicateVertex.hasDuplicate = true;
            //previousVertex->duplicateVertex = (Vertex*)malloc(sizeof(Vertex));
            //memset(previousVertex->duplicateVertex, 0, sizeof(Vertex));
            previousVertex->duplicateVertex = &duplicateVertex;
            PushBack(vertices, duplicateVertex);
            PushBack(indices, duplicateVertex.index);
        }
    }
}
void ProcessVertex_v2(std::string vertex0, std::string vertex1, std::string vertex2, DynamicArray<Vertex>* vertices, DynamicArray<int32>* indices)
{
    /*int32 index = (std::stof(vertex0) - 1);
    Vertex *currentVertex = *vertices[index];
    int32 textureIndex = (std::stof(vertex1) - 1);
    int32 normalIndex = (std::stof(vertex2) - 1);

    if (!isVertSet(currentVertex))
    {
        currentVertex->textureIndex = textureIndex;
        currentVertex->normalIndex = normalIndex;
        PushBack(indices, index);
    }
    else
    {
        dealWithAlreadyProcessedVertex(currentVertex, textureIndex, normalIndex, indices, vertices);
    }*/

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


OBJMesh LoadOBJv2(const char* modelPath)
{
    OBJMesh objMesh = {};
    objMesh.verts = (real32*)malloc(100000 * 3 * sizeof(real32));
    memset(objMesh.verts, 0, sizeof(real32) * 10000 * 3);
    objMesh.indices = (int32*)malloc(100000 * sizeof(int32));
    memset(objMesh.indices, 0, sizeof(int32) * 100000);
    objMesh.texcoords = (real32*)malloc(10000 * 2 * sizeof(real32));
    memset(objMesh.texcoords, 0, sizeof(real32) * 10000 * 2);
    objMesh.indices = (int32*)malloc(100000);
    int32* indicesArray = (int32*)malloc(100000);

    DynamicArray<Vertex> vertices = MakeDynamicArray<Vertex>(&Game->frameMem, 10000);
    DynamicArray<vec2> textures = MakeDynamicArray<vec2>(&Game->frameMem, 10000);
    DynamicArray<vec3> normals = MakeDynamicArray<vec3>(&Game->frameMem, 10000);
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
                        switch (j)
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
                vert.hasDuplicate = false;
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
                    }
                    if (myLine[i + 1] == '\0')
                    {
                        normal.z = std::stof(arr);
                        arr.clear();
                    }
                    i++;
                }
                PushBack(&normals, normal);
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

            /*ProcessVertex_v2(arr0[0], arr0[1], arr0[2], &vertices, &indices);
            ProcessVertex_v2(arr1[0], arr1[1], arr1[2], &vertices, &indices);
            ProcessVertex_v2(arr2[0], arr2[1], arr2[2], &vertices, &indices);
            */

            int32 index_Value0 = (std::stof(arr0[0]) - 1);
            // Vertex* currentVertex = *vertices[index];
            int32 textureIndex0 = (std::stof(arr0[1]) - 1);
            int32 normalIndex0 = (std::stof(arr0[2]) - 1);

            if (!isVertSet(vertices[index_Value0]))
            {
                vertices[index_Value0].textureIndex = textureIndex0;
                vertices[index_Value0].normalIndex = normalIndex0;
                PushBack(&indices, index_Value0);
            }
            else
            {
                dealWithAlreadyProcessedVertex(&vertices[index_Value0], textureIndex0, normalIndex0, &indices, &vertices);
            }

            int32 index_Value1 = (std::stof(arr1[0]) - 1);
            // Vertex* currentVertex = *vertices[index];
            int32 textureIndex1 = (std::stof(arr1[1]) - 1);
            int32 normalIndex1 = (std::stof(arr1[2]) - 1);

            if (!isVertSet(vertices[index_Value1]))
            {
                vertices[index_Value1].textureIndex = textureIndex1;
                vertices[index_Value1].normalIndex = normalIndex1;
                PushBack(&indices, index_Value1);
            }
            else
            {
                dealWithAlreadyProcessedVertex(&vertices[index_Value1], textureIndex1, normalIndex1, &indices, &vertices);
            }

            int32 index_Value2 = (std::stof(arr2[0]) - 1);
            //// Vertex* currentVertex = *vertices[index];
            int32 textureIndex2 = (std::stof(arr2[1]) - 1);
            int32 normalIndex2 = (std::stof(arr2[2]) - 1);

            if (!isVertSet(vertices[index_Value2]))
            {
                vertices[index_Value2].textureIndex = textureIndex2;
                vertices[index_Value2].normalIndex = normalIndex2;
                PushBack(&indices, index_Value2);
            }
            else
            {
                dealWithAlreadyProcessedVertex(&vertices[index_Value2], textureIndex2, normalIndex2, &indices, &vertices);
            }
        }

    }

    //removeUnusedVertices(vertices);
    for (int i = 0; i < vertices.count; i++)
    {
        if (!isVertSet(vertices[i]))
        {
            vertices[i].textureIndex = 0;
            vertices[i].normalIndex = 0;
        }
    }



    objMesh.data = (void*)malloc((sizeof(real32) * vertices.count * 3) + (sizeof(real32) * vertices.count * 2) + (sizeof(real32) * vertices.count * 3));
    objMesh.size = (sizeof(real32) * vertices.count * 3) + (sizeof(real32) * vertices.count * 2) + (sizeof(real32) * vertices.count * 3);
    //objMesh.verts = (real32*)malloc(vertices.count * 3);
    objMesh.verts = (real32*)objMesh.data;
    // objMesh.texcoords = (real32*)malloc(vertices.count * 2);
    objMesh.texcoords = (real32*)((uint8*)objMesh.data + (sizeof(real32) * vertices.count * 3));
    // objMesh.normals = (real32*)malloc(vertices.count * 3);
    objMesh.normals = (real32*)((uint8*)objMesh.data + (sizeof(real32) * vertices.count * 3) + (sizeof(real32) * vertices.count * 2));
    real32 furthest = convertDataToArrays(vertices, textures, normals, objMesh.verts, objMesh.texcoords, objMesh.normals);
    objMesh.indexCount = indices.count;
    objMesh.vertCount = vertices.count * 3;
    objMesh.texcoordsCount = vertices.count * 2;
    objMesh.normalsCount = vertices.count * 3;
    //objMesh.indices = convertIndicesListToArray(indices);
    for (int i = 0; i < indices.count; i++)
    {
        indicesArray[i] = indices[i];
    }

    // set highest vertex point
    objMesh.minAABB = {};
    objMesh.maxAABB = {};
    for (int i = 0; i < vertices.count; i++)
    {
        if (objMesh.minAABB.x > vertices[i].position.x)
        {
            objMesh.minAABB.x = vertices[i].position.x;
        }

        if (objMesh.minAABB.y > vertices[i].position.y)
        {
            objMesh.minAABB.y = vertices[i].position.y;
        }

        if (objMesh.minAABB.z > vertices[i].position.z)
        {
            objMesh.minAABB.z = vertices[i].position.z;
        }

        if (objMesh.maxAABB.x < vertices[i].position.x)
        {
            objMesh.maxAABB.x = vertices[i].position.x;
        }

        if (objMesh.maxAABB.y < vertices[i].position.y)
        {
            objMesh.maxAABB.y = vertices[i].position.y;
        }

        if (objMesh.maxAABB.z < vertices[i].position.z)
        {
            objMesh.maxAABB.z = vertices[i].position.z;
        }
    }

    real32 max_x = Abs(objMesh.maxAABB.x);
    real32 max_y = Abs(objMesh.maxAABB.y);
    real32 max_z = Abs(objMesh.maxAABB.z);
    real32 min_x = Abs(objMesh.minAABB.x);
    real32 min_y = Abs(objMesh.minAABB.y);
    real32 min_z = Abs(objMesh.minAABB.z);

    objMesh.meshOffsetForAABB = {};
    objMesh.meshOffsetForAABB.x = (max_x + min_x) ;
    objMesh.meshOffsetForAABB.y = (max_y + min_y) ;
    objMesh.meshOffsetForAABB.z = (max_z + min_z) ;


    objMesh.indices = indicesArray;
    // objMesh.furthestPoint = furthest;
       // objMesh.indexCount = furthest;

    DeallocateDynamicArray(&vertices);
    DeallocateDynamicArray(&textures);
    DeallocateDynamicArray(&normals);
    DeallocateDynamicArray(&indices);

    return objMesh;
}