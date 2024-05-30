#version 460 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float opacity;

void main() {
    // FragColor = mix(texture(texture1, texCoord) * vec4(ourColor, 1.0), texture(texture2, vec2(texCoord.x, texCoord.y)) * vec4(ourColor, 1.0), opacity);
    FragColor = mix(texture(texture1, texCoord), texture(texture2, vec2(texCoord.x, texCoord.y)), opacity);
}