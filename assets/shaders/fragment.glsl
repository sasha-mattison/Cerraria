#version 330 core

in vec4 vertexColour;
out vec4 FragColour;
in vec2 TexCoord;

uniform sampler2D ourTexture;


void main() {
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    //FragColour = vertexColour;
    FragColour = texture(ourTexture, TexCoord);
} 