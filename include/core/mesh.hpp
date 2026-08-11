#pragma once

#include "stb_image.h"
#include "constants.hpp"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

enum class Texture {
    PLAYER,
    CRATE
};

class Mesh {

    private:
        int width, height, nrChannels;
        unsigned char* data;
        GLuint texture;

    public:
        Mesh();
        Mesh(Texture type);
        Mesh(std::string path);
        GLuint getTexture();
        // "assets/textues/image.png"
};