#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 in_texcoord;
layout(location = 2) in vec3 normals;

uniform mat4 model;
uniform mat4 viewProjection;
uniform vec3 lightPosition;

out vec2 texcoord;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;

void main() {
    vec4 worldVert4 = model * vec4(vertexPosition_modelspace, 1.0f);
    vec3 worldVert = worldVert4.xyz;
    
    gl_Position = viewProjection * model * vec4(vertexPosition_modelspace, 1.0f);

	texcoord = in_texcoord;

	surfaceNormal = (model * vec4(normals, 0.0)).xyz;
	toLightVector = lightPosition - worldVert;
	toCameraVector = (inverse(viewProjection) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldVert;
}

