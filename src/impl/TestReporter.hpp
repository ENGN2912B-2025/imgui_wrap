//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#pragma once

#include <imgui_te_engine.h>

#include <memory>

namespace gui
{
  class TestReporter
  {
  public:
    virtual ~TestReporter() = default;

    static std::unique_ptr<TestReporter> makeDefault();

    virtual void generateReport(ImGuiTestEngine* engine, std::ostream& os) = 0;
  };

  class TestReporterConsole : public TestReporter
  {
  public:
    void generateReport(ImGuiTestEngine* engine, std::ostream& os) override;
  };

  class TestReporterMarkdown : public TestReporter
  {
  public:
    void generateReport(ImGuiTestEngine* engine, std::ostream& os) override;
  };

} // namespace gui
