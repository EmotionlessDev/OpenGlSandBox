#include "VAO.hpp"
namespace Utils {

VAO::VAO() {
  glGenVertexArrays(1, &ID);
  glBindVertexArray(ID);
}

VAO::~VAO() {}

void VAO::LinkAttrib(const VBO &VBO, GLuint layout, GLsizeiptr stride, void *offset) {
  VBO.Bind();
  glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, stride, offset);
  glEnableVertexAttribArray(layout);
  VBO.Unbind();
}

void VAO::Bind() {
  glBindVertexArray(ID);
}

void VAO::Unbind() {
  glBindVertexArray(0);
}

void VAO::Delete() {
  glDeleteVertexArrays(1, &ID);
}

} // namespace Utils
