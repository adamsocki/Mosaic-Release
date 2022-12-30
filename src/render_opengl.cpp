#include <iostream>
#include <fstream>
#include <string>


void DrawOBJModel(OBJMesh *mesh, vec2 pos, vec2 scale, real32 angle, vec4 color)
{


    //GLuint vaoID glGenVertexArrays();
    Shader* shader = &Game->shader;
    SetShader(shader);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   // Mesh* mesh = &Game->quad;

    mat4 model = TRS(V3(pos.x, pos.y, 10), AxisAngle(V3(0, 0, 1), angle), V3(scale.x, scale.y, 0.0f));

    glUniformMatrix4fv(shader->uniforms[0].id, 1, GL_FALSE, model.data);
    glUniformMatrix4fv(shader->uniforms[1].id, 1, GL_FALSE, Game->camera.viewProjection.data);

    glUniform4fv(shader->uniforms[2].id, 1, color.data);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBufferID);

    // 1st attribute buffer : vertices
    int vert = glGetAttribLocation(shader->programID, "vertexPosition_modelspace");
    glEnableVertexAttribArray(vert);
    glVertexAttribPointer(vert, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);


    glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, (GLvoid*)0);

    glDisableVertexAttribArray(vert);

}


void InitOBJMesh(OBJMesh *mesh)
{
    GLuint vertexBuffer;

    glGenBuffers(1, &vertexBuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, mesh->size, mesh->data, GL_STATIC_DRAW);

    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indexCount * sizeof(int32), mesh->indices, GL_STATIC_DRAW);



    mesh->vertBufferID = vertexBuffer;
    mesh->indexBufferID = indexBuffer;
}

void ProcessVertex(std::string vertexData0, std::string vertexData1, std::string vertexData2, 
    DynamicArray<int32> indices, DynamicArray<vec2> textures, DynamicArray<vec3> normals,  
    DynamicArray<real32> texturesArray, DynamicArray<real32> normalsArray)
{
    int32 currentVertexPointer = (std::stof(vertexData0) - 1);
    PushBack(&indices, currentVertexPointer);
    
    vec2 currentTexture = textures[std::stof(vertexData1) - 1];
    InsertAtIndex(&texturesArray, currentVertexPointer * 2, currentTexture.x);
    InsertAtIndex(&texturesArray, currentVertexPointer * 2 + 1, 1 - currentTexture.y);

    vec3 currentNormal = normals[std::stof(vertexData2) - 2];
    InsertAtIndex(&normalsArray, currentVertexPointer * 2, currentNormal.x);
    InsertAtIndex(&normalsArray, currentVertexPointer * 2 + 1, currentNormal.y);
    InsertAtIndex(&normalsArray, currentVertexPointer * 2 + 2, currentNormal.z);
}

void ProcessVertexPointer(std::string vertexData0, std::string vertexData1, std::string vertexData2,
    DynamicArray<int32> indices, DynamicArray<vec2> textures, DynamicArray<vec3> normals,
    real32* texturesArray, real32* normalsArray)
{
    int32 currentVertexPointer = (std::stof(vertexData0) - 1);
    PushBack(&indices, currentVertexPointer);
    
    vec2 currentTexture = textures[std::stof(vertexData1) - 1];
    texturesArray[currentVertexPointer * 2] = currentTexture.x;
    
    texturesArray[currentVertexPointer * 2 + 1] = 1 - currentTexture.y;

    vec3 currentNormal = normals[std::stof(vertexData2) - 1];
    normalsArray[currentVertexPointer * 3] = currentNormal.x;
    normalsArray[currentVertexPointer * 3 + 1] = currentNormal.y;
    normalsArray[currentVertexPointer * 3 + 2] = currentNormal.z;

}


