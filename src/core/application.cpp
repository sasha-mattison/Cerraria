#include "core/application.hpp"

#include "core/player.hpp"

ChunkManager::ChunkManager(glm::vec2 origin) : worldOrigin(origin) {}

void ChunkManager::newChunks(int amount) {
    for (int i = 0; i < amount; i++) {
        int index = chunkList.size();
        int side = index % 2;
        int multiplier = (index + 1) / 2;

        switch (side) {
            case 0: {
                Chunk chunk(glm::vec2(worldOrigin.x + multiplier * CHUNK_SIZE * BLOCK_SIZE, worldOrigin.y));
                chunkList.push_back(std::move(chunk));
            }
            break;
            case 1: {
                Chunk chunk(glm::vec2(worldOrigin.x - multiplier * CHUNK_SIZE * BLOCK_SIZE, worldOrigin.y));
                chunkList.push_back(std::move(chunk));
            }
            break;
        }
    }
}

void Application::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    Application* app =
        static_cast<Application*>(glfwGetWindowUserPointer(window));

    glViewport(0, 0, width, height);

    //Fixes squishing from the window and shii
    app->camera.setProjection(width, height);
    app->camera.applyProjection(app->shader);
    app->aspectRatio = static_cast<float>(width)/height;
    app->applyScaling();
}

void Application::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action != GLFW_PRESS)
        return;

    switch (key) {
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, true);
        break;
    default:
        break;
    }
}

void Application::applyScaling() {
    GLint scaleLoc = glGetUniformLocation(shader.getProgram(), "scale");
    glUniform1f(scaleLoc, aspectRatio);
}

void Application::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


    window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);

    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    
    shader.init();

    camera.setProjection(width, height);
    camera.applyProjection(shader);
    applyScaling();

    #ifdef __APPLE__
        glfwGetFramebufferSize(window, &width, &height); //ts fixes bullshit problem on MacOS
    #endif

    glViewport(0, 0, width, height);

}

void Application::cleanup() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::run(){
    init();

    // Chunk chunk(glm::vec2(100.0f, 100.0f));
    // Chunk chunk2(glm::vec2(200.0f, 100.0f));
    ChunkManager chunkManager(glm::vec2(300.0f, 100.0f));
    chunkManager.newChunks(500);


    Player player(glm::vec2(0.0f, 0.0f));
    player.setGround(chunkManager.chunkList[0].getGroundLevel());

    camera.applyProjection(shader);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        player.update(1);
        player.input(window);
        player.draw();

        // chunk.draw();
        // chunk2.draw();

        for (Chunk& c : chunkManager.chunkList)
            c.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    } 

    cleanup();
}