//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#include <gui/VerticalSizer.hpp>
#include <gui/Frame.hpp>

#include <cmath>

namespace gui
{
  void VerticalSizer::apply(const Vec2i& size)
  {
    auto& children{ getChildren() };
    if (children.empty())
    {
      return;
    }

    const int n{ static_cast<int>(children.size()) };
    const int dy{ static_cast<int>(size.y) / n };

    Vec2i childPos{ 0, 0 };
    Vec2i childSize{ static_cast<int>(size.x), dy };
    for (auto child : children)
    {
      child->setPosition(childPos);
      child->setSize(childSize);
      childPos.y += dy;
    }

    //ensure last child fills the remaining space
    childSize.y += static_cast<int>(size.y) % dy;
    children.back()->setSize(childSize);
  }

} // namespace gui
