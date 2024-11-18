#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Render/Shader.hpp"

namespace Utils {
class Texture {
private:
  GLuint ID;
  GLenum type;

public:
  Texture(const char *image, GLenum texType, GLenum slot, GLenum format,
          GLenum pixelType);
  ~Texture();
  // Assigns a texture unit to a texture
  void texUnit(Render::Shader &shader, const char *uniform, GLuint unit);
  void Bind();
  void Unbind();
  void Delete();
};
} // namespace Utils

#endif