OBJMesh LoadOBJModel(const char *modelPath)
{
    OBJMesh objMesh = {};

    objMesh.verts = (real32*)malloc(100000 * 3 * sizeof(real32));
    memset(objMesh.verts, 0, sizeof(real32) * 10000 * 3);
    //    indicesArray = MakeDynamicArray<int32>(&Game->frameMem, indices.count);
        //indicesArrayPointer = (int32*)malloc(indices.count * sizeof(int32));
    objMesh.indices = (int32*)malloc(100000 * sizeof(int32));
    memset(objMesh.indices, 0, sizeof(int32) * 100000);
    objMesh.texcoords = (real32*)malloc(10000* 2 * sizeof(real32));
    memset(objMesh.texcoords, 0, sizeof(real32) * 10000 * 2);
    objMesh.normals = (real32*)malloc(10000 * 3 * sizeof(real32));
    memset(objMesh.normals, 0, sizeof(real32) * 10000 * 3);

    DynamicArray<vec3> vertices = MakeDynamicArray<vec3>(&Game->frameMem, 10000);
    DynamicArray<vec2> textures = MakeDynamicArray<vec2>(&Game->frameMem, 10000);
    DynamicArray<vec3> normals  = MakeDynamicArray<vec3>(&Game->frameMem, 10000);
    DynamicArray<int32> indices = MakeDynamicArray<int32>(&Game->frameMem, 10000);
    
    real32* verticesArrayPointer;
    real32* texturesArrayPointer;
    real32* normalsArrayPointer;
    int32* indicesArrayPointer;

    int32 currentIndex = 0;

    bool firstF = false;
    
    //DynamicArray<real32> verticesArray;
    //DynamicArray<real32> texturesArray;
    //DynamicArray<real32> normalsArray;
   // DynamicArray<int32> indicesArray;

    std::ifstream myFile;
    myFile.open(modelPath);

    std::string myLine;

    if (myFile.is_open())
    {
        while (myFile.is_open())
        {
            std::getline(myFile, myLine);
            //arr[1] = myLine[1];
            char delim = ' '; 
            int i = 0;
            int j = 0;
       //     break;
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
                //char* s = {};
                std::string arr = {};


                while (myLine[i] != '\0')
                {
                    if (myLine[i] != delim) {
                        arr.push_back(myLine[i]);
                        //arr.append(myLine[i]);
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
                //myLine[i] = {};
            }
            else if (myLine.substr(0, 3) == "vn ")
            {
                vec3 normal = {};
                //char* s = {};
                std::string arr = {};


                while (myLine[i] != '\0')
                {
                    if (myLine[i] != delim) {
                        arr.push_back(myLine[i]);
                        //arr.append(myLine[i]);
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
                            //vertex.x = strtod(arr, NULL);
                            normal.x = std::stof(arr);
                            arr.clear();

                            break;
                        }
                        case 2:
                        {
                            //vertex.y = strtod(arr, NULL);
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
               // texturesArray = MakeDynamicArray<real32>(&Game->frameMem, textures.count * 2);
               // normalsArray  = MakeDynamicArray<real32>(&Game->frameMem, normals.count * 3);
               // texturesArrayPointer = (real32*)malloc(textures.count * 2 * sizeof(real32));
               // normalsArrayPointer = (real32*)malloc(normals.count * 3 * sizeof(real32));
              /* objMesh.texcoords = (real32*)malloc(textures.count * 2 * sizeof(real32));
               memset(objMesh.texcoords, 0, sizeof(real32)* textures.count * 2);
               objMesh.normals = (real32*)malloc(textures.count * 3 * sizeof(real32));
               memset(objMesh.normals, 0, sizeof(real32) * normals.count * 3);*/


                break;
            } 
        }
        while (!myFile.eof())
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

            //ProcessVertex(arr0[0], arr0[1], arr0[2], indices, textures, normals, texturesArray, normalsArray);
            //ProcessVertex(arr2[0], arr2[1], arr2[2], indices, textures, normals, texturesArray, normalsArray);
            //ProcessVertex(arr1[0], arr1[1], arr1[2], indices, textures, normals, texturesArray, normalsArray);
            int32 currentVertexPointer = (std::stof(arr0[0]) - 1);
            //PushBack(&indices, currentVertexPointer);
             objMesh.indices[currentIndex] = currentVertexPointer;
             currentIndex++;
             vec2 currentTexture = textures[std::stof(arr0[1]) - 1];
             objMesh.texcoords[currentVertexPointer * 2] = currentTexture.x;
             objMesh.texcoords[currentVertexPointer * 2 + 1] = 1 - currentTexture.y;

             vec3 currentNormal = normals[std::stof(arr0[2]) - 1];
             objMesh.normals[currentVertexPointer * 3] = currentNormal.x;
             objMesh.normals[currentVertexPointer * 3 + 1] = currentNormal.y;
             objMesh.normals[currentVertexPointer * 3 + 2] = currentNormal.z;


             //1
             int32 currentVertexPointer1 = (std::stof(arr1[0]) - 1);
             PushBack(&indices, currentVertexPointer1);
             objMesh.indices[currentIndex] = currentVertexPointer1;
             currentIndex++;

             vec2 currentTexture1 = textures[std::stof(arr1[1]) - 1];
             objMesh.texcoords[currentVertexPointer1 * 2] = currentTexture1.x;
             objMesh.texcoords[currentVertexPointer1 * 2 + 1] = 1 - currentTexture1.y;

             vec3 currentNormal1 = normals[std::stof(arr1[2]) - 1];
             objMesh.normals[currentVertexPointer1 * 3] = currentNormal1.x;
             objMesh.normals[currentVertexPointer1 * 3 + 1] = currentNormal1.y;
             objMesh.normals[currentVertexPointer1 * 3 + 2] = currentNormal1.z;

             //2
             int32 currentVertexPointer2 = (std::stof(arr2[0]) - 1);
             PushBack(&indices, currentVertexPointer2);
             objMesh.indices[currentIndex] = currentVertexPointer2;
             currentIndex++;

             vec2 currentTexture2 = textures[std::stof(arr2[1]) - 1];
             objMesh.texcoords[currentVertexPointer2 * 2] = currentTexture2.x;
             objMesh.texcoords[currentVertexPointer2 * 2 + 1] = 1 - currentTexture2.y;

             vec3 currentNormal2 = normals[std::stof(arr2[2]) - 1];
             objMesh.normals[currentVertexPointer2 * 3] = currentNormal2.x;
             objMesh.normals[currentVertexPointer2 * 3 + 1] = currentNormal2.y;
             objMesh.normals[currentVertexPointer2 * 3 + 2] = currentNormal2.z;
           // ProcessVertexPointer(arr0[0], arr0[1], arr0[2], indices, textures, normals, texturesArrayPointer, normalsArrayPointer);
            //ProcessVertexPointer(arr2[0], arr2[1], arr2[2], indices, textures, normals, texturesArrayPointer, normalsArrayPointer);
            //ProcessVertexPointer(arr1[0], arr1[1], arr1[2], indices, textures, normals, texturesArrayPointer, normalsArrayPointer);

        }
    }

   // verticesArray = MakeDynamicArray<real32>(&Game->frameMem, vertices.count * 3);
    verticesArrayPointer = (real32*)malloc(vertices.count * 3 * sizeof(real32));
//    objMesh.verts = (real32*)malloc(vertices.count * 3 * sizeof(real32));
//    memset(objMesh.verts, 0, sizeof(real32) * vertices.count * 3);
////    indicesArray = MakeDynamicArray<int32>(&Game->frameMem, indices.count);
//    //indicesArrayPointer = (int32*)malloc(indices.count * sizeof(int32));
//    objMesh.indices = (int32*)malloc(indices.count * sizeof(int32));
//    memset(objMesh.indices, 0, sizeof(int32)* indices.count);



    int32 vertexPointer = 0;
    
    for (int i = 0; i < vertices.count; i++)
    {
        verticesArrayPointer[vertexPointer++] = vertices[i].x;
        verticesArrayPointer[vertexPointer++] = vertices[i].y;
        verticesArrayPointer[vertexPointer++] = vertices[i].z;
    }
    


    /*for (int i = 0; i < indices.count; i++)
    {
        objMesh.indices[i] = indices[i];
    }*/

    objMesh.vertCount = vertices.count;
   // objMesh.verts = verticesArrayPointer;
    //objMesh.normals = normalsArrayPointer;
   
    objMesh.indexCount = indices.count;
    //objMesh.indices = indicesArrayPointer;

    objMesh.texcoordsCount = textures.count;
    //objMesh.texcoords = texturesArrayPointer;

    objMesh.data = (void*)malloc((sizeof(vec3)* objMesh.vertCount * 3) + (sizeof(vec2) * objMesh.texcoordsCount* 2));
    objMesh.size = (sizeof(vec3) * objMesh.vertCount * 3) + (sizeof(vec2) * objMesh.texcoordsCount * 2);

    objMesh.verts = (real32 *)objMesh.data; // TODO > THIS IS THE ISSUE
    //objMesh.verts = verticesArrayPointer; // TODO > THIS IS THE ISSUE
    int32 vertCounter = 0;
    for (int i = 0; i < vertices.count; i++)
    {
        objMesh.verts[vertCounter] = vertices[i].x;
        vertCounter++;
        objMesh.verts[vertCounter] = vertices[i].y;
        vertCounter++;
        objMesh.verts[vertCounter] = vertices[i].z;
        vertCounter++;
    }
    objMesh.vertSize = (sizeof(real32) * objMesh.vertCount * 3);

    int32 texCounter = 0;
    objMesh.texcoords = (real32*)((uint8*)objMesh.data + (sizeof(vec3) * objMesh.vertCount * 3));
    for (int i = 0; i < vertices.count; i++)
    {
        objMesh.texcoords[texCounter] = textures[i].x;
        texCounter++;
        objMesh.texcoords[texCounter] = textures[i].y;
        texCounter++;
    }
    objMesh.texcoordsSize = (sizeof(real32) * objMesh.texcoordsCount * 2);

    DeallocateDynamicArray(&vertices);
    DeallocateDynamicArray(&textures);
    DeallocateDynamicArray(&normals);
    DeallocateDynamicArray(&indices);
    
        
   return objMesh;

}
    //vec3* vertsForMesh = (vec3*)malloc(vertices.count * sizeof(vec3));
    //real32* vertsForPointer = (real32*)malloc(vertices.count * 3 * sizeof(vec3));
    //int32 counter = 0;
    //for (int i = 0; i < verticesArray.count; i++)
    //{
    //    vertsForMesh[i].x = verticesArray[counter++];
    //    vertsForMesh[i].y = verticesArray[counter++];
    //    vertsForMesh[i].z = verticesArray[counter++];
    //}
    //mesh.vertCount = vertices.count;
    //mesh.verts = vertsForMesh;
    //
    ////int* indicesForMesh = {};
    //uint32* indicesForPointer = (uint32*)malloc(indices.count * sizeof(uint32));
    //for (int i = 0; i < normals.count; i++)
    //{
    //    indicesForPointer[i] = indices[i];
    //}
    //mesh.indexCount = indices.count;
    //mesh.indices = indicesForPointer;
    //vec3* texcoordsForMesh = (vec3*)malloc(textures.count * sizeof();
    //mesh.texcoordsCount = textures.count;
    //mesh.texcoords = texturesArrayPointer;
    //
//    mesh.verts = &verticesArray;






inline bool glCheckError_(char *file, uint32 line) {
    GLenum _glError = glGetError();
    if (_glError != GL_NO_ERROR) {
        Print("OpenGL error (%s:%d): 0x%x (%d)\n", file, line, _glError, _glError);
        return true;
    }
    return false;
}

#define glCheckError() glCheckError_(__FILE__, __LINE__);

void LoadShader(const char *vertPath, const char *fragPath, Shader *shader) {
    FILE *file = fopen(vertPath, "r");
    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        shader->vertSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        shader->vertSrc = (char *)malloc(shader->vertSize + 1);
        int index = 0;
        int c = fgetc(file);
        while (c != EOF) {
            shader->vertSrc[index++] = c;
            c = fgetc(file);
        }

        shader->vertSrc[index] = 0;

        fclose(file);
    }
    else {
        Print("Error opening file %s", vertPath);
    }

    file = fopen(fragPath, "r");

    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        shader->fragSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        shader->fragSrc = (char *)malloc(shader->fragSize + 1);
        int index = 0;
        int c = fgetc(file);
        while (c != EOF) {
            shader->fragSrc[index++] = c;
            c = fgetc(file);
        }

        shader->fragSrc[index] = 0;

        fclose(file);
    }
    else {
        Print("Error opening file %s", fragPath);
    }
}

