#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec4 vertexColorPink;
out vec3 ourColor;
out vec4 pos;
uniform float offset;
void main() {
    gl_Position = vec4(aPos.x + offset, aPos.y, aPos.z, 1.0f); // flips all coords
    ourColor = aColor;
    vertexColorPink = vec4(1.0f, 0.5f, 1.0f, 1.0f);
    pos = gl_Position;
}