//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#include <gui/Sizer.hpp>

#include <imgui.h>

#include <cassert>
#include <numeric>
#include <stdexcept>

namespace gui
{
  Sizer::~Sizer()
  {
  }

  StackingSizer::StackingSizer(Direction direction) :
    Sizer{},
    direction_{direction}
  {
  }

  void StackingSizer::addChild(Widget* child, int weight)
  {
    while (weights_.size() < getChildren().size())
    {
      weights_.push_back(1);
    }
    if (weight < 1)
    {
      throw std::invalid_argument("weight must be greater than 0");
    }
    Sizer::addChild(child);
    weights_.push_back(weight);
  }

  void StackingSizer::addWithFixedSize(Widget* child, int size)
  {
    addChild(child);
    weights_.back() = -size; // negative size indicates fixed size
  }

  void StackingSizer::draw()
  {
    apply();
    Sizer::draw();
  }

  void StackingSizer::apply()
  {
    std::vector<Widget*> children{ getChildren() };
    const int numChildren{ static_cast<int>(children.size()) };
    if (numChildren == 0)
    { //no children, nothing to do
      return;
    }
    if (weights_.size() < numChildren)
    {
      weights_.resize(numChildren, 1);
    }

    const bool isVertical{ direction_ == Direction::Vertical };

    const Vec2i totalSize{ getSize() };
    const Vec2i space{ getItemSpacing() };

    // Size of weighted children
    // -------------------------
    // size = childSize + space + ... + childSize
    // size = space * (numChildren - 1) + childSize * totalWeight
    // childSize = (size - space * (numChildren - 1)) / totalWeight

    int totalWeight{ 0 }, fixedSize{ 0 }, lastWeightedIndex{ 0 };
    for (int i = 0; i < numChildren; ++i)
    {
      const int weight{ weights_[i] };
      if (weight > 0)
      {
        totalWeight += weight;
        lastWeightedIndex = i;
      }
      else
      {
        fixedSize -= weight;
      }
    }

    const int adjustSize{ (isVertical ? totalSize.y : totalSize.x) - fixedSize };
    const int adjustSpace{ isVertical ? space.y : space.x };

    const int otherSize{ isVertical ? totalSize.x : totalSize.y };

    const int childSize{ std::max(0,
      (adjustSize - (numChildren - 1) * adjustSpace) / totalWeight) };
    const int leftOverSize{ adjustSize
      - (numChildren - 1) * adjustSpace - totalWeight * childSize };

    // Apply to children
    Vec2i pos{ getPosition() };
    if (isVertical)
    {
      for (int i = 0; i < numChildren; ++i)
      {
        auto& child{ children[i] };
        int weight{ weights_[i] };
        int size{ weight < 0 ? -weight : weight * childSize };
        if (i == lastWeightedIndex)
        {
          size += leftOverSize;
        }
        child->setSize(Vec2i{ otherSize, size });
        child->setPosition(pos);
        pos.y += size + adjustSpace;
      }
    }
    else
    {
      for (int i = 0; i < numChildren; ++i)
      {
        auto& child{ children[i] };
        int weight{ weights_[i] };
        int size{ weight < 0 ? -weight : weight * childSize };
        if (i == lastWeightedIndex)
        {
          size += leftOverSize;
        }
        child->setSize(Vec2i{ size, otherSize });
        child->setPosition(pos);
        pos.x += size + adjustSpace;
      }
    }
  }

  VerticalSizer::VerticalSizer()
    : StackingSizer{Direction::Vertical}
  {
  }

  HorizontalSizer::HorizontalSizer()
    : StackingSizer{Direction::Horizontal}
  {
  }

} // namespace gui
