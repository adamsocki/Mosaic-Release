



void GetModelsFromEntities(DynamicArray<EntityHandle> entitiyHandleArray)
{
	
	

}


void DrawOBJModels(Entity entity, DynamicArray<TransformMatrixModelData> entityTransform, Light light ,OBJMesh* mesh, Sprite* texture, Shader* shader)
{
   // Shader* shader = &Game->modelShader;
    SetShader(shader);

    real32 shineDamper = 1;
    real32 reflectivity = 0;

    //glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);

    // Mesh* mesh = &Game->quad;
    
    glUniformMatrix4fv(shader->uniforms[1].id, 1, GL_FALSE, Game->camera.viewProjection.data);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->textureID);
    glUniform1i(shader->uniforms[2].id, 0);

    glUniform1fv(shader->uniforms[3].id, 1, &Game->time);
    glUniform3fv(shader->uniforms[4].id, 1, light.position.data);
    glUniform3fv(shader->uniforms[5].id, 1, light.color.data);
    glUniform1fv(shader->uniforms[6].id, 1, &shineDamper);
    glUniform1fv(shader->uniforms[7].id, 1, &reflectivity);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBufferID);

    // 1st attribute buffer : vertices
    int vert = glGetAttribLocation(shader->programID, "vertexPosition_modelspace");
    glEnableVertexAttribArray(vert);
    glVertexAttribPointer(vert, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // 2nd attribute buffer : texcoords
    int texcoord = glGetAttribLocation(shader->programID, "in_texcoord");
    glEnableVertexAttribArray(texcoord);
    glVertexAttribPointer(texcoord, 2, GL_FLOAT, GL_FALSE, 0, (void*)((sizeof(real32) * mesh->vertCount)));

    // 3nd attribute buffer : normals
    int normals = glGetAttribLocation(shader->programID, "normals");
    glEnableVertexAttribArray(normals);
    glVertexAttribPointer(normals, 3, GL_FLOAT, GL_FALSE, 0, (void*)((sizeof(real32) * mesh->vertCount) + (sizeof(real32) * mesh->texcoordsCount)));
    //  stbi_set_flip_vertically_on_load(true);



    for (int i = 0; i < entityTransform.count; i++)
    {
    
        
        mat4 model = TRS(entityTransform[i].position, AxisAngle(V3(0, 1, 0), entityTransform[i].angle), entityTransform[i].scale);

        glUniformMatrix4fv(shader->uniforms[0].id, 1, GL_FALSE, model.data);
        glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, (GLvoid*)0);
    
    }

    glDisableVertexAttribArray(vert);
    glDisableVertexAttribArray(texcoord);
    glDisableVertexAttribArray(normals);

}