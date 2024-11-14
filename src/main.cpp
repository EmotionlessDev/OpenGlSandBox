#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Render/Shader.hpp"
#include "utils/VAO.hpp"
#include "utils/VBO.hpp"
#include "utils/EBO.hpp"

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

GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f, // bottom left
     0.5f, -0.5f, 0.0f, // bottom right
    -0.5f,  0.5f, 0.0f, // top left
     0.5f,  0.5f, 0.0f  // top right
};

GLuint indices[] = {
    0, 1, 2, // первый треугольник
    2, 1, 3  // второй треугольник
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
  Render::Shader shaderProgram("../shaders/vertex.glsl",
                               "../shaders/fragment.glsl");
  Utils::VAO VAO1;
  VAO1.Bind();
  Utils::VBO VBO1(vertices, sizeof(vertices));
  VBO1.Bind();
  Utils::EBO EBO1(indices, sizeof(indices));
  EBO1.Bind();
  VAO1.LinkAttrib(VBO1, 0, 3 * sizeof(float), nullptr);
  VAO1.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();
  // render loop
  while (!glfwWindowShouldClose(pwindow)) {
    processInput(pwindow);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // start drawing

    shaderProgram.use();
    VAO1.Bind();
    EBO1.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    // end drawing
    glfwSwapBuffers(pwindow);
    glfwPollEvents();
  }
  VAO1.Delete();
  VBO1.Delete();
  shaderProgram.Delete();
  glfwTerminate();
  return 0;
}
