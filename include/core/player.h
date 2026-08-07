#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "core/constants.h"
#include <algorithm>
#include <vector>

struct Vertex {
    glm::vec3 pos;
    void updateVertex();
};

class Player {

    private:
        glm::vec3 position;
        glm::vec3 velocity;
        glm::vec3 acceleration;
        bool applyGravity = false;
        bool isGrounded = true;
        float size;

        std::vector<float> vertices;
        GLuint VAO;
        GLuint VBO;
        void drawSetup();

        void updateVertices();

    public:
        Player(glm::vec3 pos);
        void update(float tick);
        void input(GLFWwindow* window);
        glm::vec3 getPos();
        void draw();

};

