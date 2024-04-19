//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#include <gui/Sizer.hpp>

namespace gui
{
  Sizer::~Sizer()
  {
  }

  void Sizer::addFrame(Frame* frame)
  {
    frames_.push_back(frame);
  }

  void Sizer::removeFrame(Frame* frame)
  {
    frames_.erase(
      std::remove(frames_.begin(), frames_.end(), frame),
      frames_.end());
  }

} // namespace gui
