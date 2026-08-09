#pragma once

#include "core/mesh.h"

#include <glm/glm.hpp>
#include <vector>

struct BlockVertex {
    BlockVertex(glm::vec2 pos, glm::vec2 texCoord);
    glm::vec2 position;
    glm::vec2 initialPos;
    glm::vec2 texCoord;
    // void updateVertex(glm::vec2 pos);
};

struct Block {

    glm::vec2 position;
    GLuint VAO;
    GLuint VBO;

    std::string texPath = std::string(ASSETS_DIR) + "textures/image.png";

    Mesh mesh = Mesh(texPath);

    std::vector<BlockVertex> vertices;
    void drawSetup();

    Block(glm::vec2 pos);
    void draw();
};

class Chunk {

    private:
        std::vector<std::vector<Block>> chunk;
        glm::vec2 position;
        void initChunk();

    public:
        Chunk(glm::vec2 pos);
        void draw();
};




