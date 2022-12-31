#version 330 core

in vec2 texcoord;
in vec3 surfaceNormal;
in vec3 toLightVector;

uniform sampler2D texture0;
uniform float time;
uniform vec3 lightColor;
uniform float shineDamper;
uniform float reflectivity;

out vec4 color;

void main(void){
	vec2 uv = texcoord;
   
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(toLightVector);
	
	float nDot1 = dot (unitNormal, unitLightVector);
	float brightness = max(nDot1, 0.0);
	vec3 diffuse = brightness * lightColor;
   
    vec4 textureContrib = texture(texture0, uv).rgba;
    
    color.rgba = vec4(diffuse, 1.0) * textureContrib;
}