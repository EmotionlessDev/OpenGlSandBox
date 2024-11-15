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
     0.5f,  0.5f, 0.0f, 1.0f, 1.0f,   // верхняя правая
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   // нижняя правая
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,   // нижняя левая
    -0.5f,  0.5f, 0.0f, 0.0f, 1.0f    // верхняя левая 
};

GLuint indices[] = {
  2, 1, 3,
  1, 0, 3
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

  // load textures
  int width, height, nrChannels;
  unsigned char *data =
      stbi_load("../assets/bricks.jpg", &width, &height, &nrChannels, 0);
  if (!data) {
    std::cout << "Failed to load texture" << std::endl;
    return -1;
  }
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);

  // create a shader program
  Render::Shader shaderProgram("../shaders/vertex.glsl",
                               "../shaders/fragment.glsl");
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
    glBindTexture(GL_TEXTURE_2D, texture);
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
