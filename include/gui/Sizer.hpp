//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#pragma once

#include <gui/Widget.hpp>

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

  class NewSizer : public Widget
  {
  public:
    virtual ~NewSizer() = 0;
  };

  class StackSizer : public NewSizer
  {
  public:
    enum class Direction
    {
      Vertical,
      Horizontal,
    };

    StackSizer(Direction direction);

    void addChild(Widget* child, int weight = 1);

    void draw() override;

    void apply();

  private:
    Direction direction_;
    std::vector<int> weights_;
  };

  class VerticalSizer2 : public StackSizer
  {
  public:
    VerticalSizer2();
  };

  class HorizontalSizer2 : public StackSizer
  {
  public:
    HorizontalSizer2();
  };

} // namespace gui