bool ShaderCompiled(GLuint shader, char **infoLog) {
    int32 isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        if (infoLog != NULL) {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            maxLength = 256;

            *infoLog = (GLchar *)malloc(sizeof(GLchar) * maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, (GLchar *)*infoLog);
        }

        Print(*infoLog);
        
        glDeleteShader(shader);
    }

    return isCompiled;
}

bool ShaderLinked(GLuint shader, char **infoLog) {
    int32 isLinked = 0;
    glGetProgramiv(shader, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) {
        if (infoLog != NULL) {
            GLint maxLength = 0;
            glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            maxLength = 256;

            *infoLog = (GLchar *)malloc(sizeof(GLchar) * maxLength);
            glGetProgramInfoLog(shader, maxLength, &maxLength, (GLchar *)*infoLog);
        }

        Print(*infoLog);
        
        glDeleteShader(shader);
    }

    return isLinked;
}


void CompileShader(Shader *shader, uint32 uniformCount, const char **uniformNames) {
    char *infoLog = NULL;
    
    if (shader->vertSrc != NULL) {
        shader->vertID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(shader->vertID, 1, (const GLchar**)&shader->vertSrc, (GLint *)&shader->vertSize);
        glCheckError();
        glCompileShader(shader->vertID);
        glCheckError();

        Print("checking vert shader");
        ShaderCompiled(shader->vertID, &infoLog);
    }
    if (shader->fragSrc != NULL) {
        shader->fragID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(shader->fragID, 1, (const GLchar**)&shader->fragSrc, (GLint *)&shader->fragSize);
        glCheckError();
        glCompileShader(shader->fragID);
        glCheckError();

        Print("checking frag shader");
        ShaderCompiled(shader->vertID, &infoLog);
    }


    shader->programID = glCreateProgram();

    if (!glIsProgram(shader->programID)) {
        Print("NOT A SHADER!");
    }
    
    if (shader->vertID != 0) {
        glAttachShader(shader->programID, shader->vertID);
        glCheckError();
    }
    if (shader->fragID != 0) {
        glAttachShader(shader->programID, shader->fragID);
        glCheckError();
    }

    glLinkProgram(shader->programID);
    glCheckError();

    ShaderLinked(shader->programID, &infoLog);
    
    
    shader->uniformCount = uniformCount;

    shader->uniforms = (ShaderUniform *)malloc(sizeof(ShaderUniform) * uniformCount);
    
    for (int i = 0; i < uniformCount; i++) {
        ShaderUniform *uniform = &shader->uniforms[i];
        const char *uniformName = uniformNames[i];

        uint32 nameLen = strlen(uniformName);
        uniform->name = (char *)malloc(nameLen + 1);
        memcpy(uniform->name, uniformName, nameLen);
        uniform->name[nameLen] = 0;
        
        uniform->id = glGetUniformLocation(shader->programID, uniform->name);
        glCheckError();
        
        if (uniform->id >= 0) {
            Print("Setting uniform %s", uniform->name);    
        }
        else {
            Print("failed to set %s", uniform->name);    
        }
        ShaderCompiled(shader->vertID, &infoLog);
    }
}

