#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
 
uniform mat4 modelMatrix;
uniform mat4 cameraMatrix;

out vec3 ourColor;
out vec2 TexCoord;


void main()
{
    gl_Position = cameraMatrix * modelMatrix * vec4(aPos, 1.0); 
    TexCoord = aTexCoord;
    ourColor = vec3(1.0f, 0.5f, 0.2f);
}
