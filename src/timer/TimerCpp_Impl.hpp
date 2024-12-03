//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#pragma once

#include <timer/Timer.hpp>

#include <stdexcept>

namespace timer
{
  class Timer::Impl
  {
  public:
    // Start the timer
    void start(size_t milliseconds, Callback callback)
    {
      throw std::runtime_error{"Not implemented"};
    }

    // Stop the timer
    void stop()
    {
      // Do nothing
    }

    // Check if the timer is running
    bool isRunning() const
    {
      return false;
    }
  };

} // namespace timer
