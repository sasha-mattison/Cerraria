#include "core/chunk.h"

#include "core/constants.h"

BlockVertex::BlockVertex(glm::vec2 pos, glm::vec2 texCoord) : position(pos), initialPos(pos), texCoord(texCoord) {}

Block::Block(glm::vec2 pos) : position(pos) {

    vertices.push_back(BlockVertex(position, glm::vec2(0.0f, 0.0f)));
    vertices.push_back(BlockVertex(glm::vec2(position.x + BLOCK_SIZE, position.y), glm::vec2(1.0f, 0.0f)));
    vertices.push_back(BlockVertex(glm::vec2(position.x + BLOCK_SIZE, position.y + BLOCK_SIZE), glm::vec2(1.0f, 1.0f)));
    vertices.push_back(BlockVertex(position, glm::vec2(0.0f, 0.0f)));
    vertices.push_back(BlockVertex(glm::vec2(position.x, position.y + BLOCK_SIZE), glm::vec2(0.0f, 1.0f)));
    vertices.push_back(BlockVertex(glm::vec2(position.x + BLOCK_SIZE, position.y + BLOCK_SIZE), glm::vec2(1.0f, 1.0f)));

    drawSetup();
}

void Block::drawSetup() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void Block::draw() {
    glBindTexture(GL_TEXTURE_2D, mesh.getTexture());
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(BlockVertex), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(BlockVertex), (void *)offsetof(BlockVertex, position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(BlockVertex), (void *)offsetof(BlockVertex, texCoord));
    glEnableVertexAttribArray(1);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}


Chunk::Chunk(glm::vec2 pos) : position(pos) {
    initChunk();
}

void Chunk::initChunk() {
    for (int i = 0; i < CHUNK_SIZE; i++) {
        std::vector<Block> chunkLayer;
        for (int j = 0; j < CHUNK_SIZE; j++) {
            chunkLayer.push_back(Block(glm::vec2(position.x - j*BLOCK_SIZE + (CHUNK_SIZE * BLOCK_SIZE) / 2, position.y - i*BLOCK_SIZE + (CHUNK_SIZE * BLOCK_SIZE) / 2)));
        }
        chunk.push_back(chunkLayer);
    }
}

void Chunk::draw() {
    for (std::vector<Block>& cl : chunk) {
        for (Block& b : cl) {
            b.draw();
        }
    }
}