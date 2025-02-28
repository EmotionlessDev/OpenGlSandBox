#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // подключаем glad для активации всех заголовочных файлов OpenGL

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <../../external/glm/glm.hpp>
#include <../../external/glm/gtc/type_ptr.hpp>
#include <../../external/glm/mat4x4.hpp>

namespace Render {

class Shader {
public:
  // Конструктор считывает данные и выполняет построение шейдера
  Shader(const std::string &vertexPath, const std::string &fragmentPath);

  // Использование/активация шейдера
  void use();

  // Полезные uniform-функции
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setMat4(const std::string &name, const glm::mat4 &mat) const;
  void setVec3(const std::string &name, const glm::vec3 &vec) const;
  GLuint getID() const;

  void Delete();

  ~Shader();

private:
  // load shader source code from file
  std::string loadShaderSource(const std::string &filename);
  // check for shader compile errors
  void checkCompileErrors(GLuint shader, GLenum type);
  // ID - идентификатор программы
  GLuint ID;
};

} // namespace Render

#endif
