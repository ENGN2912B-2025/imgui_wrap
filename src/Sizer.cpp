//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#include <gui/Sizer.hpp>

#include <imgui.h>

#include <cassert>
#include <numeric>

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

  void StackSizer::addChild(Widget* child, int weight)
  {
    while (weights_.size() < getChildren().size())
    {
      weights_.push_back(1);
    }
    NewSizer::addChild(child);
    weights_.push_back(weight);
  }

  void StackSizer::draw()
  {
    apply();
    NewSizer::draw();
  }

  void StackSizer::apply()
  {
    std::vector<Widget*> children{ getChildren() };
    const int numChildren{ static_cast<int>(children.size()) };
    if (numChildren == 0)
    { //no children, nothing to do
      return;
    }

    const bool isVertical{ direction_ == Direction::Vertical };

    const Vec2i totalSize{ getSize() };
    const Vec2i space{ getItemSpacing() };

    const int adjustSize{ isVertical ? totalSize.y : totalSize.x };
    const int adjustSpace{ isVertical ? space.y : space.x };

    const int otherSize{ isVertical ? totalSize.x : totalSize.y };

    // Weighted size for all children
    // -----------------------------
    // size = childSize + space + ... + childSize
    // size = space * (numChildren - 1) + childSize * totalWeight
    // childSize = (size - space * (numChildren - 1)) / totalWeight
    const int totalWeight{ std::accumulate(weights_.begin(), weights_.end(), 0) };
    const int childSize{ std::max(0,
      (adjustSize - adjustSpace * (numChildren - 1)) / totalWeight) };
    const int lastChildSize{ adjustSize
      - (numChildren - 1) * adjustSpace - (totalWeight - 1) * childSize };

    // Apply to children
    Vec2i pos{ getPosition() };
    if (isVertical)
    {
      for (int i = 0; i < numChildren - 1; ++i)
      {
        auto& child{ children[i] };
        const int weight{ weights_[i] };
        const int size{ weight * childSize };
        child->setSize(Vec2i{ otherSize, size });
        child->setPosition(pos);
        pos.y += size + adjustSpace;
      }
      { // handle last child
        auto& lastChild{ children.back() };
        const int weight{ weights_.back() };
        const int size{ (weight - 1) * childSize + lastChildSize };
        lastChild->setSize(Vec2i{ otherSize, size});
        lastChild->setPosition(pos);
      }
    }
    else
    {
      for (int i = 0; i < numChildren - 1; ++i)
      {
        auto& child{ children[i] };
        const int weight{ weights_[i] };
        const int size{ weight * childSize };
        child->setSize(Vec2i{ size, otherSize });
        child->setPosition(pos);
        pos.x += size + adjustSpace;
      }
      { // handle last child
        auto& lastChild{ children.back() };
        const int weight{ weights_.back() };
        const int size{ (weight - 1) * childSize + lastChildSize };
        lastChild->setSize(Vec2i{ size, otherSize });
        lastChild->setPosition(pos);
      }
    }
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
