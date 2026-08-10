#include "core/shader.hpp"

std::string Shader::loadShader(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << path << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void Shader::init() {
    int success;
    char infoLog[512];

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vShaderCode = loadShader(std::string(ASSETS_DIR) + vShaderpath);
    const char *vShaderSource = vShaderCode.c_str();
    glShaderSource(vertexShader, 1, &vShaderSource, nullptr);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fShaderCode = loadShader(std::string(ASSETS_DIR) + fShaderpath);
    const char *fShaderSource = fShaderCode.c_str();
    glShaderSource(fragmentShader, 1, &fShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    initDone = true;
}

void Shader::use() {
    if (!initDone)
        std::cerr << "Shader uninitialized, please initialize by calling <shader>.init()!\n";
    else
        glUseProgram(shaderProgram);
}

GLuint Shader::getProgram() {
    return shaderProgram;
}