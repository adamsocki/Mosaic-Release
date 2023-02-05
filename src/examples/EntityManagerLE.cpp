


void CreateEntityInLE(EntityType type)
{
	EntityHandle entityHandle = AddEntity(&Data->em, type);
	switch (type)
	{
		case EntityType_Wall:
		{
			Wall* entity = (Wall*)GetEntity(&Data->em, entityHandle);
			entity->handle = entityHandle;
			entity->modelRenderData.position = -Game->camera.pos;
			entity->modelRenderData.scale = V3(10, 10, 10);
			entity->model = Data->rm.models.wall1Model;
			entity->mesh = Game->wall1Mesh;
			break;
		}
		default:
		{
			break;
		}
	}

}