#shader vertex
#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(position, 1.0);
};

#shader fragment
#version 330 core

out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0); // set all 4 vector values to 1.0
}