#include "core/application.hpp"

#include "core/player.hpp"
#include "core/chunk.hpp"

void Application::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    Application* app =
        static_cast<Application*>(glfwGetWindowUserPointer(window));

    glViewport(0, 0, width, height);

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

    Chunk chunk(glm::vec2(100.0f, 100.0f));

    Player player(glm::vec2(0.0f, 0.0f));

    camera.applyProjection(shader);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        player.update(1);
        player.input(window);
        player.draw();

        chunk.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    } 

    cleanup();
}