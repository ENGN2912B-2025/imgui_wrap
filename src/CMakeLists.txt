
add_library(imgui_wrap STATIC
  Application.cpp
  Window.cpp
  Frame.cpp
  Sizer.cpp
  VerticalSizer.cpp
  imgui_stdlib.cpp
  # private files
  impl/Backend.cpp
  impl/Backend_Null.cpp
)

target_link_libraries(imgui_wrap PUBLIC imgui)

target_include_directories(imgui_wrap
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

if (USE_GLFW_GL3)
  target_sources(imgui_wrap PRIVATE impl/Backend_GLFW_GL3.cpp)
endif(USE_GLFW_GL3)

if (USE_GUI_TEST_ENGINE)
  target_sources(imgui_wrap PRIVATE impl/TestReporter.cpp)
  target_link_libraries(imgui_wrap PUBLIC imgui_test_engine)

  option(SHOW_TEST_ENGINE_WINDOWS "Show test engine windows" OFF)
  if (SHOW_TEST_ENGINE_WINDOWS)
    target_compile_definitions(imgui_wrap PRIVATE SHOW_TEST_ENGINE_WINDOWS)
  endif(SHOW_TEST_ENGINE_WINDOWS)

endif(USE_GUI_TEST_ENGINE)
