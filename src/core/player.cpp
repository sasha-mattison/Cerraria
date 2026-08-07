#include "core/player.h"

Player::Player(glm::vec3 pos) : position(pos), velocity(0), acceleration(0) {
    vertices = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f
        };

        drawSetup();
}

void Player::update(float tick) {
    if (applyGravity && !isGrounded) {
        acceleration.z = GRAVITY;
        velocity += acceleration * tick;
        position += velocity * tick;
    } else {
        acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
        velocity.x = std::max(0.0f, velocity.x - 0.05f);
        position += velocity * tick;
    }
    

}

void Player::input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        velocity += 0.1f;
    }
}


glm::vec3 Player::getPos() {
    return position;
}

void Player::drawSetup() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void Player::updateVertices() {
    for (int i = 0; i < vertices.size(); i++) {
    }

}

void Player::draw() {
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices));
}