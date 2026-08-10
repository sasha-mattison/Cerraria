#pragma once

#include "core/mesh.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>

struct BlockVertex {
    glm::vec2 position;
    glm::vec2 initialPos;
    glm::vec2 texCoord;

    BlockVertex(glm::vec2 pos, glm::vec2 texCoord)
        : position(pos), initialPos(pos), texCoord(texCoord) {}
};

struct Block {
    glm::vec2 position;
    std::vector<BlockVertex> vertices;

    Block(glm::vec2 pos);
};

class Chunk {
private:
    GLuint VAO = 0;
    GLuint VBO = 0;

    std::string texPath = std::string(ASSETS_DIR) + "textures/image.png";
    Mesh mesh = Mesh(texPath);

    std::vector<Block> blocks;
    std::vector<BlockVertex> meshData;
    glm::vec2 position;

    void initChunk();
    void drawSetup();
    void buildMesh();

    std::vector<Block> getNeighbors(const Block& target, const std::vector<Block>& blocks);

public:
    Chunk(glm::vec2 pos);
    ~Chunk();

    void draw();
};