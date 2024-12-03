//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#pragma once

#include <timer/Timer.hpp>

#include <atomic>
#include <thread>

#include <iostream>

namespace timer
{
  class Timer::Impl
  {
    std::atomic<bool> running_;
    std::thread thread_;
  public:
    // Default constructor
    Impl() : running_{false}, thread_{}
    {
    }

    // Destructor
    ~Impl()
    {
      stop();
    }

    // Start the timer
    void start(size_t milliseconds, Callback callback)
    {
      // Ensure the timer is stopped before starting a new one, and old thread
      // is joined if it wasn't already
      stop();

      if (running_ || thread_.joinable())
      { // The timer thread is still running, something is wrong
        throw std::runtime_error{ "Timer thread is still running" };
        return;
      }

      if (milliseconds == 0)
      { // Do not start the timer if the period is zero
        return;
      }

      // Start a new timer
      running_ = true;
      thread_ = std::thread(
        [this, milliseconds, callback = std::move(callback)]()
        {
          // Calculate the time taken by the callback function last time
          std::chrono::milliseconds callbackTime{ 0 };
          while (running_)
          {
            // Sleep until the next callback event
            if (callbackTime < std::chrono::milliseconds(milliseconds))
            {
              std::this_thread::sleep_for(
                std::chrono::milliseconds(milliseconds) - callbackTime);
            }

            // Record the start time
            auto start{ std::chrono::high_resolution_clock::now() };

            // Call the callback function
            callback();

            // Record the end time
            auto end{ std::chrono::high_resolution_clock::now() };

            // Calculate the time taken by the callback function
            callbackTime = std::chrono::duration_cast<
              std::chrono::milliseconds>(end - start);
          }
        });
    }

    // Stop the timer
    void stop()
    {
      running_ = false;
      if (thread_.joinable() && std::this_thread::get_id() != thread_.get_id())
      { // join the thread if it is not the current thread
        thread_.join();
        thread_ = std::thread{};
      }
    }

    // Check if the timer is running
    bool isRunning() const
    {
      return running_;
    }
  };

} // namespace timer
