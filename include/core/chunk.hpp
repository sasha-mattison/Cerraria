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

enum class BlockType {
    GRASS,
    DIRT,
    STONE,
    AIR,

    end
};

struct Block {
    glm::vec2 position;
    std::vector<BlockVertex> vertices;
    BlockType type = BlockType::GRASS;

    Block(glm::vec2 pos, BlockType type);
    Block(glm::vec2 pos);
    Block();
};

class Chunk {
private:
    GLuint VAO = 0;
    GLuint VBO = 0;

    Texture texType = Texture::CRATE;
    Mesh mesh = Mesh(texType);

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
    void placeBlockAt(glm::vec2 point, BlockType type);
    float getGroundLevel();

    void draw();
};