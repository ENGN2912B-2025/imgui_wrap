//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#pragma once

#include <gui/Widget.hpp>

#include "impl/util.hpp"

#include <imgui.h>

#include <stdexcept>

namespace gui
{
  Widget::Widget(
    const std::string& name,
    const Vec2i& pos,
    const Vec2i& size) :
      Rect{pos, size},
      name_{name}
  {
    if (name_.empty())
    {
      name_ = util::generateIdentifier();
    }
  }

  Widget::~Widget()
  {

  }

  bool Widget::renderBegin()
  {
    return true;
  }

  void Widget::renderEnd()
  {

  }

  void Widget::render()
  {

  }

  const std::vector<Widget*>& Widget::getChildren() const
  {
    return children_;
  }

  const std::string& Widget::getName() const
  {
    return name_;
  }

  void Widget::setName(const std::string& name)
  {
    if (name.empty())
    {
      throw std::invalid_argument{"name cannot be empty"};
    }
    name_ = name;
  }

  void Widget::addChild(Widget* child)
  {
    children_.push_back(child);
  }

  void Widget::removeChild(Widget* child)
  {
    children_.erase(
      std::remove(children_.begin(), children_.end(), child),
      children_.end());
  }

  void Widget::draw()
  {
    if (renderBegin())
    {
      render();
      for (auto child : children_)
      {
        child->draw();
      }
    }
    renderEnd();
  }

  Vec2i Widget::getItemSpacing() const
  {
    return make<Vec2i>(ImGui::GetStyle().ItemSpacing);
  }

  Vec2i Widget::getContentMin() const
  {
    return gui::make<gui::Vec2i>(ImGui::GetWindowContentRegionMin());
  }

  Vec2i Widget::getContentMax() const
  {
    return gui::make<gui::Vec2i>(ImGui::GetWindowContentRegionMax());
  }

  Vec2i Widget::getContentSize() const
  {
    return getContentMax() - getContentMin();
  }

} // namespace gui
