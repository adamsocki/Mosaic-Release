


void InitMouse()
{
	vec2 mousePos = Input->mousePosNormSigned;
	mousePos.x = (mousePos.x + 1.0f) * Game->screenWidth / 2;
	mousePos.y = (-mousePos.y + 1.0f) * Game->screenHeight / 2;
	Data->mouse.positionPixel = mousePos;
	Data->mouse.rect.max = V2(0.125f, 0.125f);
	Data->mouse.rect.min = -V2(0.125f, 0.125f);
}

void UpdateMouseData()
{
	vec2 mousePos = Input->mousePosNormSigned;
	mousePos.x = (mousePos.x + 1.0f) * Game->screenWidth / 2;
	mousePos.y = (-mousePos.y + 1.0f) * Game->screenHeight / 2;
	Data->mouse.positionPixel = mousePos;
	Data->mouse.positionPixel_delta.x = Data->mouse.positionPixel.x - Data->mouse.positionPixel_prev.x;
	Data->mouse.positionPixel_delta.y = Data->mouse.positionPixel.y - Data->mouse.positionPixel_prev.y;
	Data->mouse.positionPixel_prev = mousePos;
	DrawSpriteScreen(mousePos, V2(20, 20), 0, 0, &Data->sprites.cursor_red);
}

void InitMousePicker()
{
	Data->mousePicker = {};
	Data->mousePicker.mouseData = Data->mouse;
	Data->mousePicker.cam = &Game->camera;
	Data->mousePicker.projectionMatrix = Game->camera.projection;
	Data->mousePicker.viewMatrix = Game->camera.view;
	Data->mousePicker.isEntitySelected = false;
}

//vec3 toWorldCoords(vec4 eyeCoord)
//{
//	mat4 invertedView = invert(Data->mousePicker.viewMatrix);
//	vec4 rayWorld = transform(invertedView, eyeCoord);
//	vec3 mouseRay = V3(rayWorld.x, rayWorld.y, rayWorld.z);
//	mouseRay = Normalize(mouseRay);
//	return mouseRay;
//}
//
//vec4 toEyeCoords(vec4 clipCoords)
//{
//	mat4 invertedProjection = invert(Game->camera.projection);
//	vec4 eyeCoords = transform(invertedProjection, clipCoords);
//
//
//	eyeCoords.x = eyeCoords.x;
//	eyeCoords.y = eyeCoords.y;
//	eyeCoords.z = -1.0f;
//	eyeCoords.w = 0.0f;
//	return eyeCoords;
//}
//
//vec2 getNormalizedDeviceCoords()
//{
//	vec2 mouse = {};
//	mouse.x = Data->mouse.positionFromInput.x;
//	mouse.y = Data->mouse.positionFromInput.y;
//	// normalize to opengl pos
//	vec2 normalizedMouse = {};
//	normalizedMouse.x = (2.0f * mouse.x) / Game->screenWidth - 1.0f;
//	normalizedMouse.y = (2.0f * mouse.y) / Game->screenHeight - 1.0f;
//	normalizedMouse.y = -normalizedMouse.y;
//	return normalizedMouse;
//}
//
//vec3 CalculateMouseRay(MouseData mouseData)
//{
//	vec2 normalizedCoords = getNormalizedDeviceCoords();
//	vec4 clipCoords = V4(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
//	vec4 eyeCoords = toEyeCoords(clipCoords);
//	vec3 worldRay = toWorldCoords(eyeCoords);
//	
//	return worldRay;
//}
//
//
//vec3 getPointOnRay(vec3 ray, real32 distance)
//{
//	vec3 camPos = Game->camera.pos;
//	vec3 start = camPos;
//	vec3 scaledRay = V3(ray.x * distance, ray.y * distance, ray.z * distance);
//
//	return start + scaledRay;
//}
//
//vec3 binarySearch(int32 count, real32 start, real32 finish, vec3 ray) {
//	int32 RECURSION_COUNT = 200;
//	real32 half = start + ((finish - start) / 2f);
//	if (count >= RECURSION_COUNT) {
//		vec3 endPoint = getPointOnRay(ray, half);
//		Terrain terrain = getTerrain(endPoint.getX(), endPoint.getZ());
//		if (terrain != null) {
//			return endPoint;
//		}
//		else {
//			return NULL;
//		}
//	}
//	if (intersectionInRange(start, half, ray)) {
//		return binarySearch(count + 1, start, half, ray);
//	}
//	else {
//		return binarySearch(count + 1, half, finish, ray);
//	}
//}
//
//bool isHittingTerrain(vec3 testPoint, Terrain terrain)
//{
//	if (testPoint.x > terrain->terrainWidth || textPoint.y > terrain->terrainWidth)
//	{
//		return false;
//	}
//	else
//	{
//		return true;
//	}
//}
//
//
//bool isUnderGround(vec3 testPoint, Terrain terrain) {
//	bool inTerrain = isHittingTerrain(testPoint.x, testPoint.z);
//	
//	real32 height = 0;
//	if (inTerrain) {
//		height = getHeightOfTerrain(testPoint.x, testPoint.x, terrain);
//	}
//
//	if (testPoint.y < height) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}
//
//bool intersectionInRange(float start, float finish, vec3 ray, Terrain terrain) {
//	vec3 startPoint = getPointOnRay(ray, start);
//	vec3 endPoint = getPointOnRay(ray, finish);
//	if (!isUnderGround(startPoint, terrain) && isUnderGround(endPoint, terrain)) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}





