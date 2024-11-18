#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
 
out vec3 ourColor;
out vec2 TexCoord;
uniform float offset1;
uniform float offset2;
uniform float time;
uniform float angle;

void main()
{
    mat2 rotation = mat2(cos(angle), -sin(angle),
                         sin(angle), cos(angle));
    vec2 rotation_pos = rotation * aPos.xy;
    gl_Position = vec4(rotation_pos.x + offset1, rotation_pos.y + offset2,aPos.z, 1.0);
    TexCoord = aTexCoord;
    ourColor = vec3(1.0f, 0.5f, 0.2f);
}
