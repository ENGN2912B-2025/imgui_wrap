//  Copyright (c) 2024 Daniel Moreno. All rights reserved.
//

#pragma once

#include <memory>
#include <string>
#include <functional>

struct ImGuiTestEngine;

namespace gui
{
  class TestManager
  {
  public:
    using TestRegister = void(ImGuiTestEngine*);

    static TestManager& getInstance()
    {
      static TestManager instance;
      return instance;
    }

    void registerTests(TestRegister& test)
    {
      registry_.emplace_back(test);
    }

    void processRegistrations(ImGuiTestEngine* engine)
    {
      for (auto& registerTest : registry_)
      {
        registerTest(engine);
      }
    }

  private:
    std::vector<TestRegister*> registry_;

    TestManager() = default;
    TestManager(const TestManager&) = delete;
    TestManager& operator=(const TestManager&) = delete;
  };

} // namespace gui

#define REGISTER_TEST(testRegistrationFunction) \
  void testRegistrationFunction(ImGuiTestEngine* e);  \
  namespace { \
    static bool testRegistrationFunction_{ ( \
      gui::TestManager::getInstance().registerTests(testRegistrationFunction), true) }; \
  }