void SetShader(Shader *shader) {
    glUseProgram(shader->programID);
    //glCheckError();
}

vec2 PixelToNorm(int32 x, int32 y) {
    return V2(x / (Game->screenWidth * 1.0f), y / (Game->screenHeight * 1.0f));
}

vec2 PixelToNorm(vec2i pixel) {
    return V2(pixel.x / (Game->screenWidth * 1.0f), pixel.y / (Game->screenHeight * 1.0f));
}

vec2 NormToPixel(vec2 norm) {
    return V2(norm.x * Game->screenWidth, norm.y * Game->screenHeight);
}


void ClearColor(vec4 color) {
    glClearColor(color.r, color.g, color.b, color.a);
}


void InitMesh(Mesh *mesh) {
    GLuint vertexBuffer;

    glGenBuffers(1, &vertexBuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, mesh->size, mesh->data, GL_STATIC_DRAW);

    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indexCount * sizeof(uint32), mesh->indices, GL_STATIC_DRAW);

    mesh->vertBufferID = vertexBuffer;
    mesh->indexBufferID = indexBuffer;
}

void OpenGL_InitTexture(Sprite *texture);
    
void LoadSprite(Sprite *sprite, char *path) {
    int32 x, y, n;
    uint8 *data = stbi_load(path, &x, &y, &n, 4);

    AllocateSprite(sprite, x, y);

    memcpy(sprite->data, data, sprite->size);

    free(data);

    OpenGL_InitTexture(sprite);
}

void LoadSprite(Sprite *sprite) {
    OpenGL_InitTexture(sprite);
}

// This must be called before we can draw a sprite.
void OpenGL_InitTexture(Sprite *texture) {
    glGenTextures(1, (GLuint *)&texture->textureID);
    glCheckError();

    glBindTexture(GL_TEXTURE_2D, texture->textureID);
    glCheckError();

    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->data);
    glCheckError();

    glBindTexture(GL_TEXTURE_2D, 0);
    glCheckError();
}

void InitFontTable(FontTable *font) {
    glGenTextures(1, (GLuint *)&font->texcoordsMapID);
    glBindTexture(GL_TEXTURE_1D, font->texcoordsMapID);

    // @TODO: why is this necessary? 
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA32F, font->glyphCount, 0, GL_RGBA, GL_FLOAT, font->texcoordsMapData);
    glBindTexture(GL_TEXTURE_1D, 0);

    OpenGL_InitTexture(&font->texture);
}

void InitGlyphBuffers(int32 count) {
    for (int i = 0; i < count; i++) {
        GlyphBuffer *buffer = &Game->glyphBuffers[i];
            
        buffer->capacity = GlyphBufferCapacity;
        buffer->size = buffer->capacity * sizeof(GlyphData);
        buffer->data = (GlyphData *)malloc(buffer->size);
        memset(buffer->data, 0, buffer->size);

        glGenBuffers(1, (GLuint *)&buffer->bufferID);
        glBindBuffer(GL_ARRAY_BUFFER, buffer->bufferID);
        glBufferData(GL_ARRAY_BUFFER, buffer->size, buffer->data, GL_STATIC_DRAW);
    }
}

void DrawSprite(vec2 position, vec2 scale, real32 angle, Sprite *texture) {
    Shader *shader = &Game->texturedQuadShader;
    SetShader(shader);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Mesh *mesh = &Game->quad;

    //mat4 model = TRS(V3(position.x - radius * 0.5f, position.y + radius * 0.5f, 0), IdentityQuaternion(), V3(radius));
    mat4 model = TRS(V3(position.x, position.y, 0), AxisAngle(V3(0, 0, 1), angle), V3(scale.x, scale.y, 1.0f));
        
    //mat4 model = TRS(V3(position.x, position.y, 0), IdentityQuaternion(), V3(scale.x, scale.y, 1));

    //vec4 topLeft = mvp * V4(gameMem->quad.verts[0], 1.0f);
    glUniformMatrix4fv(shader->uniforms[0].id, 1, GL_FALSE, model.data);
    glUniformMatrix4fv(shader->uniforms[1].id, 1, GL_FALSE, Game->camera.viewProjection.data);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->textureID);
    glUniform1i(shader->uniforms[2].id, 0);

    glUniform1fv(shader->uniforms[3].id, 1, &Game->time);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBufferID);

    // 1st attribute buffer : vertices
    int vert = glGetAttribLocation(shader->programID, "vertexPosition_modelspace");
    glEnableVertexAttribArray(vert);
    glVertexAttribPointer(vert, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        
    // 2nd attribute buffer : texcoords
    int texcoord = glGetAttribLocation(shader->programID, "in_texcoord");
    glEnableVertexAttribArray(texcoord);
    glVertexAttribPointer(texcoord, 2, GL_FLOAT, GL_FALSE, 0, (void *)((sizeof(vec3) * mesh->vertCount)));
        
    glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, (GLvoid *)0);

    glDisableVertexAttribArray(vert);
    glDisableVertexAttribArray(texcoord);    
}

