//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#include <gui/Sizer.hpp>

#include <imgui.h>

#include <cassert>

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

  NewSizer::~NewSizer()
  {
  }

  StackSizer::StackSizer(Direction direction) :
    NewSizer{},
    direction_{direction}
  {
  }

  void StackSizer::draw()
  {
    apply();
    NewSizer::draw();
  }

  void StackSizer::apply()
  {
    const int numChildren{ static_cast<int>(getChildren().size()) };
    if (numChildren == 0)
    { //no children, nothing to do
      return;
    }

    const bool isVertical{ direction_ == Direction::Vertical };

    const Vec2i size{ getSize() };
    const Vec2i space{ getItemSpacing() };

    const int adjustSize{ isVertical ? size.y : size.x };
    const int adjustSpace{ isVertical ? space.y : space.x };

#if 0
    const int otherSize{ isVertical ? size.x - 2*space.x : size.y - 2*space.y };

    // Regular size for all children
    // -----------------------------
    // size = space + childSize + space + .... + space
    // size = space * (numChildren + 1) + childSize * numChildren
    // childSize = (size - space * (numChildren + 1)) / numChildren
    const int childSize{ std::max(0,
      (adjustSize - adjustSpace * (numChildren + 1)) / numChildren) };
    const int lastChildSize{ adjustSize
      - (numChildren + 1) * adjustSpace - (numChildren - 1) * childSize };
    assert((numChildren - 1) *childSize
      + lastChildSize + (numChildren + 1) * adjustSpace == adjustSize);

    // Apply to children
    Vec2i pos{ getPosition() + space };
    if (isVertical)
    {
      for (auto& child : getChildren())
      {
        child->setSize(Vec2i{ otherSize, childSize });
        child->setPosition(pos);
        pos.y += childSize + adjustSpace;
      }
      { // handle last child
        auto& lastChild{ getChildren().back() };
        lastChild->setSize(Vec2i{ otherSize, lastChildSize });
      }
    }
    else
    {
      for (auto& child : getChildren())
      {
        child->setSize(Vec2i{ childSize, otherSize });
        child->setPosition(pos);
        pos.x += childSize + adjustSpace;
      }
      { // handle last child
        auto& lastChild{ getChildren().back() };
        lastChild->setSize(Vec2i{ lastChildSize, otherSize });
      }
    }
#else
    const int otherSize{ isVertical ? size.x : size.y };

    // Regular size for all children
    // -----------------------------
    // size = childSize + space + ... + childSize
    // size = space * (numChildren - 1) + childSize * numChildren
    // childSize = (size - space * (numChildren - 1)) / numChildren
    const int childSize{ std::max(0,
      (adjustSize - adjustSpace * (numChildren - 1)) / numChildren) };
    const int lastChildSize{ adjustSize
      - (numChildren - 1) * (adjustSpace + childSize) };

    // Apply to children
    Vec2i pos{ getPosition() };
    if (isVertical)
    {
      for (auto& child : getChildren())
      {
        child->setSize(Vec2i{ otherSize, childSize });
        child->setPosition(pos);
        pos.y += childSize + adjustSpace;
      }
      { // handle last child
        auto& lastChild{ getChildren().back() };
        lastChild->setSize(Vec2i{ otherSize, lastChildSize });
      }
    }
    else
    {
      for (auto& child : getChildren())
      {
        child->setSize(Vec2i{ childSize, otherSize });
        child->setPosition(pos);
        pos.x += childSize + adjustSpace;
      }
      { // handle last child
        auto& lastChild{ getChildren().back() };
        lastChild->setSize(Vec2i{ lastChildSize, otherSize });
      }
    }
#endif
  }

  VerticalSizer2::VerticalSizer2()
    : StackSizer{Direction::Vertical}
  {
  }

  HorizontalSizer2::HorizontalSizer2()
    : StackSizer{Direction::Horizontal}
  {
  }

} // namespace gui
