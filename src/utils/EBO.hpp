#ifndef EBO_HPP
#define EBO_HPP

#include <glad/glad.h>

namespace Utils {
class EBO {
private:
  GLuint ID;
public:
  EBO(GLuint *indices, GLsizeiptr size);
  ~EBO();
  void Bind();
  void Unbind();
  void Delete();
};
} // namespace Utils
#endif