void UpdateMousePicker()
{
	real32 RAY_RANGE = 600;
	Data->mousePicker.mouseData = Data->mouse;
	Data->mousePicker.viewMatrix = Game->camera.view;

	// STEP 0 - 2D Viewport Coordinates (Mouse Coordinates on Screen)
	vec2 mouse = {};
	mouse.x = Data->mouse.positionPixel.x;
	mouse.y = Data->mouse.positionPixel.y;
	// STEP 1 - 3D Normalized Device Coordinates (-1, 1) for x,y,z
	real32 x = 1.0f - (2.0f * mouse.x) / Game->screenWidth;
	real32 y = (2.0f * mouse.y) / Game->screenHeight - 1.0f;
	real32 z = 1.0f;
	vec3 ray_nds = V3(x, y, z);
	// STEP 2 - 4D Homogenous Clip Coordinates
	vec4 ray_clip = V4(ray_nds.x, ray_nds.y, -1.0f, 1.0f);
	// STEP 3 - 4D Eye (Camera) Coordinates
	vec4 ray_eye = invert(Game->camera.projection) * ray_clip;
	ray_eye = V4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);
	// STEP 4 - 4D World Coordinates
	vec4 rayEye_view = invert(Game->camera.view) * ray_eye;
	vec3 ray_wor = V3(rayEye_view.x, rayEye_view.y, rayEye_view.z);
	ray_wor = Normalize(ray_wor);



	Data->mousePicker.mouseRay = ray_wor;

	DrawTextScreenPixel(&Game->serifFont, V2(300, 210), 10, V4(1, 1, 1, 1), false, "raypos.x %2f", ray_wor.x);
	DrawTextScreenPixel(&Game->serifFont, V2(300, 240), 10, V4(1, 1, 1, 1), false, "raypos.y %2f", ray_wor.y);
	DrawTextScreenPixel(&Game->serifFont, V2(300, 270), 10, V4(1, 1, 1, 1), false, "raypos.z %2f", ray_wor.z);
	
	
	// STEP 1

	/*Data->mousePicker.mouseRay = CalculateMouseRay(Data->mouse);
	if (intersectionInRange(0, RAY_RANGE, Data->mousePicker.mouseRay, *terrain))
	{
		terrain->currentTerrainPointOnMouse = binarySearch(0, 0, RAY_RANGE, Data->mousePicker.mouseRay);
	}
	else
	{
		terrain->currentTerrainPointOnMouse = NULL;
	}*/

	/*Print("MouseRay.x: %2f", Data->mousePicker.mouseRay.x);
	Print("MouseRay.y: %2f", Data->mousePicker.mouseRay.y);
	Print("MouseRay.z: %2f", Data->mousePicker.mouseRay.z);*/
}


