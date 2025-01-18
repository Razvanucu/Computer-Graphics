#version 410 core

in vec3 fPosition;
in vec3 fNormal;
in vec2 fTexCoords;
in vec4 fragPosLightSpace;
out vec4 fColor;

//matrices
uniform mat4 model;
uniform mat4 view;
uniform mat3 normalMatrix;

//directional lighting
uniform vec3 lightDir;
uniform vec3 lightColor;

//point light
uniform vec3 lightPos;
uniform vec3 cameraPosEye;
uniform float constantAttenuation;
uniform float linearAttenuation;
uniform float quadraticAttenuation;


//spot light
uniform vec3 spotLightPos;
uniform vec3 spotLightDir;
uniform float innerCutOff;
uniform float outerCutOff;
uniform int ifSpotLight;

//shadow
uniform sampler2D shadowMap;

// textures
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

//components
vec3 ambient;
float ambientStrength = 0.2f;
vec3 diffuse;
vec3 specular;
float specularStrength = 0.5f;

void computeDirLight()
{
    //compute eye space coordinates
    vec4 fPosEye = view * model * vec4(fPosition, 1.0f);
    vec3 normalEye = normalize(normalMatrix * fNormal);

    //normalize light direction
    vec3 lightDirN = vec3(normalize(view * vec4(lightDir, 0.0f)));

    //compute view direction (in eye coordinates, the viewer is situated at the origin
    vec3 viewDir = normalize(- fPosEye.xyz);

    //compute ambient light
    ambient = ambientStrength * lightColor;

    //compute diffuse light
    diffuse = max(dot(normalEye, lightDirN), 0.0f) * lightColor;

    //compute specular light
    vec3 reflectDir = reflect(-lightDirN, normalEye);
    float specCoeff = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
    specular = specularStrength * specCoeff * lightColor;
}

vec3 ambientPoint;
float ambientStrengthPoint = 0.8f;
vec3 diffusePoint;
vec3 specularPoint;
float specularStrengthPoint = 0.1f;
float shininess = 100.0f;

void computePointLight(){	
	//transform normal
    vec4 fPosEye = view * model * vec4(fPosition, 1.0f);
	vec3 normalEye = normalize(fNormal);	
	
	//compute light direction
	vec3 lightDirN = normalize(lightPos - fPosEye.xyz);
	
	//compute view direction 
	vec3 viewDirN = normalize(cameraPosEye - fPosEye.xyz);
		
	//compute ambient light
	ambientPoint = ambientStrengthPoint * lightColor;
	
	//compute diffuse light
	diffusePoint = max(dot(normalEye, lightDirN), 0.0f) * lightColor;
	
	//compute specular light
	vec3 reflection = reflect(-lightDirN, normalEye);
	float specCoeff = pow(max(dot(viewDirN, reflection), 0.0f), shininess);
	specularPoint = specularStrengthPoint * specCoeff * lightColor;

	float distance    = length(lightPos - fPosEye.xyz);
	float attenuation = 1.0 / (constantAttenuation +  linearAttenuation * distance + quadraticAttenuation * (distance * distance));

	ambientPoint *= attenuation;
	specularPoint *= attenuation;
	diffusePoint *= attenuation;
}

vec3 ambientSpotLight;
float ambientStrengthSpotLight = 0.1f;
vec3 diffuseSpotLight;
vec3 specularSpotLight;
float specularStrengthSpotLight = 0.2f;

void computeSpotLight(){
    
    vec4 fPosEye = view * model * vec4(fPosition, 1.0f);
    vec3 lightDirN = normalize(vec3(spotLightPos - fPosEye.xyz ));
    float theta = dot(lightDirN, normalize(-spotLightDir));
    
    if(theta > innerCutOff) {       

        ambientSpotLight = ambientStrengthSpotLight * vec3(0.4f,0.4f,0.4f);
        
        vec3 normalEye = normalize(fNormal);
        diffuseSpotLight = max(dot(normalEye, lightDirN), 0.0f) * lightColor;

        vec3 viewDirN = normalize(cameraPosEye - fPosEye.xyz);
        vec3 reflection = reflect(-lightDirN, normalEye);
        float specCoeff = pow(max(dot(viewDirN, reflection), 0.0f), shininess);
        specularSpotLight = specularStrengthPoint * specCoeff * lightColor;

        float epsilon   = innerCutOff - outerCutOff;
        float intensity = clamp((theta - outerCutOff) / epsilon, 0.0, 1.0);  

        float distance    = length(lightPos - fPosEye.xyz);
	    float attenuation = 1.0 / (constantAttenuation +  linearAttenuation * distance + quadraticAttenuation * (distance * distance));

        specularSpotLight *= intensity;
	    diffuseSpotLight *= intensity;

        ambientPoint *= attenuation;
	    specularPoint *= attenuation;
	    diffusePoint *= attenuation;
    }
    else{
        ambientSpotLight = vec3(0.0f);
        diffuseSpotLight = vec3(0.0f);
        specularSpotLight = vec3(0.0f);
    }
}
float computeShadow(){
	
	vec3 normalizedCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

	normalizedCoords = normalizedCoords * 0.5 + 0.5;

    vec2 TexelSize = vec2(1.0f/2048.0f,1.0f/2048.0f);
    
	if (normalizedCoords.z > 1.0f)
		return 0.0f;

	
    float bias = max(0.05f * (1.0f - dot(normalizedCoords, lightDir)), 0.005f);
    float shadow = 0.0f;

    float currentDepth = normalizedCoords.z;
    for(int v=-3;v<=3;v++)
        for(int u=-3;u<=3;u++){
            vec2 offset = vec2(u,v) * TexelSize;
            float closestDepth = texture(shadowMap, normalizedCoords.xy + offset).r;

            if(currentDepth - bias > closestDepth){
                shadow += 1.0f;
            }
            else{
                shadow += 0.0f;
            }
        
        }

	return (shadow/49.0f);
}
float computeFog()
{
   vec4 fPosEye = view * model * vec4(fPosition, 1.0f);
   float fogDensity = 0.03f;
   float fragmentDistance = length(fPosEye);
   float fogFactor = exp(-pow(fragmentDistance * fogDensity,2));

   return fogFactor; 
}
void main() 
{
    computeDirLight();
    computePointLight();
    
    if(ifSpotLight==1){
        computeSpotLight();
    }
    
    ambient += ambientPoint;
    diffuse += diffusePoint;
    specular += specularPoint;

    ambient += ambientSpotLight;
    diffuse += diffuseSpotLight;
    specular += specularSpotLight;
    
    //compute final vertex color
    float shadow = computeShadow();
    vec3 color = min((ambient + (1.0f - shadow)*diffuse) * texture(diffuseTexture, fTexCoords).rgb + (1.0f - shadow)*specular * texture(specularTexture, fTexCoords).rgb, 1.0f);
    	
    float fogFactor = computeFog();

    vec4 fogColor = vec4(0.5f,0.5f,0.5f,1.0f);
    fColor = vec4(color, 1.0f);
    fColor = (1 - fogFactor)*fogColor + fColor*fogFactor;

    float gamma = 2.2;
    fColor.rgb = pow(fColor.rgb,vec3(1.0/gamma));
}
