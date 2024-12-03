//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#pragma once

#include <gl/Shader.hpp>

#include <vector>

namespace gl
{
  class Program
  {
    unsigned program_;
    std::vector<Shader> shaders_;
  public:
    Program();
    ~Program();

    void attachShader(Shader shader);
    void link();
    void use() const;
    void unuse() const;

    unsigned get() const { return program_; }

    static Program defaultProgram();
  };
} // namespace gl
