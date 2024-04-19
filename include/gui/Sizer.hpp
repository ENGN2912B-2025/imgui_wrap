//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#pragma once

#include <gui/Types.hpp>

#include <vector>

namespace gui
{
  // forward declarations
  class Frame;

  class Sizer
  {
    std::vector<Frame*> frames_;
  public:
    virtual ~Sizer() = 0;

    const std::vector<Frame*>& getFrames() const { return frames_; }

    void addFrame(Frame* frame);
    void removeFrame(Frame* frame);

    virtual void apply(const Vec2i& size) = 0;
  };

} // namespace gui
