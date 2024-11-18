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
#include "utils/Texture.hpp"
#include "../external/stb/stb_image.h"

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
    // координаты      // текстурные координаты
    0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // верхняя правая
    0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // нижняя правая
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // нижняя левая
    -0.5f, 0.5f,  0.0f, 0.0f, 1.0f  // верхняя левая
};

GLuint indices[] = {2, 1, 3, 1, 0, 3};

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
  Utils::Texture texture("../assets/pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0,
                         GL_RGBA, GL_UNSIGNED_BYTE);
  texture.texUnit(shaderProgram, "ourTexture", 0);
  Utils::VAO VAO1;
  VAO1.Bind();
  Utils::VBO VBO1(vertices, sizeof(vertices));
  VBO1.Bind();
  Utils::EBO EBO1(indices, sizeof(indices));
  EBO1.Bind();
  VAO1.LinkAttrib(VBO1, 0, 5 * sizeof(float), nullptr);
  VAO1.LinkAttrib(VBO1, 1, 5 * sizeof(float), (void *)(3 * sizeof(float)));
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
    texture.Bind();

    float timeValue = glfwGetTime();
    float offset1 = 0.8f * cos(timeValue) / 2.0f;
    float offset2 = (0.8f * sin(timeValue) / 2.0f) / 2.0f;
    float angle = 1.0f * timeValue;
    shaderProgram.setFloat("offset1", offset1);
    shaderProgram.setFloat("offset2", offset2);
    shaderProgram.setFloat("time", timeValue);
    shaderProgram.setFloat("angle", angle);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    // end drawing
    glfwSwapBuffers(pwindow);
    glfwPollEvents();
  }
  VAO1.Delete();
  VBO1.Delete();
  EBO1.Delete();
  texture.Delete();
  shaderProgram.Delete();
  glfwTerminate();
  return 0;
}
