#include "core/player.hpp"

#include <cstddef>

Vertex::Vertex(glm::vec2 pos, glm::vec2 texCoord) : initialPos(pos), position(pos), texCoord(texCoord) {}

void Vertex::updateVertex(glm::vec2 pos) {
    position.x = initialPos.x + pos.x;
    position.y = initialPos.y+ pos.y;
}

Player::Player(glm::vec2 pos) : position(pos), velocity(0), acceleration(0) {

    vertices.push_back(Vertex(glm::vec2(-0.5f + pos.x, -0.5f + pos.y), glm::vec2(0.0f, 0.0f)));
    vertices.push_back(Vertex(glm::vec2(0.5f + pos.x, -0.5f + pos.y), glm::vec2(1.0f, 0.0f)));
    vertices.push_back(Vertex(glm::vec2(0.5f + pos.x, 0.5f + pos.y), glm::vec2(1.0f, 1.0f)));
    vertices.push_back(Vertex(glm::vec2(-0.5f + pos.x, -0.5f + pos.y), glm::vec2(0.0f, 0.0f)));
    vertices.push_back(Vertex(glm::vec2(-0.5f + pos.x, 0.5f + pos.y), glm::vec2(0.0f, 1.0f)));
    vertices.push_back(Vertex(glm::vec2(0.5f + pos.x, 0.5f + pos.y), glm::vec2(1.0f, 1.0f)));

    drawSetup();
}

void Player::update(float tick) {
    if (applyGravity && !isGrounded) {
        acceleration.y = GRAVITY/20000.0f;
        velocity += acceleration * tick;
        position += velocity * tick;
    } else {
        acceleration = glm::vec2(0.0f, 0.0f);
        if (velocity.x > 0.0f) {
            velocity.x = std::max(0.0f, velocity.x - 0.05f);
        } else if (velocity.x < 0.0f) {
            velocity.x = std::min(0.0f, velocity.x + 0.05f);
        }
        if (isGrounded) {
            velocity.y = 0.0f;
        }
        position += velocity * tick;
    }
}

void Player::input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position.x -= 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position.x += 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position.y += 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        position.y -= 0.01f;
    }
}


glm::vec2 Player::getPos() {
    return position;
}

void Player::drawSetup() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void Player::updateVertices() {
    for (Vertex& v : vertices) {
        v.updateVertex(position);
    }
}

void Player::draw() {
    updateVertices();
    glBindTexture(GL_TEXTURE_2D, sprite.getTexture());
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(1);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}