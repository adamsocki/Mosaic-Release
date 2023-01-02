#include <iostream>
#include <fstream>
#include <string>

void ProcessVertex_v2(std::string vertex0, std::string vertex1, std::string vertex2, DynamicArray<vec3> vertices, DynamicArray<int32> indices)
{
	int32 index = (std::stof(vertex0) - 1);
	vec3 currentVertex = vertices[index];
	int32 textureIndex = (std::stof(vertex1) - 1);
	int32 normalIndex = (std::stof(vertex2) - 1);
	
	// if (currentVertex != NULL)
	// {
	// }
    
}


OBJMesh LoadOBJv2(const char *modelPath)
{
	OBJMesh objMesh = {};
	
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
                PushBack(&vertices, vertex);
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

	return objMesh;


}