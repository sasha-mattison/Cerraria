#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 vertexColour;

void main() {
    gl_Position = vec4(aPos, 1.0f);
    vertexColour = vec4(sin(aPos.x), sin(aPos.y), sin(aPos.z), 0.0f);
}