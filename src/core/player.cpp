#include "core/player.hpp"

#include <cstddef>

Vertex::Vertex(glm::vec2 pos, glm::vec2 texCoord) : initialPos(pos), position(pos), texCoord(texCoord) {}

void Vertex::updateVertex(glm::vec2 pos) {
    position.x = initialPos.x + pos.x;
    position.y = initialPos.y+ pos.y;
}

Inventory::Inventory() {

    int hotbarSlots = static_cast<int>(BlockType::end);

    for (int i = 0; i < hotbarSlots; i++) {
        hotbar.emplace(i, static_cast<BlockType>(i));
    }
}

void Inventory::setActiveSlot(int slot) {
    activeSlot = slot;

    if (slot > hotbar.size()) activeSlot = hotbar.size();
    if (slot < 0) activeSlot = 0;
}

Player::Player(glm::vec2 pos, float size, float scale) : position(pos), velocity(0), acceleration(0) {

    vertices.push_back(Vertex(glm::vec2(pos.x, pos.y), glm::vec2(0.0f, 0.0f)));
    vertices.push_back(Vertex(glm::vec2(pos.x + size, pos.y), glm::vec2(1.0f, 0.0f)));
    vertices.push_back(Vertex(glm::vec2(pos.x + size, pos.y + size), glm::vec2(1.0f, 1.0f)));

    vertices.push_back(Vertex(glm::vec2(pos.x, pos.y), glm::vec2(0.0f, 0.0f)));
    vertices.push_back(Vertex(glm::vec2(pos.x, pos.y + size), glm::vec2(0.0f, 1.0f)));
    vertices.push_back(Vertex(glm::vec2(pos.x + size, pos.y + size), glm::vec2(1.0f, 1.0f)));

    for (Vertex& v : vertices) {
        v.initialPos *= scale;
        v.position *= scale;
        v.texCoord *= scale;
    }

    drawSetup();
}

void Player::update(float tick) {
    lastPosition = position;
    if (position.y <= groundLevel && velocity.y <= 0.0f) {
        position.y = groundLevel;
        velocity.y = 0.0f;
        isGrounded = true;
    } else {
        isGrounded = false;
    }
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
    //keys
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position.x -= 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position.x += 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && isGrounded) {
        velocity.y += 2.0f;
        isGrounded = false;
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        std::cout << "x: " << position.x << " y: " << position.y << "\n";
    }
    
    //clicks
    lastPress = MouseButton::NONE;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwGetCursorPos(window, &cursorX, &cursorY);
        lastPress = MouseButton::LEFT;
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        glfwGetCursorPos(window, &cursorX, &cursorY);
        lastPress = MouseButton::RIGHT;
    }

    //inv stuff
    if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) {
        inventory.setActiveSlot(inventory.activeSlot + 1);
    }
        if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) {
        inventory.setActiveSlot(inventory.activeSlot - 1);
    }
}


glm::vec2 Player::getPos() {
    return position;
}

MouseButton Player::getLastMousePress() {
    return lastPress;
}


glm::vec2 Player::getCursorPos(GLFWwindow* window) {
    int height;
    glfwGetWindowSize(window, nullptr, &height);
    return glm::vec2(cursorX, height - cursorY);

    /* 
    cursor coords:                window coords:
   
    -y-axis                         +y-axis
    |                               |
    |                               |
    |                               |
    |                               |
    +--------- +x-axis              +--------- +x-axis

    y-axis is flipped between cursor coords and window so you have to flip them yourself
    */
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

void Player::setGround(float gl) {
    groundLevel = gl;
} 

void Player::draw() {

    GLuint drawType;
    if (position != lastPosition) {
        drawType = GL_DYNAMIC_DRAW; 
        updateVertices();
    }
    else {
        drawType = GL_STATIC_DRAW; 
    }
    
    glBindTexture(GL_TEXTURE_2D, sprite.getTexture());
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), drawType);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(1);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