void DrawSprite(vec2 position, vec2 scale, Sprite *texture) {
    DrawSprite(position, scale, 0.0f, texture);
}


void DrawRect(vec2 pos, vec2 scale, real32 angle, vec4 color) {
    // @PERF: don't do this every draw call
    Shader *shader = &Game->shader;
    SetShader(shader);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Mesh *mesh = &Game->quad;
    
    mat4 model = TRS(V3(pos.x, pos.y, 0), AxisAngle(V3(0, 0, 1), angle), V3(scale.x, scale.y, 0.0f));

    glUniformMatrix4fv(shader->uniforms[0].id, 1, GL_FALSE, model.data);
    glUniformMatrix4fv(shader->uniforms[1].id, 1, GL_FALSE, Game->camera.viewProjection.data);

    glUniform4fv(shader->uniforms[2].id, 1, color.data);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBufferID);

    // 1st attribute buffer : vertices
    int vert = glGetAttribLocation(shader->programID, "vertexPosition_modelspace");
    glEnableVertexAttribArray(vert);
    glVertexAttribPointer(vert, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);


    glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, (GLvoid *)0);

    glDisableVertexAttribArray(vert);
}

void DrawRect(vec2 pos, vec2 scale, vec4 color) {
    DrawRect(pos, scale, 0, color);
}


void DrawCoolRect(vec2 pos, vec2 scale, real32 angle, vec4 color) {
    // @PERF: don't do this every draw call
    Shader *shader = &Game->coolShader;
    SetShader(shader);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Mesh *mesh = &Game->quad;
    
    mat4 model = TRS(V3(pos.x, pos.y, 0), AxisAngle(V3(0, 0, 1), angle), V3(scale.x, scale.y, 0.0f));

    glUniformMatrix4fv(shader->uniforms[0].id, 1, GL_FALSE, model.data);
    glUniformMatrix4fv(shader->uniforms[1].id, 1, GL_FALSE, Game->camera.viewProjection.data);
    glUniform4fv(shader->uniforms[2].id, 1, color.data);
    glUniform1fv(shader->uniforms[3].id, 1, &Game->time);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBufferID);

    // 1st attribute buffer : vertices
    int vert = glGetAttribLocation(shader->programID, "vertexPosition_modelspace");
    glEnableVertexAttribArray(vert);
    glVertexAttribPointer(vert, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    int texcoords = glGetAttribLocation(shader->programID, "in_texcoords");
    glEnableVertexAttribArray(texcoords);
    glVertexAttribPointer(texcoords, 2, GL_FLOAT, GL_FALSE, 0, (void *)(sizeof(vec3) * mesh->vertCount));
        
    glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, (GLvoid *)0);

    glDisableVertexAttribArray(vert);
}

// @NOTE: origin of rect and screen are both top left
// @GACK: this is pretty weird cause it's not how DrawRect or DrawSprite work!
void DrawRectScreen(vec2 pos, vec2 scale, vec4 color) {
    Shader *shader = &Game->shader;
    SetShader(shader);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Mesh *mesh = &Game->quadTopLeft;
    
    mat4 model = TRS(V3(pos.x, pos.y, 0), IdentityQuaternion(), V3(scale.x, scale.y, 0.0f));

    mat4 projMat = Orthographic(0, Game->screenWidth, Game->screenHeight, 0, -1, 1);
    
    glUniformMatrix4fv(shader->uniforms[0].id, 1, GL_FALSE, model.data);
    glUniformMatrix4fv(shader->uniforms[1].id, 1, GL_FALSE, projMat.data);

    glUniform4fv(shader->uniforms[2].id, 1, color.data);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBufferID);

    // 1st attribute buffer : vertices
    int vert = glGetAttribLocation(shader->programID, "vertexPosition_modelspace");
    glEnableVertexAttribArray(vert);
    glVertexAttribPointer(vert, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        
    glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, (GLvoid *)0);

    glDisableVertexAttribArray(vert);
}

void DrawRectScreenNorm(vec2 pos, vec2 scale, vec4 color) {
    vec2 pos_ = V2(pos.x * Game->screenWidth, pos.y * Game->screenHeight);
    vec2 scale_ = V2(scale.x * Game->screenWidth, scale.y * Game->screenWidth);

    DrawRectScreen(pos_, scale_, color);
}


void DrawLine(vec2 a, vec2 b, real32 width, vec4 color) {
    vec2 c = Lerp(a, b, 0.5f);

    real32 length = Distance(a, b) * 0.5f;

    real32 angle = Angle(Normalize(b - a), V2(1, 0));

    if (Dot(b - a, V2(0, 1)) < 0) {
        angle *= -1;
    }


    DrawRect(c, V2(length, width), angle, color);
}


void AllocateRectBuffer(int32 capacity, RectBuffer *buffer) {
    buffer->count = 0;
    buffer->capacity = capacity;
    buffer->bufferSize = sizeof(RectRenderData) * buffer->capacity;

    buffer->data = (RectRenderData *)malloc(buffer->bufferSize);
    memset(buffer->data, 0, buffer->bufferSize);
    
    glGenBuffers(1, &buffer->bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, buffer->bufferID);
    glBufferData(GL_ARRAY_BUFFER, buffer->bufferSize, buffer->data, GL_STREAM_DRAW);
}

void DrawRect(RectBuffer *buffer, vec2 pos, vec2 scale, vec4 color) {
    RectRenderData data = {};
    data.color = color;
    data.model = TRS(V3(pos.x, pos.y, 0), IdentityQuaternion(), V3(scale.x, scale.y, 0.0f));
    
    if (buffer->count < buffer->capacity) {
        buffer->data[buffer->count++] = data;
    }
    else {
        ASSERT(false);
        // Ran out of space in the rect buffer :(
    }
}

