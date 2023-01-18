



void InitMousePicker()
{
	Data->mousePicker = {};
	Data->mousePicker.mouseData = Data->mouse;
	Data->mousePicker.cam = &Game->camera;
	Data->mousePicker.projectionMatrix = &Game->camera.projection;
	Data->mousePicker.viewMatrix = &Game->camera.view;
}

vec2 CalculateMouseRay(MouseData mouseData)
{
	vec2 mouse = {};
	mouse.x = mouseData.posOnWindow.x;
	mouse.y = mouseData.posOnWindow.y;
	// normalize to opengl pos
	vec2 normalizedMouse = {};
	normalizedMouse.x = (2.0f * mouse.x) / Game->screenWidth - 1.0f;
	normalizedMouse.y = (2.0f * mouse.y) / Game->screenHeight - 1.0f;
	normalizedMouse.y = -normalizedMouse.y;
	vec4 clipCoords = V4(normalizedMouse.x, normalizedMouse.y, -1.0f, 1.0f);
	
	mat4 invertedProjection = invert(Game->camera.projection);
	vec4 eyeCoords = transform(invertedProjection, clipCoords);

	eyeCoords.x = eyeCoords.x;
	eyeCoords.y = eyeCoords.y;
	eyeCoords.z = -1.0f;
	eyeCoords.w = 0.0f;
	
	//return normalizedMouse;
}


vec4 toEyeCoords(vec4 clipCoords)
{
	 
}

void UpdateMousePicker()
{
	Data->mousePicker.mouseData = Data->mouse;
	Data->mousePicker.viewMatrix = &Game->camera.view;
	Data->mousePicker.mouseRay = CalculateMouseRay(Data->mouse);

	


}