void InitMouse_LE()
{

}

void LogicMouse_LE()
{

}

void RenderMouse_LE()
{

}







void MouseToObjectCollision(Entity* entity)
{
    real32 distanceForRay = -500.0f;

    real32 intersection_distance;
    mat4 ModelMatrix = TRS(entity->modelRenderData.position, Identity4(), entity->modelRenderData.scale.x);
    vec3 scaledRayPos = V3(Data->mousePicker.mouseRay.x * distanceForRay, Data->mousePicker.mouseRay.y * distanceForRay, Data->mousePicker.mouseRay.z * distanceForRay);

    vec3 aabb_max = {};
    aabb_max.x = entity->modelRenderData.position.x + (entity->mesh.maxAABB.x * entity->modelRenderData.scale.x);
    aabb_max.y = entity->modelRenderData.position.y + (entity->mesh.maxAABB.y * entity->modelRenderData.scale.y);
    aabb_max.z = entity->modelRenderData.position.z + (entity->mesh.maxAABB.z * entity->modelRenderData.scale.z);

    vec3 aabb_min = {};
    aabb_min.x = entity->modelRenderData.position.x + (entity->mesh.minAABB.x * entity->modelRenderData.scale.x);
    aabb_min.y = entity->modelRenderData.position.y + (entity->mesh.minAABB.y * entity->modelRenderData.scale.y);
    aabb_min.z = entity->modelRenderData.position.z + (entity->mesh.minAABB.z * entity->modelRenderData.scale.z);

    vec3 aabbSize = {};
    aabbSize = aabb_max - aabb_min;
    entity->modelRenderData.aabb_min = aabb_min;
    entity->modelRenderData.aabbSize = aabbSize;

    if (TestRayOBBIntersection(-Game->camera.pos, scaledRayPos, aabb_min, aabb_max, Identity4(), &intersection_distance) && !Data->mousePicker.isEntitySelected)
    {
        real32 distanceToEntity = Distance(-Game->camera.pos, entity->modelRenderData.position);
        if (distanceToEntity < Data->mousePicker.shortestDistanceToEntityOnRay)
        {
            goto Advance;
        }
        
        
        
        Data->mousePicker.shortestDistanceToEntityOnRay = distanceToEntity;

        
        DrawAABB(entity->modelRenderData.position, IdentityQuaternion(), V3(0.25f, 0.25f, 0.25f), V4(0.5f, 0.5f, 0.25f, 1.0), true);
        //entity->editorMode = fixed_EditorMode;
        entity->modelRenderData.isMouseOver = true;
        //bool xMode = false;

        if (InputHeld(Mouse, Input_MouseLeft))
        {
            entity->modelRenderData.isSelected = true;
            entity->modelRenderData.aabbColor = V4(0.0f, 1.0f, 0.0f, 1.0f);
            // TODO: Calculate distance from mouseRay.origin to object Position
            // entity->modelRenderData.position = 
        }
        else
        {
            entity->modelRenderData.aabbColor = V4(1);
            entity->modelRenderData.isSelected = false;
        }


        entity->modelRenderData.sprite = Data->sprites.wall1Texture;
    }
    else
    {
        entity->modelRenderData.isMouseOver = false;
        entity->modelRenderData.sprite = Data->sprites.wall1Texture;
    }

    if (entity->modelRenderData.isMouseOver && !entity->modelRenderData.isSelected)
    {
        DrawAABB(aabb_min, IdentityQuaternion(), aabbSize, entity->modelRenderData.aabbColor, true);
    }

    if (entity->modelRenderData.isSelected)
    {
        // first choose editorMode

        // TODO Send entity handle & type to Level Editor
        Data->le.ep.selectedEntityHandle = entity->handle;


        if (InputPressed(Keyboard, Input_1))
        {
            entity->editorMode = posMode;
        }
        if (InputPressed(Keyboard, Input_2))
        {
            entity->editorMode = rotMode;
        }
        if (InputPressed(Keyboard, Input_3))
        {
            entity->editorMode = scaleMode;
        }
        if (InputPressed(Keyboard, Input_Tick))
        {
            entity->editorMode = fixed_EditorMode;
        }


        if (InputHeld(Keyboard, Input_X))
        {
            entity->axisMode = xAxisMode;
        }
        if (InputHeld(Keyboard, Input_Y))
        {
            entity->axisMode = yAxisMode;
        }
        if (InputHeld(Keyboard, Input_Z))
        {
            entity->axisMode = zAxisMode;
        }

        switch (entity->editorMode)
        {
        case posMode:
        {
            switch (entity->axisMode)
            {
            case fixed_EditorMode:
            {
                break;
            }
            case xAxisMode:
            {
                entity->modelRenderData.position.x += -Data->mouse.positionPixel_delta.x * 0.1f;
                DrawLine(V3(-10000.0f, entity->modelRenderData.position.y, entity->modelRenderData.position.z), V3(20000.0f, 0.05f, 0.05f), V4(1.0f, 0.0f, 0.0f, 1.0f));
                break;
            }
            case yAxisMode:
            {
                entity->modelRenderData.position.y += -Data->mouse.positionPixel_delta.x * 0.1f;
                DrawLine(V3(entity->modelRenderData.position.x, -10000.0f, entity->modelRenderData.position.z), V3(0.05f, 20000.0f, 0.05f), V4(0.0f, 1.0f, 0.0f, 1.0f));
                break;
            }
            case zAxisMode:
            {
                entity->modelRenderData.position.z += -Data->mouse.positionPixel_delta.x * 0.1f;
                DrawLine(V3(entity->modelRenderData.position.x, entity->modelRenderData.position.y, -10000.0f), V3(0.05f, 0.05f, 20000.0f), V4(0.0f, 0.0f, 1.0f, 1.0f));
                break;
            }
            default:
            {
                break;
            }
            }
            break;
        }
        case rotMode:
        {
            // TODO Add this for rotation
            break;
        }
        case scaleMode:
        {
            switch (entity->axisMode)
            {
            case fixed_EditorMode:
            {
                break;
            }
            case xAxisMode:
            {
                entity->modelRenderData.scale.x += -Data->mouse.positionPixel_delta.x * 0.1f;
                DrawLine(V3(-10000.0f, entity->modelRenderData.position.y, entity->modelRenderData.position.z), V3(20000.0f, 0.05f, 0.05f), V4(1.0f, 0.0f, 0.0f, 1.0f));
                break;
            }
            case yAxisMode:
            {
                entity->modelRenderData.scale.y += -Data->mouse.positionPixel_delta.x * 0.1f;
                DrawLine(V3(entity->modelRenderData.position.x, -10000.0f, entity->modelRenderData.position.z), V3(0.05f, 20000.0f, 0.05f), V4(0.0f, 1.0f, 0.0f, 1.0f));
                break;
            }
            case zAxisMode:
            {
                entity->modelRenderData.scale.z += -Data->mouse.positionPixel_delta.x * 0.1f;
                DrawLine(V3(entity->modelRenderData.position.x, entity->modelRenderData.position.y, -10000.0f), V3(0.05f, 0.05f, 20000.0f), V4(0.0f, 0.0f, 1.0f, 1.0f));
                break;
            }
            default:
            {
                break;
            }
            }
            break;
        }
            default:
            {
                break;
            }
        }


        if (InputReleased(Mouse, Input_X) || InputReleased(Mouse, Input_Y) || InputReleased(Mouse, Input_Z))
        {
            entity->axisMode = fixed_AxisMode;
        }

        if (InputReleased(Mouse, Input_MouseLeft))
        {
            Data->mousePicker.isEntitySelected = false;
            entity->modelRenderData.isSelected = false;
        }
        DrawAABB(aabb_min, IdentityQuaternion(), aabbSize, entity->modelRenderData.aabbColor, true);

    }
Advance:
    int32 value;
}