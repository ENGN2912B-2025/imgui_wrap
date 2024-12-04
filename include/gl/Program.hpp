//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#pragma once

#include <gl/Shader.hpp>

#include <array>
#include <vector>
#include <string>

namespace gl
{
  class Program
  {
    unsigned program_;
    std::vector<Shader> shaders_;
  public:
    Program();
    ~Program();

    Program(const std::string& vertexShader, const std::string& fragmentShader);

    void attachShader(Shader shader);
    void link();
    void use() const;
    void unuse() const;

    void setUniform1f(const char* name, float value) const;
    void setUniform2f(const char* name, const std::array<float,2>& value) const;
    void setUniform3f(const char* name, const std::array<float,3>& value) const;
    void setUniform4f(const char* name, const std::array<float,4>& value) const;

    unsigned get() const { return program_; }
  };
} // namespace gl
