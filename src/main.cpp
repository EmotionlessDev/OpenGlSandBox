#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "../external/glm/glm.hpp"
#include "../external/glm/gtc/matrix_transform.hpp"
#include "../external/glm/gtc/type_ptr.hpp"
#include "Render/Shader.hpp"
#include "utils/VAO.hpp"
#include "utils/VBO.hpp"
#include "utils/EBO.hpp"
#include "utils/Texture.hpp"
#include "../external/stb/stb_image.h"

// constants
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
const GLint WIDTH = 800;
const GLint HEIGHT = 600;
GLfloat lastX = static_cast<GLfloat>(WIDTH) / 2,
        lastY = static_cast<GLfloat>(HEIGHT) / 2;
GLfloat yaw = -90.0f, pitch = 0.0f;
GLboolean firstMouse = true;
// callback function for window resizing
void framebuffer_size_callback(GLFWwindow *pwindow, int width, int height) {
  glViewport(0, 0, width, height);
}

// quit the application when ESC is pressed
void processInput(GLFWwindow *pwindow, glm::vec3 &cameraPos,
                  glm::vec3 &cameraFront, glm::vec3 &cameraUp) {
  if (glfwGetKey(pwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(pwindow, true);
  }
  const GLfloat cameraSpeed = 2.5f * deltaTime;
  if (glfwGetKey(pwindow, GLFW_KEY_W) == GLFW_PRESS) {
    std::cout << "W key is pressed" << std::endl;
    cameraPos += cameraSpeed * cameraFront;
  }
  if (glfwGetKey(pwindow, GLFW_KEY_S) == GLFW_PRESS) {
    std::cout << "S key is pressed" << std::endl;
    cameraPos -= cameraSpeed * cameraFront;
  }
  if (glfwGetKey(pwindow, GLFW_KEY_A) == GLFW_PRESS) {
    std::cout << "A key is pressed" << std::endl;
    cameraPos -=
        glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  }
  if (glfwGetKey(pwindow, GLFW_KEY_D) == GLFW_PRESS) {
    std::cout << "D key is pressed" << std::endl;
    cameraPos +=
        glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  }
}

// mouse callback function
void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }
  GLfloat xoffset = xpos - lastX;
  GLfloat yoffset = lastY - ypos;
  lastX = xpos;
  lastY = ypos;
  GLfloat sensitivity = 0.05f;
  xoffset *= sensitivity;
  yoffset *= sensitivity;
  yaw += xoffset;
  pitch += yoffset;
  if (pitch > 89.0f) {
    pitch = 89.0f;
  }
  if (pitch < -89.0f) {
    pitch = -89.0f;
  }
}

GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //
    0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, //
    0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
    0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
    -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, //
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //

    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //
    0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, //
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, //
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, //
    -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, //
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //

    -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, //
    -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, //
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //
    -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, //

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //
    0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
    0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, //
    0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, //
    0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, //
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
    0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, //
    0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, //
    0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, //
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, //
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //

    -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, //
    0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //
    -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, //
    -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f  //
};

GLuint indices[] = {
    0, 1, 3, // первый треугольник
    1, 2, 3  // второй треугольник
};

glm::vec3 cubePositions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
    glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

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
  GLFWwindow *pwindow =
      glfwCreateWindow(WIDTH, HEIGHT, "SandBox", nullptr, nullptr);
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
  Utils::Texture texture("../assets/wooden_container.jpg", GL_TEXTURE_2D,
                         GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
  texture.texUnit(shaderProgram, "ourTexture", 0);
  Utils::VAO VAO1;
  VAO1.Bind();
  Utils::VBO VBO1(vertices, sizeof(vertices));
  VBO1.Bind();
  Utils::EBO EBO1(indices, sizeof(indices));
  EBO1.Bind();
  VAO1.LinkAttrib(VBO1, 0, 3, 5 * sizeof(float), (void *)0);
  VAO1.LinkAttrib(VBO1, 1, 2, 5 * sizeof(float), (void *)(3 * sizeof(float)));
  VAO1.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();
  // camera settings
  glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
  glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 cameraDirection =
      glm::normalize(cameraPos - cameraTarget); // camera direction
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);   // up vector
  glm::vec3 cameraRight =
      glm::normalize(glm::cross(up, cameraDirection)); // camera right vector
  glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight); // camera up
  glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);          // camera front
  // catch mouse events
  glfwSetInputMode(pwindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(pwindow, mouse_callback);
  // enable depth testing
  glEnable(GL_DEPTH_TEST);
  // render loop

  while (!glfwWindowShouldClose(pwindow)) {
    processInput(pwindow, cameraPos, cameraFront, cameraUp);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // start drawing
    shaderProgram.use();
    VAO1.Bind();
    texture.Bind();

    for (int i = 0; i < 10; i++) {
      glm::mat4 modelMatrix = glm::mat4(1.0f); // init model matrix
      modelMatrix = glm::translate(modelMatrix,
                                   cubePositions[i]); // translate model matrix
      GLfloat angle = 20.0f * (i + 1);
      if (i % 3 == 0) {
        angle = static_cast<GLfloat>(glfwGetTime() * glm::radians(angle));
      }
      modelMatrix =
          glm::rotate(modelMatrix, angle,
                      glm::vec3(1.0f, 0.3f, 0.5f)); // rotate model matrix
      shaderProgram.setMat4("modelMatrix", modelMatrix);
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glm::mat4 viewMatrix = glm::mat4(1.0f); // init view matrix
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
    viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    glm::mat4 projectionMatrix = glm::mat4(1.0f); // init projection matrix
    projectionMatrix =
        glm::perspective(glm::radians(45.0f), (GLfloat)WIDTH / HEIGHT, 0.1f,
                         100.0f); // set projection
    shaderProgram.setMat4("viewMatrix", viewMatrix);
    shaderProgram.setMat4("projectionMatrix", projectionMatrix);


    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
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
