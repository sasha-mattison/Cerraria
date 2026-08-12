#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 projection;
uniform float scale;
uniform vec2 cameraPos;

out vec4 vertexColour;
out vec2 TexCoord;

void main() {

    gl_Position = scale * projection * vec4(aPos, 0.0f, 1.0f);
    vertexColour = vec4(sin(aPos.x), sin(aPos.y), 0.0f, 0.0f);
    TexCoord = aTexCoord;
    
}