//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#pragma once

#include <gui/Rect.hpp>

#include <string>

namespace gui
{
  class Frame : public Rect
  {
    std::string name_;
    std::string id_;
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

    const std::string& getName() const;
    const std::string& getId() const;
  };

} // namespace gui
