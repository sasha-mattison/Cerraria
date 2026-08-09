#pragma once

#include "stb_image.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class Mesh {

    private:
        int width, height, nrChannels;
        unsigned char* data;
        GLuint texture;

    public:
        Mesh();
        Mesh(int TexID);
        Mesh(std::string path);
        GLuint getTexture();
        // "assets/textues/image.png"
};