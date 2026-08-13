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
    #include "core/chunk.hpp"

    struct ChunkManager {

        enum Direction {
            LEFT,
            RIGHT
        };

        std::vector<Chunk> chunkList;
        float yPosition;
        glm::vec2 worldOrigin;
        ChunkManager(glm::vec2 origin);
        void newChunks(int amount);
        Chunk* getChunkAt(const glm::vec2& worldPos);
    };

    class Application {

        private:
            GLFWwindow* window;
            const int initialWidth = 800;
            const int initialHeight = 600;
            int width = initialWidth;
            int height = initialHeight;
            float scale = 1;
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