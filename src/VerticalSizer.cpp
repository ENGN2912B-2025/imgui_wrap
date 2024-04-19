//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#include <gui/VerticalSizer.hpp>
#include <gui/Frame.hpp>

#include <cmath>

namespace gui
{
  void VerticalSizer::apply(const Vec2i& size)
  {
    auto& frames{ getFrames() };
    if (frames.empty())
    {
      return;
    }

    const int n{ static_cast<int>(frames.size()) };
    const int dy{ static_cast<int>(size.y) / n };

    Vec2i framePos{ 0, 0 };
    Vec2i frameSize{ static_cast<int>(size.x), dy };
    for (auto frame : frames)
    {
      frame->setPosition(framePos);
      frame->setSize(frameSize);
      framePos.y += dy;
    }

    //ensure last frame fills the remaining space
    frameSize.y += static_cast<int>(size.y) % dy;
    frames.back()->setSize(frameSize);
  }

} // namespace gui
