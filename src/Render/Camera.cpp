#include "Camera.hpp"

namespace Render {
Camera::Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp,
               GLint width, GLint height, GLfloat cameraSpeed)
    : cameraPos(cameraPos), cameraFront(cameraFront), cameraUp(cameraUp),
      width(width), height(height), cameraSpeed(cameraSpeed) {}

void Camera::Matrix(GLfloat fov, GLfloat nearPlane, GLfloat farPlane,
                    GLuint shaderProgram, const char *uniform) {
  // glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
  glm::mat4 view = getLookAt(cameraPos, cameraPos + cameraFront, cameraUp);
  glm::mat4 projection = glm::perspective(
      glm::radians(fov), (GLfloat)width / height, nearPlane, farPlane);
  // Camera matrix
  glUniformMatrix4fv(glGetUniformLocation(shaderProgram, uniform), 1, GL_FALSE,
                     glm::value_ptr(projection * view));
}

// my own lookAt function
glm::mat4 Camera::getLookAt(glm::vec3 position, glm::vec3 target,
                            glm::vec3 worldUp) {
  glm::vec3 cameraDirection = glm::normalize(position - target);
  glm::vec3 cameraRight = glm::normalize(glm::cross(worldUp, cameraDirection));
  glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
  glm::mat4 lookAt = glm::mat4(1.0f);
  lookAt[0][0] = cameraRight.x;
  lookAt[1][0] = cameraRight.y;
  lookAt[2][0] = cameraRight.z;
  lookAt[0][1] = cameraUp.x;
  lookAt[1][1] = cameraUp.y;
  lookAt[2][1] = cameraUp.z;
  lookAt[0][2] = cameraDirection.x;
  lookAt[1][2] = cameraDirection.y;
  lookAt[2][2] = cameraDirection.z;
  lookAt = glm::translate(lookAt, -position);
  return lookAt;
}

void Camera::ProcessInput(GLFWwindow *pwindow) {
  // keyboard inputs
  if (glfwGetKey(pwindow, GLFW_KEY_W) == GLFW_PRESS) {
    cameraPos += cameraSpeed * cameraFront;
  }
  if (glfwGetKey(pwindow, GLFW_KEY_S) == GLFW_PRESS) {
    cameraPos -= cameraSpeed * cameraFront;
  }
  if (glfwGetKey(pwindow, GLFW_KEY_A) == GLFW_PRESS) {
    cameraPos -=
        glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  }
  if (glfwGetKey(pwindow, GLFW_KEY_D) == GLFW_PRESS) {
    cameraPos +=
        glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  }
  // mouse inputs
  glfwSetInputMode(pwindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // hide cursor
  if (firstClick) {
    lastX = static_cast<GLfloat>(width) / 2;
    lastY = static_cast<GLfloat>(height) / 2;
    firstClick = false;
  }
  // get mouse position
  double xPos, yPos;
  glfwGetCursorPos(pwindow, &xPos, &yPos);
  // calculate mouse offset
  GLfloat xOffSet = static_cast<GLfloat>(xPos - lastX);
  GLfloat yOffSet = static_cast<GLfloat>(lastY - yPos);
  lastX = static_cast<GLfloat>(xPos);
  lastY = static_cast<GLfloat>(yPos);
  xOffSet *= sensitivity;
  yOffSet *= sensitivity;
  yaw += xOffSet;
  pitch += yOffSet;
  // check pitch out of bounds otherwise screen gets flipped
  if (pitch > 89.0f) {
    pitch = 89.0f;
  }
  if (pitch < -89.0f) {
    pitch = -89.0f;
  }
  // calculate direction
  glm::vec3 direction;
  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  cameraFront = glm::normalize(direction);
}
} // namespace Render
