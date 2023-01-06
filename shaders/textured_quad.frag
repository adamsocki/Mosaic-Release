
#version 330 core

in vec2 texcoord;

uniform sampler2D texture0;
uniform float time;
uniform float transparency;

out vec4 color;

void main() {
   
    
    vec4 textureContrib = texture(texture0, texcoord).rgba;
    
	vec4 transparencyVec = vec4(0.0,0.0,0.0,transparency);
    color.rgba = textureContrib - transparencyVec;

}