void RenderRectBuffer(RectBuffer *buffer) {
    Mesh *mesh = &Game->quad;
    
    Shader *shader = &Game->instancedQuadShader;
    SetShader(shader);
    
    glUniformMatrix4fv(shader->uniforms[0].id, 1, GL_FALSE, Game->camera.viewProjection.data);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBufferID);

    // Position
    int vert = glGetAttribLocation(shader->programID, "vertexPosition_modelspace");
    glEnableVertexAttribArray(vert);
    glVertexAttribPointer(vert, 3, GL_FLOAT, GL_FALSE, 0, (uint8 *)0);

    int32 stride = sizeof(RectRenderData);

    glBindBuffer(GL_ARRAY_BUFFER, buffer->bufferID);
    glBufferData(GL_ARRAY_BUFFER, buffer->bufferSize, buffer->data, GL_STREAM_DRAW);

    int model = glGetAttribLocation(shader->programID, "instance_model");
    int color = glGetAttribLocation(shader->programID, "instance_color");
    
    // color
    glEnableVertexAttribArray(color);
    glVertexAttribPointer(color, 4, GL_FLOAT, GL_FALSE, stride, (uint8 *)0);
    glVertexAttribDivisor(color, 1);

    // model column 0
    glEnableVertexAttribArray(model);
    glVertexAttribPointer(model, 4, GL_FLOAT, GL_FALSE, stride, (uint8 *)0 + sizeof(vec4));
    glVertexAttribDivisor(model, 1);

    // model column 1
    glEnableVertexAttribArray(model + 1);
    glVertexAttribPointer(model + 1, 4, GL_FLOAT, GL_FALSE, stride, (uint8 *)0 + sizeof(vec4) * 2);
    glVertexAttribDivisor(model + 1, 1);

    // model column 2
    glEnableVertexAttribArray(model + 2);
    glVertexAttribPointer(model + 2, 4, GL_FLOAT, GL_FALSE, stride, (uint8 *)0 + sizeof(vec4) * 3);
    glVertexAttribDivisor(model + 2, 1);

    // model column 3
    glEnableVertexAttribArray(model + 3);
    glVertexAttribPointer(model + 3, 4, GL_FLOAT, GL_FALSE, stride, (uint8 *)0 + sizeof(vec4) * 4);
    glVertexAttribDivisor(model + 3, 1);

    glDrawElementsInstanced(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, (uint8 *)NULL + 0, buffer->count);
    
    glDisableVertexAttribArray(vert);
    glDisableVertexAttribArray(color);
    glDisableVertexAttribArray(model);
    glDisableVertexAttribArray(model + 1);
    glDisableVertexAttribArray(model + 2);
    glDisableVertexAttribArray(model + 3);
    
    glVertexAttribDivisor(vert, 0);
    glVertexAttribDivisor(color, 0);
    glVertexAttribDivisor(model, 0);
    glVertexAttribDivisor(model + 1, 0);
    glVertexAttribDivisor(model + 2, 0);
    glVertexAttribDivisor(model + 3, 0);
}



void DrawMesh(Mesh *mesh, vec3 pos, quaternion rotation, vec3 scale, vec4 color) {
    Shader *shader = &Game->shader;
    SetShader(shader);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    mat4 model = TRS(pos, rotation, scale);

    glUniformMatrix4fv(shader->uniforms[0].id, 1, GL_FALSE, model.data);
    glUniformMatrix4fv(shader->uniforms[1].id, 1, GL_FALSE, Game->camera.viewProjection.data);

    glUniform4fv(shader->uniforms[2].id, 1, color.data);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBufferID);

    // 1st attribute buffer : vertices
    int vert = glGetAttribLocation(shader->programID, "vertexPosition_modelspace");
    glEnableVertexAttribArray(vert);
    glVertexAttribPointer(vert, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        
    glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, (GLvoid *)0);

    glDisableVertexAttribArray(vert);
}


// @NOTE: only works for monospace fonts because it assumes everyone has the same dimensions.
real32 CharacterCountToWidth(FontTable *font, int32 count, real32 size) {
    char c = '-';
    int32 codepoint = c - 32;

    real32 x = 0;

    x += font->glyphs[codepoint].lowerLeft.x * size;
    x += font->glyphs[codepoint].xAdvance * size;

    return x * count;
}

// @NOTE: width is totally arbitrary until we figure out the emSize situation.
void LayoutGlyphs(FontTable *font, const char *string, int32 count, real32 size, vec2 *positions, real32 width, bool center) {
    real32 maxWidth = 0;
    
    real32 x = 0;
    real32 y = 0;
    for (int i = 0; i < count; i++) {
        char c = string[i];

        int32 codepoint = c - 32;

        // @HACK: actually figure out lineheight of font!
        if (c == '\n') {
            x = 0;
            y -= size * 1.5f; // @HACK
        }

        // @NOTE: see if we can fit the rest of the word on within the width.
        real32 tempX = x;
        int32 tempI = i;
        char tempC = string[tempI];
        while (tempC != ' ') {
            int32 tempCodepoint = tempC - 25;

            tempX += font->glyphs[tempCodepoint].lowerLeft.x * size;
            tempX += font->glyphs[tempCodepoint].xAdvance * size;

            tempC = string[++tempI];
        }

        if (tempX > width) {
            x = 0;
            y -= 1.5f;
        }

        positions[i] = V2(x, y);
        positions[i].y += font->glyphs[codepoint].lowerLeft.y * size;
        positions[i].x += font->glyphs[codepoint].lowerLeft.x * size;

        x += (font->glyphs[codepoint].xAdvance * size);

        if (x > maxWidth) {
            maxWidth = x;
        }
    }

    if (center) {
        for (int i = 0; i < count; i++) {
            positions[i].x -= maxWidth * 0.5f;
        }
    }
}


