#include <core/camera.hpp>

Camera::Camera(glm::vec2 pos) : position(pos) {}

void Camera::applyProjection(Shader& shader) {
    GLint projectionLoc = glGetUniformLocation(shader.getProgram(), "projection");

    shader.use();

    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void Camera::setProjection(float width, float height) {
    projection = glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
}