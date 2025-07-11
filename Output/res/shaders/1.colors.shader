#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 u_MVP;
uniform mat4 u_Model;

void main()
{
    gl_Position = u_MVP * vec4(position, 1.0);
    FragPos = vec3(u_Model * vec4(position, 1.0));
    Normal = aNormal;
};

#shader fragment
#version 330 core

in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;
  
uniform vec4 u_ObjectColor;
uniform vec4 u_LightColor;
uniform vec4 u_LightPos;
uniform vec4 u_ViewPos;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * u_LightColor.rgb;


    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(u_LightPos.rgb - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_LightColor.rgb;


    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_ViewPos.rgb - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
    vec3 specular = specularStrength * spec * u_LightColor.rgb;

    
    FragColor = vec4((ambient+diffuse+specular) * u_ObjectColor.rgb, 1.0);
}