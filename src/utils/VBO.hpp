#ifndef VBO_HPP
#define VBO_HPP

#include <glad/glad.h>

namespace Utils {

class VBO {
private:
  GLuint ID;

public:
  VBO(GLfloat *vertices, GLsizeiptr size);
  ~VBO();
  void Bind() const;
  void Unbind() const;
  void Delete() const;
};
} // namespace Utils

#endif
