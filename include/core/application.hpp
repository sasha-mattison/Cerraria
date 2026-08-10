#pragma once

#include <glad/gl.h>

#include "core/shader.hpp"
#include "core/camera.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

struct World {

};

class Application {

    private:
        GLFWwindow* window;
        int width = 800;
        int height = 800;
        float aspectRatio = static_cast<float>(width)/height;
        void applyScaling();
        std::string name = "Cerraria";

        std::string loadShader(const std::string &path);
        void init();
        void cleanup();

        static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

        Shader shader;

        Camera camera{glm::vec2(0.0f, 0.0f)};

    public:
        void run();
};