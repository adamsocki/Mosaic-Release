


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
			entity->modelRenderData.rotation = IdentityQuaternion();
			//entity->model = Data->rm.models.wall1Model;
			entity->mesh = Game->wall1Mesh;
			break;
		}
		case EntityType_Post:
		{
			/*Post* entity = (Post*)GetEntity(&Data->em, entityHandle);
			entity->handle = entityHandle;
			entity->modelRenderData.position = -Game->camera.pos;
			entity->modelRenderData.scale = V3(2, 2, 2);
			entity->model = Data->rm.models.wall1Model;
			entity->mesh = Game->postMesh;*/
			break;
		}
		case EntityType_Door:
		{
			Door* entity = (Door*)GetEntity(&Data->em, entityHandle);
			entity->handle = entityHandle;
			entity->modelRenderData.position = -Game->camera.pos;
			entity->modelRenderData.scale = V3(10, 10, 10);
			entity->modelRenderData.rotation = IdentityQuaternion();
			entity->modelRenderData.sprite = Data->sprites.door_greenTexture;
			//entity->model = Data->rm.models.doorModel;
			entity->mesh = Game->doorMesh;
			break;
		}

		default:
		{
			break;
		}
	}

}