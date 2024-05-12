//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#include <gui/Sizer.hpp>

namespace gui
{
  Sizer::~Sizer()
  {
  }

  void Sizer::add(Rect* child)
  {
    children_.push_back(child);
  }

  void Sizer::remove(Rect* child)
  {
    children_.erase(
      std::remove(children_.begin(), children_.end(), child),
      children_.end());
  }

} // namespace gui
