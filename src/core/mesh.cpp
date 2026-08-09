#define STB_IMAGE_IMPLEMENTATION
#include "core/mesh.hpp"

Mesh::Mesh() {}

Mesh::Mesh(int TexID) {}

Mesh::Mesh(std::string path) {
    data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (!data)
        std::cerr << "Failed to load texture at " << path << "\n";

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);  

}

GLuint Mesh::getTexture() {
    return texture;
}
