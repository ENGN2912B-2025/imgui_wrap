//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#include "TestReporter.hpp"

#include <imgui_te_internal.h>

#include <iostream>

#ifdef _WIN32
# include <windows.h>
#endif

namespace gui
{
  std::unique_ptr<TestReporter> TestReporter::makeDefault()
  {
    return std::make_unique<TestReporterConsole>();
  }

  namespace
  {
    enum class ColorCode
    {
      Default, Red, Green, Yellow, Cyan
    };

    std::string setColor(ColorCode color)
    {
      switch (color)
      {
        case ColorCode::Red:    return "\033[31m";
        case ColorCode::Green:  return "\033[32m";
        case ColorCode::Yellow: return "\033[33m";
        case ColorCode::Cyan:   return "\033[36m";
        default:
         break;
      }
      return "\033[0m"; //Reset to default color
    }

#ifdef _WIN32
    bool enableAnsiEscape(
      std::ostream& os, bool enable, bool* wasEnabled = nullptr)
    {
      HANDLE hConsole;
      if (os.rdbuf() == std::cout.rdbuf())
      {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
      }
      else if (os.rdbuf() == std::cerr.rdbuf())
      {
        hConsole = GetStdHandle(STD_ERROR_HANDLE);
      }
      else
      {
        return false;
      }

      // Get the current console mode
      DWORD consoleMode;
      if (!GetConsoleMode(hConsole, &consoleMode)) {
        // If GetConsoleMode fails, return false
        return false;
      }

      const bool isEnabled{
        (consoleMode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) != 0 };
      if (wasEnabled)
      {
        *wasEnabled = isEnabled;
      }

      if (isEnabled == enable)
      {
        // If the state is already the same, return true
        return true;
      }

      if (enable)
      {
        // Enable ANSI escape codes
        consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
      }
      else
      {
        // Disable ANSI escape codes
        consoleMode &= ~ENABLE_VIRTUAL_TERMINAL_PROCESSING;
      }

      // Set the new console mode
      if (!SetConsoleMode(hConsole, consoleMode)) {
        // If SetConsoleMode fails, return false
        return false;
      }

      return true;
    }
#endif
  }

  void TestReporterConsole::generateReport(ImGuiTestEngine* engine, std::ostream& os)
  {
    int count_tested = 0;
    int count_success = 0;
    ImGuiTestEngine_GetResult(engine, count_tested, count_success);

#ifdef _WIN32
    bool wasAnsiEnabled;
    enableAnsiEscape(os, true, &wasAnsiEnabled);
#endif

    if (count_success < count_tested)
    {
      os << "\nFailing tests:\n";
      for (ImGuiTest* test : engine->TestsAll)
      {
        if (test->Output.Status == ImGuiTestStatus_Error)
        {
          os << "- " << test->Name << "\n";
        }
      }
    }

    const bool failed{ count_success != count_tested };
    try
    {
      os
        << setColor(failed ? ColorCode::Red : ColorCode::Green)
        << "\nTests Result: " << (failed ? "Errors" : "OK") << "\n"
        << "(" << count_success << "/" << count_tested << " tests passed)\n";
    }
    catch(const std::exception& e)
    {
    }

    os << setColor(ColorCode::Default); //make sure we reset colors

#ifdef _WIN32
    if (wasAnsiEnabled == false)
    { // If ANSI escape codes were not enabled before, disable them now
      enableAnsiEscape(os, false);
    }
#endif
  }

  void TestReporterMarkdown::generateReport(ImGuiTestEngine* engine, std::ostream& os)
  {
    int count_tested = 0;
    int count_success = 0;
    ImGuiTestEngine_GetResult(engine, count_tested, count_success);

    if (count_success < count_tested)
    {
      os << "\nFailing tests:\n";
      for (ImGuiTest* test : engine->TestsAll)
      {
        if (test->Output.Status == ImGuiTestStatus_Error)
        {
          os << "- " << test->Name << "\n";
        }
      }
    }

    const bool failed{ count_success != count_tested };
    os
      << "\n"
      << "<span style='color: " << (failed ? "red" : "green") << ";'>"
      << "Tests Result: "
      << count_success << "/" << count_tested << " tests passed"
      << "</span>"
      << "\n";
  }
}