// @TODO: version of this that just takes GlyphData so we can do custom stuff like set the
// color of each glyph.
// @NOTE Its interesting that we pass in a pointer to a buffer that we allocate in here.
// On the one hand I dont like hidden allocations but frameMem makes it no hassle. The
// issue comes from the fact that we want to be able to call DrawText(format, arguments)
// which means that the caller doesnt know how long the string is.
void DrawText_(FontTable *font, vec2 pos, real32 size, vec4 color, bool screen, const char *str, real32 width, bool center, vec2 **positionsBuffer) {
    GlyphBuffer *buffer = &Game->glyphBuffers[Game->currentGlyphBufferIndex];
    buffer->screen = screen;

    buffer->font = font;
    
    int32 len = strlen(str);

    buffer->model = TRS(V3(pos.x, pos.y, 0), IdentityQuaternion(), V3(1));

    vec2 *positions = PushArray(&Game->frameMem, vec2, len);
    LayoutGlyphs(buffer->font, str, len, size, positions, width, center);

    buffer->count += len;

    for (int i = 0; i < len; i++) {
        int32 codepoint = str[i] - 32;
        
        buffer->data[i].position = positions[i];
        
        buffer->data[i].color = color;
        buffer->data[i].codepoint = codepoint;

        vec4 corners = buffer->font->texcoordsMapData[codepoint];
        buffer->data[i].dimensions = font->glyphs[codepoint].size * size;
    }

    if (positionsBuffer != NULL) {
        *positionsBuffer = positions;
    }

    Game->currentGlyphBufferIndex++;
}


void DrawText(FontTable *font, vec2 pos, real32 size, vec4 color, bool center, real32 width, const char *fmt, ...) {
    va_list args;
    va_start (args, fmt);

    // @BUG: if our string has more characters this fails!!!!
    char str[GlyphBufferCapacity];
    vsnprintf(str, PRINT_MAX_BUFFER_LEN, fmt, args);
    
    DrawText_(font, pos, size, color, false, str, width, center, NULL);

    va_end(args);
}

void DrawText(FontTable *font, vec2 pos, real32 size, vec4 color, bool center, const char *fmt, ...) {
    va_list args;
    va_start (args, fmt);
    
    char str[GlyphBufferCapacity];
    vsnprintf(str, PRINT_MAX_BUFFER_LEN, fmt, args);
    
    DrawText_(font, pos, size, color, false, str, INFINITY, center, NULL);

    va_end(args);
}


void DrawText(vec2 pos, real32 size, vec4 color, bool center, const char *fmt, ...) {
    va_list args;
    va_start (args, fmt);
    
    char str[GlyphBufferCapacity];
    vsnprintf(str, PRINT_MAX_BUFFER_LEN, fmt, args);
    
    DrawText_(&Game->monoFont, pos, size, color, false, str, INFINITY, center, NULL);

    va_end(args);
}

void DrawText(FontTable *font, vec2 pos, real32 size, vec4 color, const char *fmt, ...) {
    va_list args;
    va_start (args, fmt);
    
    char str[GlyphBufferCapacity];
    vsnprintf(str, PRINT_MAX_BUFFER_LEN, fmt, args);
    
    DrawText_(font, pos, size, color, false, str, INFINITY, false, NULL);

    va_end(args);
}

void DrawText(vec2 pos, real32 size, vec4 color, const char *fmt, ...) {
    va_list args;
    va_start (args, fmt);
    
    char str[GlyphBufferCapacity];
    vsnprintf(str, PRINT_MAX_BUFFER_LEN, fmt, args);
    
    DrawText_(&Game->monoFont, pos, size, color, false, str, INFINITY, false, NULL);

    va_end(args);
}

void DrawTextScreen(FontTable *font, vec2 pos, real32 size, vec4 color, bool center, real32 width, const char *fmt, ...) {
    va_list args;
    va_start (args, fmt);
    
    char str[GlyphBufferCapacity];
    vsnprintf(str, PRINT_MAX_BUFFER_LEN, fmt, args);

    size *= Game->screenWidth;

    pos = V2(pos.x * Game->screenWidth, (1 - pos.y) * Game->screenHeight);

    DrawText_(font, V2(pos.x, pos.y), size, color, true, str, width, center, NULL);
    
    va_end(args);
}

void DrawTextScreen(FontTable *font, vec2 pos, real32 size, vec4 color, bool center, const char *fmt, ...) {
    va_list args;
    va_start (args, fmt);
    
    char str[GlyphBufferCapacity];
    vsnprintf(str, PRINT_MAX_BUFFER_LEN, fmt, args);

    size *= Game->screenWidth;

    pos = V2(pos.x * Game->screenWidth, (1 - pos.y) * Game->screenHeight);

    DrawText_(font, V2(pos.x, pos.y), size, color, true, str, INFINITY, center, NULL);
    
    va_end(args);
}

void DrawTextScreen(vec2 pos, real32 size, vec4 color, bool center, const char *fmt, ...) {
    va_list args;
    va_start (args, fmt);
    
    char str[GlyphBufferCapacity];
    vsnprintf(str, PRINT_MAX_BUFFER_LEN, fmt, args);

    size *= Game->screenWidth;

    pos = V2(pos.x * Game->screenWidth, (1 - pos.y) * Game->screenHeight);

    DrawText_(&Game->monoFont, V2(pos.x, pos.y), size, color, true, str, INFINITY, center, NULL);
    
    va_end(args);
}

void DrawTextScreen(FontTable *font, vec2 pos, real32 size, vec4 color, const char *fmt, ...) {
    va_list args;
    va_start (args, fmt);
    
    char str[GlyphBufferCapacity];
    vsnprintf(str, PRINT_MAX_BUFFER_LEN, fmt, args);

    size *= Game->screenWidth;

    pos = V2(pos.x * Game->screenWidth, (1 - pos.y) * Game->screenHeight);

    DrawText_(font, V2(pos.x, pos.y), size, color, true, str, INFINITY, false, NULL);
    
    va_end(args);
}

