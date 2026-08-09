#pragma once

#include <glad/gl.h>

#include "core/shader.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

class Application {

    private:
        GLFWwindow* window;
        int width = 800;
        int height = 800;
        std::string name = "Cerraria";

        std::string loadShader(const std::string &path);
        void shaderSetup();
        void init();
        void cleanup();
        void loop();

        static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

        Shader shader;

    public:
        void run();
};