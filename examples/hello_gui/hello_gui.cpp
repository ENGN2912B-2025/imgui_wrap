//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#include <gui/Application.hpp>
#include <gui/Frame.hpp>
#include <imgui.h>

class MainWindow : public gui::Frame
{
public:
  void render() override
  {
    ImGui::Text("Hello World!");
  }
};

int main(int argc, char** argv)
{
  // Create the application
  gui::Application app{ "GUI: Hello World!" };

  // Create the main window
  MainWindow mainWindow;

  // Run the application
  app.run();

  return 0;
}
