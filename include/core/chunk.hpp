#pragma once

#include "core/mesh.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <algorithm>
#include <iterator>

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

    Block* getBlockAt(glm::vec2 point);

    std::vector<Block> getNeighbors(const Block& target);

public:
    Chunk(glm::vec2 pos);
    Chunk(const Chunk&) = delete;
    Chunk& operator=(const Chunk&) = delete;
    Chunk(Chunk&& other) noexcept;
    Chunk& operator=(Chunk&& other) noexcept;
    ~Chunk();

    void removeBlockAt(glm::vec2 point);
    float getGroundLevel();

    void draw();
};