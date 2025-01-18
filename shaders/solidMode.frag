#version 410 core

in vec3 fPosition;
flat in vec3 fNormal;
in vec2 fTexCoords;

out vec4 fColor;

void main() 
{    
    //fColor = vec4(vec3(texture(depthMap, fTexCoords).r), 1.0f);
    fColor = (dot(fNormal,fPosition)) * vec4(1.0f); 
}
