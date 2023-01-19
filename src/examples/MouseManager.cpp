void InititalizeMouse()
{
	Data->mouse.positionFromInput = Input->mousePosNormSigned;
	Data->mouse.rect.max = V2(0.125f, 0.125f);
	Data->mouse.rect.min = -V2(0.125f, 0.125f);
}

void UpdateMouseData()
{
	vec2 mousePos = Input->mousePosNormSigned;
	mousePos.x = (mousePos.x + 1.0f) * Game->screenWidth / 2;
	mousePos.y = (-mousePos.y + 1.0f) * Game->screenHeight / 2;

	Data->mouse.positionFromInput = mousePos;

	Data->mouse.positionFromInput_delta.x = Data->mouse.positionFromInput.x - Data->mouse.positionFromInput_prev.x;
	Data->mouse.positionFromInput_delta.y = Data->mouse.positionFromInput.y - Data->mouse.positionFromInput_prev.y;
	Data->mouse.positionFromInput_prev = mousePos;
	DrawSpriteScreen(mousePos, V2(20, 20), 0, 0, &Data->sprites.cursor_red);

}

void InitMousePicker()
{
	Data->mousePicker = {};
	Data->mousePicker.mouseData = Data->mouse;
	Data->mousePicker.cam = &Game->camera;
	Data->mousePicker.projectionMatrix = Game->camera.projection;
	Data->mousePicker.viewMatrix = Game->camera.view;
}

vec3 toWorldCoords(vec4 eyeCoord)
{
	mat4 invertedView = invert(Data->mousePicker.viewMatrix);
	vec4 rayWorld = transform(invertedView, eyeCoord);
	vec3 mouseRay = V3(rayWorld.x, rayWorld.y, rayWorld.z);
	mouseRay = Normalize(mouseRay);
	return mouseRay;
}

vec4 toEyeCoords(vec4 clipCoords)
{
	mat4 invertedProjection = invert(Game->camera.projection);
	vec4 eyeCoords = transform(invertedProjection, clipCoords);


	eyeCoords.x = eyeCoords.x;
	eyeCoords.y = eyeCoords.y;
	eyeCoords.z = -1.0f;
	eyeCoords.w = 0.0f;
	return eyeCoords;
}

vec2 getNormalizedDeviceCoords()
{
	vec2 mouse = {};
	mouse.x = Data->mouse.positionFromInput.x;
	mouse.y = Data->mouse.positionFromInput.y;
	// normalize to opengl pos
	vec2 normalizedMouse = {};
	normalizedMouse.x = (2.0f * mouse.x) / Game->screenWidth - 1.0f;
	normalizedMouse.y = (2.0f * mouse.y) / Game->screenHeight - 1.0f;
	normalizedMouse.y = -normalizedMouse.y;
	return normalizedMouse;
}

vec3 CalculateMouseRay(MouseData mouseData)
{
	vec2 normalizedCoords = getNormalizedDeviceCoords();
	vec4 clipCoords = V4(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
	vec4 eyeCoords = toEyeCoords(clipCoords);
	vec3 worldRay = toWorldCoords(eyeCoords);
	
	return worldRay;
}


vec3 getPointOnRay(vec3 ray, real32 distance)
{
	vec3 camPos = Game->camera.pos;
	vec3 start = camPos;
	vec3 scaledRay = V3(ray.x * distance, ray.y * distance, ray.z * distance);

	return start + scaledRay;
}

//vec3 binarySearch(int32 count, real32 start, real32 finish, vec3 ray)
//{
//	int32 RECURSION_COUNT = 200;
//
//	real32 half = start + ((finish - start) / 2.0f);
//	if (count >= RECURSION_COUNT)
//	{
//		vec3 enPoint = getPointOnRay(ray, half);
//
//	}
//}

//bool isUnderGround(vec3 testPoint) {
//	Terrain terrain = getTerrain(testPoint.getX(), testPoint.getZ());
//	real32 height = 0;
//	if (terrain != null) {
//		height = terrain.getHeightOfTerrain(testPoint.getX(), testPoint.getZ());
//	}
//	if (testPoint.y < height) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}

//bool intersectionInRange(float start, float finish, vec3 ray) {
//	vec3 startPoint = getPointOnRay(ray, start);
//	vec3 endPoint = getPointOnRay(ray, finish);
//	if (!isUnderGround(startPoint) && isUnderGround(endPoint)) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}

void UpdateMousePicker()
{
	Data->mousePicker.mouseData = Data->mouse;
	Data->mousePicker.viewMatrix = Game->camera.view;
	Data->mousePicker.mouseRay = CalculateMouseRay(Data->mouse);
	/*if (intersectionInRange(0, RAY_RANGE, Data->mousePicker.mouseRay))
	{
		
	}*/

	Print("MouseRay.x: %2f", Data->mousePicker.mouseRay.x);
	Print("MouseRay.y: %2f", Data->mousePicker.mouseRay.y);
	Print("MouseRay.z: %2f", Data->mousePicker.mouseRay.z);
	
	


}