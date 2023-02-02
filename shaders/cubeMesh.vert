#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 color;

out vec4 fs_color;

void main() {
    vec4 worldVert4 = model * vec4(vertexPosition_modelspace, 1.0f);
    vec3 worldVert = worldVert4.xyz;
    
	vec4 positionRelativeToCamera = view * worldVert4;
	
	
    gl_Position = projection * positionRelativeToCamera;
	
    fs_color = color;
}

