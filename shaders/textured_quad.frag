
#version 330 core

in vec2 texcoord;

uniform sampler2D texture0;
uniform float time;

out vec4 color;

void main() {
   
    
    vec4 textureContrib = texture(texture0, texcoord).rgba;
    
    color.rgba = textureContrib;

}
