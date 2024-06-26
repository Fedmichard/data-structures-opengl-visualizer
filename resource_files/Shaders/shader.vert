#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 texCoord;
out vec4 pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0f); // flips all coords
    // gl_Position = view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0f);

    ourColor = aColor;
    texCoord = aTexCoord;

    pos = gl_Position;
}