#pragma once

#include "core/mesh.hpp"
#include "core/chunk.hpp"

#include <glm/glm.hpp>
#include "core/constants.hpp"
#include <algorithm>
#include <vector>
#include <map>
#include <memory>

struct Vertex {
    Vertex(glm::vec2 pos, glm::vec2 texCoord);
    glm::vec2 initialPos;
    glm::vec2 position;
    glm::vec2 texCoord;
    void updateVertex(glm::vec2 pos);
};

struct InvData {
    Block block;
    int count;

    InvData() = default;
    InvData(const Block& b, int c) : block(b), count(c) {}
};

struct Inventory {
    Inventory();
    std::vector<InvData> hotbar;
    void modifyHotbar(int slot, Block block, int amount);
};

class Player {

    private:
        std::string spritePath = std::string(ASSETS_DIR) + "textures/image.png";
        Mesh sprite = Mesh(Texture::PLAYER);
        glm::vec2 position;
        glm::vec2 velocity;
        glm::vec2 acceleration;
        bool applyGravity = true;
        bool isGrounded = false;
        float groundLevel = -100.0f;
        float size = 0.5f;

        double cursorX;
        double cursorY;

        std::vector<Vertex> vertices;
        GLuint VAO;
        GLuint VBO;
        void drawSetup();

        void updateVertices();

    public:
        Player(glm::vec2 pos);
        void update(float tick);
        void input(GLFWwindow* window);
        glm::vec2 getPos();
        glm::vec2 getCursorPos(GLFWwindow* window);
        void setGround(float gl);
        void draw();


};

