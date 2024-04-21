//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#include <gui/Application.hpp>
#include <gui/Frame.hpp>

#include <imgui_te_context.h>

#include <iostream>

void registerHelloGuiTests(ImGuiTestEngine* e)
{
    ImGuiTest* t = NULL;

    t = IM_REGISTER_TEST(e, "hello_gui", "output_text");
    struct TestVars
    {
      bool guiRendered = false;
      std::string text;
    };
    t->SetVarsDataType<TestVars>();
    t->GuiFunc = [](ImGuiTestContext* ctx)
    {
      IM_UNUSED(ctx);
      auto app = gui::Application::getInstancePtr();
      auto& window = app->getWindow();
      auto& frames = window.getFrames();
      IM_CHECK_GE(frames.size(), 1);
      auto framePtr = frames.front();
      IM_CHECK(framePtr);

      TestVars& vars = ctx->GetVars<TestVars>();
      vars.guiRendered = true;

      ImGui::Begin("Test Window", NULL, ImGuiWindowFlags_NoSavedSettings);
      ImGui::LogToBuffer();
      framePtr->render();
      vars.text = ctx->UiContext->LogBuffer.c_str();
      ImGui::LogFinish();
      ImGui::End();
    };
    t->TestFunc = [](ImGuiTestContext* ctx)
    {
      TestVars& vars = ctx->GetVars<TestVars>();
      if (!vars.guiRendered)
      { //skip test if gui was not rendered
        return;
      }
      ctx->SetRef("Test Window");
      std::cout << "[TestFunc hello_gui::output_text] vars.text = "
        << vars.text << std::endl;
      IM_CHECK_STR_EQ(vars.text.c_str(), "Hello World!");
    };
}
