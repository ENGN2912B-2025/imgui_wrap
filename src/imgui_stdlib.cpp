//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#pragma once

#include <gui/imgui_stdlib.hpp>

#include <imgui.h>

namespace ImGui
{
  void Text(const std::string fmt, ...)
  {
    va_list args;
    va_start(args, fmt);
    ImGui::TextV(fmt.c_str(), args);
    va_end(args);
  }
}
