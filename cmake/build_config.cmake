
include(cmake/common.cmake)

option(USE_GLFW_GL3 "Enable GLFW/OpenGL3 backend" ON)
option(USE_GUI_TEST_ENGINE "Enable Dear ImGui test engine" OFF)

set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/3rd-party/imgui)
checkout_submodules(${IMGUI_DIR})

if(USE_GLFW_GL3)
  set(GLFW_DIR ${PROJECT_SOURCE_DIR}/3rd-party/glfw)
  checkout_submodules(${GLFW_DIR})
endif()
if(USE_GUI_TEST_ENGINE)
  set(IMGUI_TEST_ENGINE_DIR ${PROJECT_SOURCE_DIR}/3rd-party/imgui_test_engine)
  checkout_submodules(${IMGUI_TEST_ENGINE_DIR})
endif()
