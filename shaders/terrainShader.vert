#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 in_texcoord;
layout(location = 2) in vec3 normals;

uniform mat4 model;uniform mat4 view;
uniform mat4 projection;
uniform mat4 viewProjection;
uniform vec3 lightPosition;
uniform float modifiedLighting;

out vec2 texcoord;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;
out float visibility;

const float density = 0.007;
const float gradient = 1.5;

void main() {
    vec4 worldVert4 = model * vec4(vertexPosition_modelspace, 1.0f);
    vec3 worldVert = worldVert4.xyz;
    vec4 positionRelativeToCamera = view * worldVert4;
    gl_Position = projection * positionRelativeToCamera;

	texcoord = in_texcoord * 40.0;


	vec3 actualNormal = normals;
	if (modifiedLighting > 0.5)
	{	
		actualNormal = vec3(0.0, 1.0, 0.0);
	}
	
	surfaceNormal = (model * vec4(actualNormal, 0.0)).xyz;
	toLightVector = lightPosition - worldVert;
	toCameraVector = (inverse(view) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldVert;
	
	float distance = length(positionRelativeToCamera.xyz);
	visibility = exp(-pow((distance * density), gradient));
	visibility = clamp(visibility, 0.0, 1.0);
}

