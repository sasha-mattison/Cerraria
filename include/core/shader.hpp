#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {

    private:
        GLuint shaderProgram;
        bool initDone = false;

        const std::string vShaderpath = "shaders/vertex.glsl";
        const std::string fShaderpath = "shaders/fragment.glsl";

        std::string
        loadShader(const std::string& path);

    public:
        void use();
        void init();
        GLuint getProgram();
};