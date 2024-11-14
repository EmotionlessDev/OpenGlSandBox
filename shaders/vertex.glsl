#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
 
out vec3 ourColor;
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
    
    ourColor = aColor * sin(time + aPos.x + aPos.y);
}