void DrawTextScreen(vec2 pos, real32 size, vec4 color, const char *fmt, ...) {
    va_list args;
    va_start (args, fmt);
    
    char str[GlyphBufferCapacity];
    vsnprintf(str, PRINT_MAX_BUFFER_LEN, fmt, args);

    size *= Game->screenWidth;

    pos = V2(pos.x * Game->screenWidth, (1 - pos.y) * Game->screenHeight);

    DrawText_(&Game->monoFont, V2(pos.x, pos.y), size, color, true, str, INFINITY, false, NULL);
    
    va_end(args);
}


void DrawTextScreenPixel(FontTable *font, vec2 pos, real32 size, vec4 color, bool center, real32 width, const char *fmt, ...) {
    va_list args;
    va_start (args, fmt);
    
    char str[GlyphBufferCapacity];
    vsnprintf(str, PRINT_MAX_BUFFER_LEN, fmt, args);

    // @BUG @GACK: this height - pos.y is because we want zero vector to be top left, but
    // our projection matrix is set up so that 0 is the bottom of the screen, and changing
    // that seems to flip our glyphs...
    DrawText_(font, V2(pos.x, Game->screenHeight - pos.y), size, color, true, str, width, center, NULL);
    
    va_end(args);
}

void DrawTextScreenPixel(FontTable *font, vec2 pos, real32 size, vec4 color, bool center, const char *fmt, ...) {
    va_list args;
    va_start (args, fmt);
    
    char str[GlyphBufferCapacity];
    vsnprintf(str, PRINT_MAX_BUFFER_LEN, fmt, args);

    // @BUG @GACK: this height - pos.y is because we want zero vector to be top left, but
    // our projection matrix is set up so that 0 is the bottom of the screen, and changing
    // that seems to flip our glyphs...
    DrawText_(font, V2(pos.x, Game->screenHeight - pos.y), size, color, true, str, INFINITY, center, NULL);
    
    va_end(args);
}

void DrawTextScreenPixel(FontTable *font, vec2 pos, real32 size, vec4 color, const char *fmt, ...) {
    va_list args;
    va_start (args, fmt);
    
    char str[GlyphBufferCapacity];
    vsnprintf(str, PRINT_MAX_BUFFER_LEN, fmt, args);

    // @BUG
    // @GACK: this height - pos.y is because we want zero vector to be top left, but our projection matrix is set up
    // so that 0 is the bottom of the screen, and changing that seems to flip our glyphs...
    DrawText_(font, V2(pos.x, Game->screenHeight - pos.y), size, color, true, str, INFINITY, false, NULL);
    
    va_end(args);
}


int32 DrawTextScreenPixel(FontTable *font, vec2 pos, real32 size, vec4 color, bool center, vec2 **positionsBuffer, const char *fmt, ...) {
    va_list args;
    va_start (args, fmt);
    
    char str[GlyphBufferCapacity];
    vsnprintf(str, PRINT_MAX_BUFFER_LEN, fmt, args);

    // @BUG
    // @GACK: this height - pos.y is because we want zero vector to be top left, but our projection matrix is set up
    // so that 0 is the bottom of the screen, and changing that seems to flip our glyphs...
    DrawText_(font, V2(pos.x, Game->screenHeight - pos.y), size, color, true, str, INFINITY, center, positionsBuffer);
    
    va_end(args);

    return strlen(str);
}


void DrawGlyphs(GlyphBuffer *buffers) {
    Shader *shader = &Game->textShader;
    SetShader(shader);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (int i = 0; i < GlyphBufferCount; i++) {
        GlyphBuffer *buffer = &buffers[i];

        if (buffer->count == 0) {
            continue;
        }
        
        mat4 model = buffer->model;

        Mesh *mesh = &Game->glyphQuad;
     
        glUniformMatrix4fv(shader->uniforms[0].id, 1, GL_FALSE, model.data);

        if (buffer->screen) {
            mat4 projMat = Orthographic(0, Game->screenWidth, 0, Game->screenHeight, -1, 1);
            glUniformMatrix4fv(shader->uniforms[1].id, 1, GL_FALSE, projMat.data);
        }
        else {
            glUniformMatrix4fv(shader->uniforms[1].id, 1, GL_FALSE, Game->camera.viewProjection.data);
        }

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, buffer->font->texture.textureID);
        glUniform1i(shader->uniforms[3].id, 0);

        glActiveTexture(GL_TEXTURE0 + 1);
        glBindTexture(GL_TEXTURE_1D, buffer->font->texcoordsMapID);
        glUniform1i(shader->uniforms[2].id, 1);

        glUniform1f(shader->uniforms[4].id, Game->time);

        glBindBuffer(GL_ARRAY_BUFFER, mesh->vertBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBufferID);

        // 1st attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2,  GL_FLOAT, GL_FALSE, 0, (void*)((sizeof(vec3) * mesh->vertCount)));
    
        // Buffer the data and draw it
        glBindBuffer(GL_ARRAY_BUFFER, buffer->bufferID);
        glBufferData(GL_ARRAY_BUFFER, buffer->size, buffer->data, GL_STATIC_DRAW);

        glEnableVertexAttribArray(2);
        glVertexAttribIPointer(2, 1, GL_INT, sizeof(GlyphData), (void *)FIELD_OFFSET(GlyphData, codepoint));
        glVertexAttribDivisor(2, 1);

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, false, sizeof(GlyphData), (void *)FIELD_OFFSET(GlyphData, color));
        glVertexAttribDivisor(3, 1);

        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 2, GL_FLOAT, false, sizeof(GlyphData), (void *)FIELD_OFFSET(GlyphData, dimensions));
        glVertexAttribDivisor(4, 1);
    
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 2, GL_FLOAT, false, sizeof(GlyphData), (void *)FIELD_OFFSET(GlyphData, position));
        glVertexAttribDivisor(5, 1);

        glDrawElementsInstanced(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, (GLvoid *)0, buffer->count);
        
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);
        glDisableVertexAttribArray(4);
        glDisableVertexAttribArray(5);
    
        buffer->count = 0;
    }
}



// API interface
