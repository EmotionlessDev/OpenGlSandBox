#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <../../external/glm/glm.hpp>
#include <../../external/glm/gtc/matrix_transform.hpp>
#include <../../external/glm/gtc/type_ptr.hpp>

namespace Render {

class Camera {
private:
  glm::vec3 cameraPos;
  glm::vec3 cameraFront;
  glm::vec3 cameraUp;
  GLint width;
  GLint height;
  GLfloat cameraSpeed;
  // mouse data
  GLboolean firstClick = true;
  GLfloat lastX;
  GLfloat lastY;
  GLfloat yaw = -90.0f;
  GLfloat pitch = 0.0f;
  GLfloat sensitivity = 0.05f;
public:
  Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, GLint width, GLint height, GLfloat cameraSpeed);
  void Matrix(GLfloat fov, GLfloat nearPlane, GLfloat farPlane, GLuint shaderProgram, const char *uniform);
  void ProcessInput(GLFWwindow *pwindow);
  glm::mat4 getLookAt(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp);
};

} // namespace Render

#endif
