//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#include <gui/Application.hpp>

#ifdef USE_GUI_TEST_ENGINE
  // Test Engine
  #include <imgui_te_engine.h>
  #include <imgui_te_ui.h>
  #include <imgui_te_utils.h>  // ImOsIsDebuggerPresent()
  #include <imgui_te_exporters.h>
  namespace
  {
    static ImGuiTestEngine* initTestEngine_()
    {
      // Setup test engine
      ImGuiTestEngine* engine = ImGuiTestEngine_CreateContext();
      ImGuiTestEngineIO& test_io = ImGuiTestEngine_GetIO(engine);
      test_io.ConfigVerboseLevel = ImGuiTestVerboseLevel_Info;
      test_io.ConfigVerboseLevelOnError = ImGuiTestVerboseLevel_Debug;
      test_io.ConfigRunSpeed = ImGuiTestRunSpeed_Cinematic; // Default to slowest mode in this demo
      //test_io.ScreenCaptureFunc = ImGuiApp_ScreenCaptureFunc;
      //test_io.ScreenCaptureUserData = (void*)app;

      // Optional: save test output in junit-compatible XML format.
      //test_io.ExportResultsFile = "./results.xml";
      //test_io.ExportResultsFormat = ImGuiTestEngineExportFormat_JUnitXml;

      // Start test engine
      ImGuiTestEngine_Start(engine, ImGui::GetCurrentContext());
      ImGuiTestEngine_InstallDefaultCrashHandler();

      // Register tests
      //RegisterAppMinimalTests(engine);

      return engine;
    }
  }
#endif


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

  #ifdef USE_GUI_TEST_ENGINE
    ImGuiTestEngine* engine = initTestEngine_();
    //TODO: Register tests -----------------------------------------------
  #endif

    // main loop
    while (window_->renderBegin())
    {
      window_->render();
      window_->renderEnd();

#ifdef USE_GUI_TEST_ENGINE
      // Call after your rendering. This is mostly to support screen/video
      //  capturing features.
      ImGuiTestEngine_PostSwap(engine);
#endif
    }

  #ifdef USE_GUI_TEST_ENGINE
    ImGuiTestEngine_Stop(engine);
  #endif

    //deinit window
    window_->deinit();

  #ifdef USE_GUI_TEST_ENGINE
    // IMPORTANT: we need to destroy the Dear ImGui context BEFORE the test
    //  engine context, so .ini data may be saved.
    ImGuiTestEngine_DestroyContext(engine);

    ImGuiTestEngine_PrintResultSummary(engine);

    int count_tested = 0;
    int count_success = 0;
    ImGuiTestEngine_GetResult(engine, count_tested, count_success);
    if (count_tested != count_success)
    {
       exit(EXIT_FAILURE); // Error
    }
    exit(EXIT_SUCCESS); // OK
  #endif
  }

} // namespace support
