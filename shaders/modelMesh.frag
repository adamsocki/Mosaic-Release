#version 330 core

in vec2 texcoord;
in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCameraVector;
in float visibility;

uniform sampler2D texture0;
uniform float time;
uniform vec3 lightColor;
uniform float shineDamper;
uniform float reflectivity;
uniform vec3 skyColor;

out vec4 color;

void main(void){
	vec2 uv = texcoord;
   
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(toLightVector);
	
	float nDot1 = dot (unitNormal, unitLightVector);
	float brightness = max(nDot1, 0.2);
	vec3 diffuse = brightness * lightColor;
	
	
	vec3 unitVectorToCamera = normalize(toCameraVector);
	vec3 lightDirection = -unitLightVector;
	vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);
	
	float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);
	specularFactor = max(specularFactor, 0.0);
	float damperFactor = pow(specularFactor, shineDamper);
	vec3 finalSpecular = damperFactor * reflectivity * lightColor;
	
    vec4 textureContrib = texture(texture0, uv).rgba;
    if (textureContrib.a < 0.5)
    {
    	discard;
    }
	

    color.rgba = vec4(diffuse, 1.0) * textureContrib + vec4(finalSpecular, 1.0);
	color.rgba = mix(vec4(skyColor, 1.0), color.rgba, visibility);
}