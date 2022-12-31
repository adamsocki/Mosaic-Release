#version 330 core


in vec2 texcoord;

uniform sampler2D texture0;
uniform float time;

out vec4 color;

void main(void){
	vec2 uv = texcoord;
   
    vec4 textureContrib = texture(texture0, uv).rgba;
    
    color.rgba = textureContrib;
}

