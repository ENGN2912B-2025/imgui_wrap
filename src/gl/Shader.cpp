//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#include <gl/gl.h>
#include <gl/Shader.hpp>

#include <vector>
#include <stdexcept>
#include <cstdio>

namespace gl
{
  Shader::Shader(unsigned type)
  {
    shader_ = glCreateShader(type);
  }

  Shader::~Shader()
  {
    glDeleteShader(shader_);
  }

  void Shader::source(const char* source)
  {
    glShaderSource(shader_, 1, &source, nullptr);
  }

  void Shader::compile()
  {
    // Compile the shader
    glCompileShader(shader_);

    // Check compilation status
    int status_, length_;
    glGetShaderiv(shader_, GL_COMPILE_STATUS, &status_);
    if (status_ == GL_FALSE)
    {
      glGetShaderiv(shader_, GL_INFO_LOG_LENGTH, &length_);
      std::vector<char> infoLog_(length_);
      glGetShaderInfoLog(shader_, length_, nullptr, infoLog_.data());
      throw std::runtime_error(infoLog_.data());
    }
  }

  size_t Shader::getShadingLanguageVersion()
  {
    const char* versionStr{
      reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)) };
    if (!versionStr)
    {
      throw std::runtime_error{ "Failed to get GLSL version" };
    }
    // Assume format is like "1.40 - Build 31.0.101.5186" or "4.50 NVIDIA"
    double version{ 0.0 };
    if (std::sscanf(versionStr, "%lf", &version) != 1)
    {
      throw std::runtime_error{ "Failed to parse GLSL version" };
    }
    return static_cast<size_t>(version * 100);
  }

} // namespace gl
