#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 texCoord;
out vec4 pos;

uniform float offsetX;
uniform float offsetY;

void main() {
    gl_Position = vec4(aPos.x + offsetX, aPos.y + offsetY, aPos.z, 2.0f); // flips all coords

    ourColor = aColor;
    texCoord = aTexCoord;

    pos = gl_Position;
}