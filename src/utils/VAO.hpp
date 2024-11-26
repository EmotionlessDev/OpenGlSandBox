#ifndef VAO_HPP
#define VAO_HPP

#include <glad/glad.h>
#include "VBO.hpp"

namespace Utils {
class VAO {
private:
  GLuint ID;

public:
  VAO();
  ~VAO();
  void LinkAttrib(const VBO &VBO, GLuint layout, GLuint size, GLsizeiptr stride, void *offset);
  void Bind();
  void Unbind();
  void Delete();
};
} // namespace Utils

#endif
