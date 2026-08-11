#define STB_IMAGE_IMPLEMENTATION
#include "core/mesh.hpp"

#include <algorithm>

Mesh::Mesh() {}

Mesh::Mesh(Texture type) {
    data = stbi_load(TEXTURE_ATLAS_PATH, &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load texture atlas\n";
        return; 
    }

    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    int tileSize = TEXTURE_ATLAS_RESOLUTION;
    int startX = tileSize * static_cast<int>(type); 

    std::vector<unsigned char> texData(tileSize * tileSize * nrChannels);

    for (int row = 0; row < tileSize; row++) {
        for (int col = 0; col < tileSize; col++) {
            size_t srcOffset = (static_cast<size_t>(row) * width + (startX + col)) * nrChannels;
            size_t dstOffset = (static_cast<size_t>(row) * tileSize + col) * nrChannels;

            for (int c = 0; c < nrChannels; c++) {
                texData[dstOffset + c] = data[srcOffset + c];
            }
        }
    }

    GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, format, tileSize, tileSize, 0, format, GL_UNSIGNED_BYTE, texData.data());
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

Mesh::Mesh(std::string path) {
    data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load texture at " << path << "\n";
        return;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}

GLuint Mesh::getTexture() {
    return texture;
}
