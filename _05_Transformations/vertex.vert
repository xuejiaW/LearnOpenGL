#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 atex;

uniform mat4 transform;

out vec2 tex;

void main()
{
        gl_Position = transform * vec4(aPos.xyz, 1.0);
//    gl_Position = vec4(aPos.xyz, 1.0);
    tex = atex;
}