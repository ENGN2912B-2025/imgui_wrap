//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#pragma once

#include <gui/Rect.hpp>

#include <vector>

namespace gui
{
  class Sizer
  {
    std::vector<Rect*> children_;
  public:
    virtual ~Sizer() = 0;

    const std::vector<Rect*>& getChildren() const { return children_; }

    void add(Rect* child);
    void remove(Rect* child);

    virtual void apply(const Vec2i& size) = 0;
  };

} // namespace gui
