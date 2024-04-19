//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#pragma once

#include <gui/Backend.hpp>

namespace gui
{
  class Backend_Null : public Backend
  {
  public:
    ~Backend_Null() = default;

    static std::unique_ptr<Backend_Null> create();

    ImU64 LastTime = 0;

    bool InitCreateWindow(const char* window_title, ImVec2 window_size) override;
    void InitBackends() override;
    bool NewFrame() override;
    void Render() override;
    void ShutdownCloseWindow() override;
    void ShutdownBackends() override;
    bool CaptureFramebuffer(
      ImGuiViewport* viewport,
      int x, int y, int w, int h,
      unsigned int* pixels_rgba, void* user_data) override;
  };

} // namespace gui
