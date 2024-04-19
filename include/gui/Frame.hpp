//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#pragma once

#include <gui/Types.hpp>

#include <string>

namespace gui
{
  class Frame
  {
    std::string name_;
    std::string id_;
    Vec2i pos_;
    Vec2i size_;
    int flags_;
  public:
    Frame(
      const std::string& name = "Frame",
      const Vec2i& pos = {0, 0},
      const Vec2i& size = {640, 480},
      int flags = -1);
    virtual ~Frame();

    bool renderBegin();
    void renderEnd();
    virtual void render();

    void setPosition(const Vec2i& pos);
    void setSize(const Vec2i& size);
  };

} // namespace gui
