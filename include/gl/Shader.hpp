//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#pragma once

namespace gl
{
  class Shader
  {
    unsigned shader_;
  public:
    Shader(unsigned type);
    ~Shader();

    void source(const char* source);
    void compile();
    unsigned get() const { return shader_; }

    static Shader defaultVertexShader();
    static Shader defaultFragmentShader();
  };
} // namespace gl
