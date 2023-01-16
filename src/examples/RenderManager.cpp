
void GetModelsFromEntities(DynamicArray<EntityHandle> entitiyHandleArray)
{
}

void DrawOBJModels(DynamicArray<ModelRenderData> modelRenderData, Light light ,OBJMesh* mesh, Sprite* texture, Shader* shader)
{
    SetShader(shader);

    real32 shineDamper = 1;
    real32 reflectivity = 0;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    glUniformMatrix4fv(shader->uniforms[1].id, 1, GL_FALSE, Game->camera.viewProjection.data);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->textureID);
    glUniform1i(shader->uniforms[2].id, 0);

    glUniform1fv(shader->uniforms[3].id, 1, &Game->time);
    glUniform3fv(shader->uniforms[4].id, 1, light.position.data);
    glUniform3fv(shader->uniforms[5].id, 1, light.color.data);
    glUniform1fv(shader->uniforms[6].id, 1, &shineDamper);
    glUniform1fv(shader->uniforms[7].id, 1, &reflectivity);
    glUniformMatrix4fv(shader->uniforms[9].id, 1, GL_FALSE, Game->camera.view.data);
    glUniformMatrix4fv(shader->uniforms[10].id, 1, GL_FALSE, Game->camera.projection.data);
    glUniform3fv(shader->uniforms[11].id, 1, Data->rm.skyColor.data);

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
    
    for (int i = 0; i < modelRenderData.count; i++)
    {
        mat4 model = TRS(modelRenderData[i].position, AxisAngle(V3(0, 1, 0), modelRenderData[i].rotY), modelRenderData[i].scale);
        if(modelRenderData[i].hasTransparency)
        {
            glDisable(GL_CULL_FACE);
        }
        else
        {
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
        }
        glUniform1f(shader->uniforms[8].id, modelRenderData[i].modifiedLighting);
        glUniformMatrix4fv(shader->uniforms[0].id, 1, GL_FALSE, model.data);
        glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, (GLvoid*)0);
    }

    glDisableVertexAttribArray(vert);
    glDisableVertexAttribArray(texcoord);
    glDisableVertexAttribArray(normals);
}