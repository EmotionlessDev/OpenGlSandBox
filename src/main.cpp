#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Render/Shader.hpp"

// callback function for window resizing
void framebuffer_size_callback(GLFWwindow *pwindow, int width, int height) {
  glViewport(0, 0, width, height);
}

// quit the application when ESC is pressed
void processInput(GLFWwindow *pwindow) {
  if (glfwGetKey(pwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(pwindow, true);
  }
}

float vertices[] = {
    // координаты       // цвета
    0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // нижняя правая вершина
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // нижняя левая вершина
    0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // верхняя вершина
};

unsigned int indices[] = {
    0, 1, 3, // первый треугольник
    1, 2, 3  // второй треугольник
};

int main() {
  // initialize GLFW
  if (!glfwInit()) {
    std::cout << "glfwInit failed" << std::endl;
    return -1;
  }
  // set GLFW window hints
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // required for Mac
#endif

  // create a windowed mode window and its OpenGL context
  GLFWwindow *pwindow = glfwCreateWindow(800, 600, "SandBox", nullptr, nullptr);
  if (!pwindow) {
    std::cout << "glfwCreateWindow failed" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(pwindow);

  // initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }
  glfwSetFramebufferSizeCallback(pwindow, framebuffer_size_callback);

  // create a shader program
  Render::Shader shaderProgram("../shaders/vertex.glsl", "../shaders/fragment.glsl");
  // VAO1
  unsigned int VAO1;
  glGenVertexArrays(1, &VAO1);
  glBindVertexArray(VAO1);
  // VBO 1
  unsigned int VBO1;
  glGenBuffers(1, &VBO1);
  glBindBuffer(GL_ARRAY_BUFFER, VBO1);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // coordinates
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);
  // colors
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // render loop
  while (!glfwWindowShouldClose(pwindow)) {
    processInput(pwindow);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    shaderProgram.use();
    shaderProgram.setFloat("ourColor", greenValue);
    glBindVertexArray(VAO1);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(pwindow);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}
