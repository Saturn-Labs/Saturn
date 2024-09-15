#version 410 core
in vec2 uv;
out vec4 color;
uniform sampler2D uTexture;

void main() {
    color = texture2D(uTexture, uv);
}