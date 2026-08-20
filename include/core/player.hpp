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

enum class MouseButton {
    LEFT,
    RIGHT,
    NONE
};

struct Inventory {
    std::map<int, BlockType> hotbar;
    int activeSlot = 0;

    Inventory();
    void setActiveSlot(int slot);

};

class Player {

    private:
        std::string spritePath = std::string(ASSETS_DIR) + "textures/image.png";
        Mesh sprite = Mesh(Texture::PLAYER);
        glm::vec2 position;
        glm::vec2 lastPosition;
        glm::vec2 velocity;
        glm::vec2 acceleration;
        bool applyGravity = true;
        bool isGrounded = false;
        float groundLevel = -100.0f;
        float scale = 0.5f;

        double cursorX;
        double cursorY;

        MouseButton lastPress;

        Inventory inventory;

        std::vector<Vertex> vertices;
        GLuint VAO;
        GLuint VBO;
        void drawSetup();

        void updateVertices();

    public:
        Player(glm::vec2 pos, float scale, float size);
        void update(float tick);
        void input(GLFWwindow* window);
        glm::vec2 getPos();
        glm::vec2 getCursorPos(GLFWwindow* window);
        MouseButton getLastMousePress();
        void setGround(float gl);
        void draw();
        BlockType getActiveBlock();


};

