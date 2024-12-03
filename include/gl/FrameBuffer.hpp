//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#pragma once

#include <math/Vec2.hpp>

namespace gl
{
  using math::Vec2i;

  class FrameBuffer
  {
    Vec2i size_;
    unsigned fbo_;
    unsigned texture_;
    unsigned rbo_;
  public:
    FrameBuffer(const Vec2i& size = {0, 0});

    ~FrameBuffer();

    void setSize(const Vec2i& size);
    const Vec2i& getSize() const { return size_; }

    void bind() const;
    void unbind() const;

    unsigned getTexture() const { return texture_; }

  private:
    void generateFrameBuffer_();
  };

} // namespace gl
