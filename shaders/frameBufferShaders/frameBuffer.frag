#version 400 core
out vec2 FragColor;
in vec2 TexCoords;

uniform smapler2D screenTexture;

void main() {
    FragColor = texture(screenTexture, TexCoords);
}
