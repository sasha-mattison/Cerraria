#include "core/chunk.hpp"
#include "core/constants.hpp"

Block::Block(glm::vec2 pos) : position(pos) {
    vertices.emplace_back(position, glm::vec2(0.0f, 0.0f));
    vertices.emplace_back(glm::vec2(position.x + BLOCK_SIZE, position.y), glm::vec2(1.0f, 0.0f));
    vertices.emplace_back(glm::vec2(position.x + BLOCK_SIZE, position.y + BLOCK_SIZE), glm::vec2(1.0f, 1.0f));

    vertices.emplace_back(position, glm::vec2(0.0f, 0.0f));
    vertices.emplace_back(glm::vec2(position.x, position.y + BLOCK_SIZE), glm::vec2(0.0f, 1.0f));
    vertices.emplace_back(glm::vec2(position.x + BLOCK_SIZE, position.y + BLOCK_SIZE), glm::vec2(1.0f, 1.0f));
}

std::vector<Block> Chunk::getNeighbors(const Block& target) {
    std::vector<Block> neighbors;

    auto it = std::find_if(
        blocks.begin(),
        blocks.end(),
        [&target](const Block& block) {
            return block.position == target.position;
        }
    );

    if (it == blocks.end())
        return neighbors;

    const std::size_t index = std::distance(blocks.begin(), it);

    const std::size_t x = index % CHUNK_SIZE;
    const std::size_t y = index / CHUNK_SIZE;

    if (x > 0)
        neighbors.push_back(blocks[index - 1]);

    if (x + 1 < CHUNK_SIZE)
        neighbors.push_back(blocks[index + 1]);

    if (y > 0)
        neighbors.push_back(blocks[index - CHUNK_SIZE]);

    if (y + 1 < CHUNK_SIZE)
        neighbors.push_back(blocks[index + CHUNK_SIZE]);

    return neighbors;
}

Chunk::Chunk(glm::vec2 pos) : position(pos) {
    blocks.reserve(pow(CHUNK_SIZE, 2));
    initChunk();
    buildMesh();
    drawSetup();
}

Chunk::Chunk(Chunk&& other) noexcept
    : VAO(other.VAO),
      VBO(other.VBO),
      texPath(std::move(other.texPath)),
      mesh(std::move(other.mesh)),
      blocks(std::move(other.blocks)),
      meshData(std::move(other.meshData)),
      position(other.position)
{
    other.VAO = 0;
    other.VBO = 0;
}

Chunk& Chunk::operator=(Chunk&& other) noexcept {
    if (this != &other) {
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);

        VAO = other.VAO;
        VBO = other.VBO;
        texPath = std::move(other.texPath);
        mesh = std::move(other.mesh);
        blocks = std::move(other.blocks);
        meshData = std::move(other.meshData);
        position = other.position;

        other.VAO = 0;
        other.VBO = 0;
    }
    return *this;
}

Chunk::~Chunk() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Chunk::initChunk() {
    for (int i = 0; i < CHUNK_SIZE; i++) {
        for (int j = 0; j < CHUNK_SIZE; j++) {
            glm::vec2 blockPos(
                position.x + j * BLOCK_SIZE - (CHUNK_SIZE * BLOCK_SIZE) / 2.0f,
                position.y + i * BLOCK_SIZE - (CHUNK_SIZE * BLOCK_SIZE) / 2.0f);
            blocks.emplace_back(blockPos);
        }
    }
}

void Chunk::buildMesh() {
    meshData.clear();
    for (const auto &block : blocks) {
        meshData.insert(meshData.end(), block.vertices.begin(), block.vertices.end());
    }
}

void Chunk::drawSetup() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, meshData.size() * sizeof(BlockVertex), meshData.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(BlockVertex), (void *)offsetof(BlockVertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(BlockVertex), (void *)offsetof(BlockVertex, texCoord));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

Block Chunk::getBlockAt(glm::vec2 point) {
    
}

Block Chunk::removeBlockAt(glm::vec2 point) {

}

float Chunk::getGroundLevel() {
    float groundLevel = position.y - (BLOCK_SIZE * (CHUNK_SIZE / 2));
    std::cout << position.y << "\n";
    return groundLevel;
}

void Chunk::draw() {
    glBindTexture(GL_TEXTURE_2D, mesh.getTexture());
    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(meshData.size()));

    glBindVertexArray(0);
}