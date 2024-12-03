//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#include <gl/gl.h>
#include <gl/Program.hpp>

#include <vector>
#include <stdexcept>

namespace gl
{
  Program::Program()
  {
    program_ = glCreateProgram();
  }

  Program::~Program()
  {
    glDeleteProgram(program_);
  }

  void Program::attachShader(Shader shader)
  {
    shaders_.emplace_back(std::move(shader));
    glAttachShader(program_, shaders_.back().get());
  }

  void Program::link()
  {
    // Link the program
    glLinkProgram(program_);

    // Check the link status
    int status_, length_;
    glGetProgramiv(program_, GL_LINK_STATUS, &status_);
    if (status_ == GL_FALSE)
    {
      glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &length_);
      std::vector<char> infoLog_(length_);
      glGetProgramInfoLog(program_, length_, nullptr, infoLog_.data());
      throw std::runtime_error(infoLog_.data());
    }
  }

  void Program::use() const
  {
    glUseProgram(program_);
  }

  void Program::unuse() const
  {
    glUseProgram(0);
  }

  Program Program::defaultProgram()
  {
    Program program;
    program.attachShader(Shader::defaultVertexShader());
    program.attachShader(Shader::defaultFragmentShader());
    program.link();
    return program;
  }

} // namespace gl
