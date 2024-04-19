//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#include <gui/Application.hpp>

namespace gui
{
  // static member initialization
  Application* Application::instance_{ nullptr };

  Application::Application(const std::string& title) :
    window_{ std::make_unique<Window>(title) }
  {
    if (instance_ == nullptr)
    {
      setInstancePtr(this);
    }
  }

  Application::~Application()
  {
  }

  Window& Application::getWindow()
  {
    return *window_;
  }

  const Window& Application::getWindow() const
  {
    return *window_;
  }

  void Application::run()
  {
    //init window
    window_->init();

    // main loop
    while (window_->renderBegin())
    {
      window_->render();
      window_->renderEnd();
    }

    //deinit window
    window_->deinit();
  }

} // namespace support
