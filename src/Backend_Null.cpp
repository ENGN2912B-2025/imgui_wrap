//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//
#include <gui/Backend_Null.hpp>

#include <chrono>

namespace
{
  static uint64_t GetTimeInMicroseconds_()
  {
    using namespace std;
    chrono::microseconds ms = chrono::duration_cast<chrono::microseconds>(
      chrono::high_resolution_clock::now().time_since_epoch());
    return static_cast<uint64_t>(ms.count());
  }
}

namespace gui
{
  std::unique_ptr<Backend_Null> Backend_Null::create()
  {
    return std::make_unique<Backend_Null>();
  }

  bool Backend_Null::InitCreateWindow(
    const char* window_title, ImVec2 window_size)
  {
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = window_size;
    io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset | ImGuiBackendFlags_HasMouseCursors;
    //io.Fonts->Build();
#if IMGUI_VERSION_NUM < 18603
    for (int n = 0; n < ImGuiKey_COUNT; n++)
        io.KeyMap[n] = n;
#endif

    return true;
  }

  void Backend_Null::InitBackends()
  {

  }

  bool Backend_Null::NewFrame()
  {
    ImGuiIO& io = ImGui::GetIO();

    //unsigned char* pixels = NULL;
    //int width = 0;
    //int height = 0;
    //io.Fonts->GetTexDataAsAlpha8(&pixels, &width, &height);

    uint64_t time = GetTimeInMicroseconds_();
    if (LastTime == 0)
        LastTime = time;
    io.DeltaTime = (float)((double)(time - LastTime) / 1000000.0);
    if (io.DeltaTime <= 0.0f)
        io.DeltaTime = 0.000001f;
    LastTime = time;

    return true;
  }

  bool Backend_Null::CaptureFramebuffer(
    ImGuiViewport* viewport,
    int x, int y, int w, int h,
    unsigned int* pixels, void* user_data)
  {
    memset(pixels, 0, static_cast<size_t>(w * h) * sizeof(unsigned int));
    return false;
  }

  void Backend_Null::Render()
  {
    ImDrawData* draw_data = ImGui::GetDrawData();

    // RenderDrawData
    for (int n = 0; n < draw_data->CmdListsCount; n++)
    {
      const ImDrawList* cmd_list = draw_data->CmdLists[n];
      for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
      {
        const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
        if (pcmd->UserCallback != NULL)
        {
          if (pcmd->UserCallback != ImDrawCallback_ResetRenderState)
              pcmd->UserCallback(cmd_list, pcmd);
        }
      }
    }
  }

  void Backend_Null::ShutdownCloseWindow()
  {
    // nothing to do
  }

  void Backend_Null::ShutdownBackends()
  {
    // nothing to do
  }

} // namespace gui
