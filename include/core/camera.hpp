#pragma once

#include "core/shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {

    private:
        glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
        glm::vec2 position;
        float zoom = 1.0f;

    public:
        Camera(glm::vec2 pos);
        void setProjection(float width, float height);
        void applyProjection(Shader& shader);


};