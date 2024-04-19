//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#pragma once

#include <gui/Sizer.hpp>

namespace gui
{
  class VerticalSizer : public Sizer
  {
  public:
    void apply(const Vec2i& size) override;
  };

} // namespace gui
