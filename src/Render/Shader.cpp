#include "Shader.hpp"

namespace Render {

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
  std::string vertexCode = loadShaderSource(vertexPath);
  std::string fragmentCode = loadShaderSource(fragmentPath);

  const char *vShaderCode = vertexCode.c_str();
  const char *fShaderCode = fragmentCode.c_str();

  GLuint vertex, fragment;

  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, nullptr);
  glCompileShader(vertex);
  checkCompileErrors(vertex, GL_VERTEX_SHADER);

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, nullptr);
  glCompileShader(fragment);
  checkCompileErrors(fragment, GL_FRAGMENT_SHADER);

  this->ID = glCreateProgram();
  glAttachShader(this->ID, vertex);
  glAttachShader(this->ID, fragment);
  glLinkProgram(this->ID);
  checkCompileErrors(this->ID, GL_PROGRAM);
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

Shader::~Shader() {}

std::string Shader::loadShaderSource(const std::string &filename) {
  std::ifstream file;
  try {
    file.open(filename);
    if (!file)
      throw std::ios_base::failure("File not found or cannot be opened");
  } catch (const std::ios_base::failure &e) {
    std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what()
              << std::endl;
    return "";
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

void Shader::checkCompileErrors(GLuint shader, GLenum type) {
  GLint success;
  GLchar infoLog[1024];
  if (type == GL_PROGRAM) {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
      std::cout
          << "ERROR::PROGRAM_LINKING_ERROR of type: PROGRAM\n"
          << infoLog
          << "\n -- --------------------------------------------------- -- "
          << std::endl;
    }
  } else {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
      std::cout
          << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
          << infoLog
          << "\n -- --------------------------------------------------- -- "
          << std::endl;
    }
  }
}

void Shader::use() { glUseProgram(this->ID); }

void Shader::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::Delete() { glDeleteProgram(this->ID); }

} // namespace Render
