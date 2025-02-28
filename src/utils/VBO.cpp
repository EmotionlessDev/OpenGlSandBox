#include "VBO.hpp"

namespace Utils {

VBO::VBO(GLfloat *vertices, GLsizeiptr size) {
  glGenBuffers(1, &ID);
  glBindBuffer(GL_ARRAY_BUFFER, ID);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VBO::~VBO() {}

void VBO::Bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() const {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() const {
  glDeleteBuffers(1, &ID);
}

} // namespace Utils
